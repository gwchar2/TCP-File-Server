# File Backup Server (TCP)

This repository contains the implementation of a server-client system. The server is written in C++ and the client in Python. Below is an overview of the project structure and its components.

---

## Components

### **Server (C++)**
- **Source files**: Implements the core server functionality:
  - `main.cpp`: Entry point of the server.
  - `server.cpp`: Contains the main server logic.
  - `request.cpp`: Handles various client requests like save, retrieve, and delete.
  - `response.cpp`: Handles various responses from the server to a client.
  - `logger.cpp`: Handles preety printing requests and responses.

- **Headers**: Contains declarations corresponding to the source files.
  - `protocol.hpp`: Contains declerations for main server protocol settings.
  - `server.hpp`: Contains declarations for socket related functions.
  - `request.hpp`: Contains declarations for the Request class.
  - `response.hpp`: Contains declarations for the Response class.
  - `logger.hpp`: Contains declarations for preety printing functions.
  -
- **Build Configuration**: The `makefile.txt` file provides configuration for building the server.

### **Client (Python)**
- **Source files**: Implements the client-side logic:
  - `client.py`: Main logic of client to server communication.
  - `request_handler.py`: Contains the implementations for Request class.
  - `response.py`: Contains the implementations for Response class.
  - `logger.py`: Contains a function for preety printing.

---

## How to Build and Run
Note: This must be done with 2 seperate terminals, one for the client, and one for the server.

### **Server**
1. Navigate to the main directory

2. Use CMake to build the server:
    ```bash
    makefile
    ```
3. Run the server
    ```bash
    ./server
    ```
### **Client**
1. Navigate to the client directory
   ```bash
   cd client/src
   ```
2. Run the client
    ```bash
    python client.py
    ```
---

## Project Structure

```plaintext
/maman14
│
├── /server                     # C++ server-side code
│   ├── /src                    # C++ source files
│   │   ├── main.cpp            # Main entry point of the server
│   │   ├── server.cpp          # Server logic
│   │   ├── request.cpp         # Handles requests (e.g., save, retrieve, delete)
│   │   ├── logger.cpp          # Log handling (e.g., prints to terminal)
│   │   └── protocol.cpp        # Protocol logic (e.g., binary protocol parsing)
│   ├── /include                # C++ header files
│   │   ├── server.hpp          # Declarations for server
│   │   ├── request.hpp         # Declarations for request handling
│   │   ├── response.hpp        # Declarations for response handling
│   │   ├── logger.hpp          # Declarations for logger
│   │   └── protocol.hpp        # Declarations for protocol logic
│   │  
│   └── /build                  # Build directory (output of compilation)
│      
│
├── /client                     # Python client-side code
│   ├── /src                    # Python source files
│       ├── server.info         # Holds the IP:PORT for connection
│       ├── backup.info         # Includes the file names for backup
│       ├── client.py           # Python client entry point
│       ├── request_handler.py  # Handles the requests sent to server
│       ├── response.py         # Handles the responses received from server
│       └── logger.py           # Logs the information received in hexa...   
│
├── /docs                       # Documentation (optional)
│   └── project_overview.md     # Overview of the project, protocol, etc.
│
├── makefile.txt                # Builds the server
└── README.md                   # Project description and instructions
```
