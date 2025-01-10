/maman14
│
├── /server                     # C++ server-side code
│   ├── /src                    # C++ source files
│   │   ├── main.cpp            # Main entry point of the server
│   │   ├── server.cpp          # Server logic
│   │   ├── request_handler.cpp # Handles requests (e.g., save, retrieve, delete)
│   │   ├── communication.cpp   # Handles networking (e.g., TCP communication)
│   │   ├── file_manager.cpp    # File handling (e.g., file read/write)
│   │   └── protocol.cpp        # Protocol logic (e.g., binary protocol parsing)
│   ├── /include                # C++ header files
│   │   ├── server.h            # Declarations for server
│   │   ├── request_handler.h   # Declarations for request handling
│   │   ├── communication.h     # Declarations for communication
│   │   ├── file_manager.h      # Declarations for file management
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
