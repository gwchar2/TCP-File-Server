#include "../include/server.hpp"
#include <iostream>

Server::Server(int port): io_context(),acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {}

void Server::start() {
    std::cout << "Server started, waiting for client connections...\n";
    while (true) {
        tcp::socket sock(io_context);
        try {
            // Accept a client connection
            acceptor.accept(sock);
            std::cout << "Client connected!\n";

            // Create a new thread to handle the client communication
            std::thread(&Server::handle_client, this, std::move(sock)).detach();  // Detached thread
        } catch (const std::exception& e) {
            std::cerr << "Error accepting connection: " << e.what() << std::endl;
        }
    }
}

void Server::handle_client(tcp::socket sock) {
    const int max_Length = 1024;  // Max length for received data
    char data[max_Length];

    try {
        // Read the data from the client
        size_t length = sock.read_some(boost::asio::buffer(data, max_Length));
        data[length] = '\0';  // Null-terminate the received data
        std::cout << "Received message: " << data << std::endl;

        // Send a response back to the client
        const char* response = "Message received";
        boost::asio::write(sock, boost::asio::buffer(response, strlen(response)));
        std::cout << "Response sent back to client.\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
