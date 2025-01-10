import socket

HOST = "127.0.0.1"  # Server IP address
PORT = 8080  # Port number

# Connect to the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    message = "Hello from Python client!"
    print(f"Sending: {message}")
    s.sendall(message.encode())

    # Receive response from the server
    data = s.recv(1024)
    print(f"Received: {data.decode()}")


