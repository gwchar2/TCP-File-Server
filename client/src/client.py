import socket
import random
import struct

HOST = "127.0.0.1"  # Server IP address
PORT = 8080  # Port number

# FOR TESTING UNDER THIS !!!
# Random user_id (4 bytes)
user_id = random.randint(0, 0xFFFFFFFF)

# Version (1 byte)
version = 1

# Random name_len (2 bytes), assuming the name length is between 1 and 255
name_len = random.randint(1, 255)

# OpCode (200, BackupFile)
opcode = 200

# File size (4 bytes, which will be 0 as per the request)
file_size = 0

# Create the request header in little-endian format
# The struct format string: 
# 'I' for uint32 (user_id, file_size), 
# 'B' for uint8 (version, opcode),
# 'H' for uint16 (name_len)
request_header = struct.pack('<I B B H I', user_id, version, opcode, name_len, file_size)
# FOR TESTING ABOVE THIS !!!

# Connect to the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    # Print the sending message in hex format for debug
    print(f"Sending: {request_header.hex()}")

    # Send the header data
    s.sendall(request_header) 

    #message = "Hello from Python client!"
    #print(f"Sending: {message}")
    #s.sendall(message.encode())

    # Receive response from the server
    data = s.recv(1024)
    print(f"Received: {data.decode()}")


