
# Makefile for C++ Server only

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g 
LDFLAGS = -lpthread -lws2_32
SRC_DIR = server/src
INCLUDE_DIR = server/include
BUILD_DIR = server/build

# Server source files
SERVER_SRC = $(SRC_DIR)/main.cpp \
             $(SRC_DIR)/server.cpp \
			 $(SRC_DIR)/request.cpp \
             # add the files when I need them: \
             $(SRC_DIR)/communication.cpp \
             $(SRC_DIR)/file_manager.cpp \
             $(SRC_DIR)/protocol.cpp

# Server object files
SERVER_OBJ =  $(SERVER_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Output executable
SERVER_EXEC = server.exe

# Default target
all: $(SERVER_EXEC)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilation rule for server-side code
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Link the server object files into the final executable
$(SERVER_EXEC): $(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) $(SERVER_OBJ) -o $(SERVER_EXEC) $(LDFLAGS)

# Clean up the build
clean:
	rm -rf $(BUILD_DIR)/*.o $(SERVER_EXEC)

# Rebuild everything from scratch
rebuild: clean all

# Run the server
run: $(SERVER_EXEC)
	./$(SERVER_EXEC)

# Phony targets
.PHONY: all clean rebuild run
