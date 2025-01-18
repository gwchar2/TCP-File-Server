# Maman14 Project

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

- **Build Configuration**: The `CMakeLists.txt` file provides configuration for building the server.

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

### **Server**
1. Navigate to the server's build directory:
   ```bash
   cd server/build
   ```
2. Use CMake to build the server:
    ```bash
    makefile
    ```
3. Run the server
    ```bash
    ./server
    ```

4. Run the client
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
│   │   ├── communication.cpp   # Handles networking (e.g., TCP communication)
│   │   ├── logger.cpp          # Log handling (e.g., prints to terminal)
│   │   └── protocol.cpp        # Protocol logic (e.g., binary protocol parsing)
│   ├── /include                # C++ header files
│   │   ├── server.h            # Declarations for server
│   │   ├── request.h           # Declarations for request handling
│   │   ├── communication.h     # Declarations for communication
│   │   ├── logger.h            # Declarations for logger
│   │   └── protocol.h          # Declarations for protocol logic
│   ├── /build                  # Build directory (output of compilation)
│   │   └── CMakeLists.txt      # CMake configuration for building the server
│   ├── /assets                 # Optional: store sample files or configuration files
│   │   └── sample_files/       # Sample files for testing or examples
│   └── /tests                  # C++ test cases for unit tests (optional)
│       ├── test_server.cpp     # Tests for the server logic
│       └── test_communication.cpp # Tests for communication logic
│
├── /client                     # Python client-side code
│   ├── /src                    # Python source files
│   │   ├── client.py           # Python client entry point
│   │   └── client_helpers.py   # Helper functions for client communication
│   ├── /tests                  # Python test cases (optional)
│   │   ├── test_client.py      # Tests for client-side logic
│   └── /assets                 # Optional: assets for testing or configuration
│
├── /docs                       # Documentation (optional)
│   └── project_overview.md     # Overview of the project, protocol, etc.
│
├── /scripts                    # Miscellaneous scripts (e.g., build scripts)
│   ├── build.sh                # Build script (if applicable for server)
│   └── run_tests.sh            # Run tests script (if needed for both C++ and Python)
│
└── README.md                   # Project description and instructions
```