#include "../include/server.hpp"

int main() {
    int port = 8080;  // Port number

    // Create the server object and start it
    Server server(port);
    server.start();  // Start the server

    return 0;
}