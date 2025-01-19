import struct
import logger
from enum import Enum

class Status(Enum):
    FILES_RETREIVED = 210
    LIST_RETURNED = 211
    OPERATION_SUCCESS = 212
    FILE_NOT_FOUND = 1001
    EMPTY_DIRECTORY = 1002
    GENERAL_ERROR = 1003


class Response:
    # Response header format & size calculation
    HEADER_FORMAT = 'B H B I'  
    HEADER_SIZE = struct.calcsize(HEADER_FORMAT)

    # Constructor
    def __init__(self,socket):
        self.socket = socket
        self.hex_data = None
        self.version = None
        self.status = None
        self.name_len = None
        self.data_size = None
        self.name = None
        self.data = None
        self._parse_header()

    # Helper function to receive exactly 'size' bytes
    def _receive_all(self, size):
        data = bytearray()
        while len(data) < size:
            packet = self.socket.recv(size - len(data))
            if not packet:
                raise ConnectionError("Connection closed Prematurely")
            data.extend(packet)
            print(f"Recevied {len(data)}/{size} Bytes")
        return data     

    # Parses the header message and inputs the data to respected holders
    def _parse_header(self):
        header_data = self._receive_all(self.HEADER_SIZE)
        self.hex_data = logger.format_hex(header_data,1)
        self.version, status_code ,self.name_len, self.data_size = struct.unpack(
            self.HEADER_FORMAT,header_data
        )   
        self.status = Status(status_code) if status_code in Status._value2member_map_ else None
        

    # If we need to parse the file name
    def parse_name(self):
        if self.name is None and self.name_len > 0:
            self.name = self._receive_all(self.name_len).decode('utf-8')

    # Parses all the data
    def parse_data(self):
        if self.data is None and self.data_size > 0:
            self.data = self._receive_all(self.data_size)

    def get_data(self):
        return self.data

    def print_data(self):
        try:
            decoded_data = self.get_data().decode('utf-8') if self.get_data() is not None else "No data"
            return decoded_data
        except UnicodeDecodeError:
            return f"Raw data (hex): {self.get_data().hex()}"

    # Definition for a logger method
    def __str__(self):
        status_str = self.status.name if self.status else "UNKNOWN_STATUS"
        return (
            f"Response Receieved: \n"
            f"{self.hex_data}\n"
            f"Version: {self.version}\n"
            f"Status: {status_str}\n"
            f"Name Length: {self.name_len}\n"
            f"File Name: {self.name or 'None'}\n"
            f"Data Size: {self.data_size}\n"
            f"Data Received:\n{self.print_data()}")

            