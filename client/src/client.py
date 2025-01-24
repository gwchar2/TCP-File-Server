import socket
import os
import request_handler
import struct
import random
import logging
from request_handler import RequestHeader
from response import Response


# Read the server address and port from server.info
def get_server_info(filename="server.info"):
    with open(filename, "r") as file:
        server_info = file.readline().strip()
        server, port = server_info.split(":")
        return server, int(port)

# Read the list of files to back up from backup.info
def get_backup_files(filename="backup.info"):
    try:
        with open(filename, "r") as file:
            files = [line.strip() for line in file.readlines()]
        print("\nFiles written in backup.info: ")
        for backup_file in files:
            print(f"{backup_file}")
        print("\n")
        return files
    except Exception:
        print("backup.info was not found in directory")
 
# Main function to execute the client logic
def main():
    # Get server info from server.info
    HOST, PORT = get_server_info()
    print(f"Connecting to {HOST} : {PORT}\n")
    user_id = random.randint(0, 0xFFFFFFFF) 

    # Connect to the server
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect((HOST, PORT))
        except: 
            print(f"Error: Server {HOST}:{PORT} is OFFLINE")
            return

    
        # Send request to save backup_files[0] & backup_files[1]
        backup_files = get_backup_files()
        
        # Send request for file list
        request_handler.request_file_list(user_id,s)

        if backup_files is not None:
            try:
                request_handler.request_backup_file(user_id,s,backup_files[0])
                request_handler.request_backup_file(user_id,s,backup_files[1])
            except IndexError:
                print("Error: Not enough file names in backup_file\n")
                
        else:
            print("Skipping second request, backup_file is None\n")

        # Send request for file list
        request_handler.request_file_list(user_id,s)
        if backup_files is not None:
            try:        
                # Send request for backup_files[0] from server
                request_handler.request_file(user_id,s,backup_files[0])
                # Request to delete backup_files[0]
                request_handler.delete_from_server(user_id,s,backup_files[0])
                # Send request for backup_files[0] from server
                request_handler.request_file(user_id,s,backup_files[0])
            except IndexError:
                print("Error: Not enough file names in backup_file\n")

# Execute the main function
if __name__ == "__main__":
    main()
