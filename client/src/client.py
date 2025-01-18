import socket
import os
import request_handler
import struct
from request_handler import RequestHeader


# Read the server address and port from server.info
def get_server_info(filename="server.info"):
    with open(filename, "r") as file:
        server_info = file.readline().strip()
        server, port = server_info.split(":")
        return server, int(port)

# Read the list of files to back up from backup.info
def get_backup_files(filename="backup.info"):
    with open(filename, "r") as file:
        files = [line.strip() for line in file.readlines()]
    print("Files written in backup.info: ")
    for backup_file in files:
        print(f"{backup_file}")
    print("\n")
    return files

def receive_all(sock, size):
    # Helper function to receive exactly 'size' bytes
    data = bytearray()
    while len(data) < size:
        packet = sock.recv(size - len(data))
        if not packet:
            raise ConnectionError("Connection closed")
        data.extend(packet)
    return data

# Main function to execute the client logic
def main():

    # Get server info from server.info
    HOST, PORT = get_server_info()
    print(f"Connecting to {HOST} : {PORT}\n")

    # Get the list of files to back up from backup.info
    backup_files = get_backup_files()

    # Connect to the server
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))

        # Send request
        request = request_handler.firstRequest()
        s.sendall(request)

        # First receive and parse the header
        header_size = struct.calcsize('I B B I')  # Adjust based on your header structure
        header_data = receive_all(s, header_size)
        total_size, version, status, data_size = struct.unpack('I B B I', header_data)

        print(f"Expecting {data_size} bytes of data")

        # Now receive all the data
        received_data = bytearray()
        while len(received_data) < data_size:
            remaining = data_size - len(received_data)
            chunk_size = min(2048, remaining)
            
            chunk = receive_all(s, chunk_size)
            received_data.extend(chunk)
            
            print(f"Received {len(received_data)} of {data_size} bytes")

        # Try to decode the complete data
        try:
            decoded_data = received_data.decode('utf-8')
            print("Files found:")
            print(decoded_data)
        except UnicodeDecodeError:
            print(f"Raw data (hex): {received_data.hex()}")

# Execute the main function
if __name__ == "__main__":
    main()
