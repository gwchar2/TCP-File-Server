import struct
import os 
from enum import Enum

class Response(Enum):
    FILES_RETREIVED = 210,
    LIST_RETURNED = 211,
    OPERATION_SUCCESS = 212,
    FILE_NOT_FOUND = 1001,
    EMPTY_DIRECTORY = 1002,
    GENERAL_ERROR = 1003


class ResponseHeader:
    
