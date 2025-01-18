import random
import struct
import os 
import logger
from enum import Enum

class OpCode(Enum):
    BACKUPFILEOP = 100
    RETRIEVEFILEOP = 200
    DELETEFILEOP = 201
    LISTFILESOP = 202


class RequestHeader:
    def __init__(self, op: OpCode):
        self.user_id = random.randint(0, 0xFFFFFFFF) 
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
        self.file_size = os.path.getsize(self.file_name)

    def getOpCode(self):
        return self.op
    def getUserID(self):
        return self.user_id
    
    def getFileSize(self):
        return self.file_size
    
    def getFileName(self):
        return self.file_name.encode('utf-8') if self.file_name else None

    def getNameLen(self):
        return self.name_len

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


def firstRequest():
    # Implement the header data
    header = RequestHeader(OpCode.LISTFILESOP)
    header.setUserId(125)
    request_header = header.pack_header()

    # Log the request 
    formatted_request = logger.format_hex(request_header, group_size=1)
    print(f"Sending first request:\n{formatted_request}")
    message = header.build_message()
    print(f"User ID: {header.getUserID()}")
    print(f"Op Code: {header.getOpCode()}\n")
    # Return the message to be sent
    return message



    