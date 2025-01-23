import struct
import os 
import select
import logger
from enum import Enum
from response import Response
from response import Status

# Max block size for sent packets
MAX_BLOCK_SIZE = 2048

class OpCode(Enum):
    BACKUPFILEOP = 100
    RETRIEVEFILEOP = 200
    DELETEFILEOP = 201
    LISTFILESOP = 202

class RequestHeader:
    def __init__(self, op: OpCode, user_id):
        self.user_id = user_id
        self.version = 1 
        self.op = op  
        self.name_len = None
        self.file_name = None
        self.file_size = None

    def setUserId(self,user_id):
        self.user_id = user_id

    def setName(self, file_name):
        self.file_name = file_name
        self.name_len = len(self.file_name)
        if self.op is OpCode.BACKUPFILEOP:
            try:
                self.file_size = os.path.getsize(self.file_name)
            except Exception:
                print(f"Error: The file '{self.file_name}' was not found.")
                self.file_size = 0 

    def getNameLen(self):
        return self.name_len

    def getOpCode(self):
        return self.op

    def setOpCode(self, op: OpCode):
        self.op = op

    def getUserID(self):
        return self.user_id
    
    def getFileSize(self):
        return self.file_size
    
    def getFileName(self):
        return self.file_name.encode('utf-8') if self.file_name else None

    # Packs the header according to the Op Code
    def pack_header(self):
        if self.op == OpCode.BACKUPFILEOP:
            return struct.pack('<I B B H I', self.user_id, self.version, self.op.value, self.name_len, self.file_size)
        elif self.op == OpCode.RETRIEVEFILEOP:
            return struct.pack('<I B B H I', self.user_id, self.version, self.op.value, self.name_len, 0)
        elif self.op == OpCode.DELETEFILEOP:
            return struct.pack('<I B B H I', self.user_id, self.version, self.op.value, self.name_len, 0)
        elif self.op == OpCode.LISTFILESOP:
            return struct.pack('<I B B H I', self.user_id, self.version, self.op.value, 0, 0)
        else:
            #raise ValueError("Unsupported op code")
            print("Error")
            return None

    # Create the full message: header + filename (encoded)
    def build_message(self):
        header = self.pack_header()
        if self.op != OpCode.LISTFILESOP:  # Only add file name for other ops
            if self.file_name:  # Only include the file name if it's set
                filename = self.getFileName()
                return header + filename
            else:
                return header  # If no file name, just return header
        else:
            return header  # For LISTFILESOP, no file name


# Request for file backup on server OpCode.BACKUPFILEOP (100)
def request_backup_file(user_id, socket, file):
    if not os.path.exists(file):
        print(f"Error: The file '{file}' does not exist.\n")
        return
    else:
        # Implement the header data
        header = RequestHeader(OpCode.BACKUPFILEOP, user_id)

        if file is not None:
            header.setName(file)
        request_header = header.pack_header()

        # Log the request 
        formatted_request = logger.format_hex(request_header, group_size=1)
        message = header.build_message()
        print("Sending file for backup")
        print(formatted_request)
        print(f"User ID: {header.getUserID()}")
        print(f"Op Code: {header.getOpCode()}")
        print(f"File Name: {header.getFileName().decode('utf-8')}")
        print(f"File Size: {header.getFileSize()}\n")

        socket.sendall(message)

        send_file(socket,header.getFileName())
        response = Response(socket)
        print(response)
 
# Sending files with the size of MAX_BLOCK_SIZE
def send_file(socket, file_name):
    # Grab file size
    file_size = os.path.getsize(file_name)  

    # We need to open the file in binary mode 
    # We send it according to blocks
    with open(file_name, 'rb') as file:
        bytes_sent = 0
        while bytes_sent < file_size:
            block = file.read(MAX_BLOCK_SIZE)
            if not block:
                break 
            try:
                socket.sendall(block)
            except Exception:
                print("Error sending files: \n")
                return
            bytes_sent += len(block)
            print(f"Sent {bytes_sent}/{file_size} bytes")

    print("File transfer complete.\n")

#Request for file list OpCode.RETRIEVEFILEOP (200)
def request_file(user_id,socket, file_name):
    # Implement the header data
    header = RequestHeader(OpCode.RETRIEVEFILEOP, user_id)
    header.setName(file_name)
    request_header = header.pack_header()

    # Log the request 
    formatted_request = logger.format_hex(request_header, group_size=1)
    message = header.build_message()
    print("Requesting File")
    print(formatted_request)
    print(f"User ID: {header.getUserID()}")
    print(f"Op Code: {header.getOpCode()}")
    print(f"File Name: {header.getFileName().decode('utf-8')}")
    print(f"File Size: {header.getFileSize()}\n")
    
    # Send the request
    socket.sendall(message)
    
    # Wait for response
    response = Response(socket)
    print(response)

#Request for file list OpCode.DELETEFILEOP (201)
def delete_from_server(user_id,socket,file_name):
    # Implement the header data
    header = RequestHeader(OpCode.DELETEFILEOP, user_id)
    header.setName(file_name)
    request_header = header.pack_header()

    # Log the request 
    formatted_request = logger.format_hex(request_header, group_size=1)
    message = header.build_message()
    print("Requesting deletion of file")
    print(formatted_request)
    print(f"User ID: {header.getUserID()}")
    print(f"Op Code: {header.getOpCode()}")
    print(f"File Name: {header.getFileName().decode('utf-8')}")
    print(f"File Size: {header.getFileSize()}\n")

    # Send the request
    socket.sendall(message)
    
    # Wait for response
    response = Response(socket)
    print(response)

#Request for file list OpCode.LISTFILESOP (202)
def request_file_list(user_id,socket):
    # Implement the header data
    header = RequestHeader(OpCode.LISTFILESOP,user_id)
    request_header = header.pack_header()

    # Log the request 
    formatted_request = logger.format_hex(request_header, group_size=1)
    message = header.build_message()
    print("Requesting File List")
    print(formatted_request)
    print(f"User ID: {header.getUserID()}")
    print(f"Op Code: {header.getOpCode()}\n")

    # Return the message to be sent
    socket.sendall(message)
    
    # Handle the response
    response = Response(socket)
    print(response)
    