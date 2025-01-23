# File Backup Server (TCP)

This repository contains the implementation of a server-client system. The server is written in C++ and the client in Python. Below is an overview of the project structure and its components.

---

## Components

### **Server (C++)**
- **Source files**: Implements the core server functionality:
  - `main.cpp`: Entry point of the server.
  - `server.cpp`: Contains the main server logic.
  - `request_handler.cpp`: Handles various client requests like save, retrieve, and delete.
  - `communication.cpp`: Manages networking and TCP communication.
  - `file_manager.cpp`: Handles file I/O operations for persistent storage.
  - `protocol.cpp`: Implements the binary protocol used for communication.

- **Headers**: Contains declarations corresponding to the source files.

- **Tests**: Optional test cases located in `/server/tests`.

- **Build Configuration**: The `makefile.txt` file provides configuration for building the server.

### **Client (Python)**
- **Source files**: Implements the client-side logic:
  - `client.py`: Entry point for the client application.
  - `client_helpers.py`: Contains helper functions for communication with the server.

- **Tests**: Optional test cases located in `/client/tests`.

- **Assets**: Contains any optional assets needed for testing or configuration.

### **Documentation**
- All project documentation is in the `/docs` directory.
- Includes files like `project_overview.md` for detailed explanations of the project structure, communication protocol, etc.

### **Scripts**
- The `/scripts` directory contains utility scripts:
  - `build.sh`: Builds the server using the configuration in `/server/build`.
  - `run_tests.sh`: Runs all tests for both the server and client.

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
4. Navigate to the client directory
   ```bash
   cd client/src
   ```
5. Run the client
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
