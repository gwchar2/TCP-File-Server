#include "../include/server.hpp"

Server::Server(int port): io_context(),acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {}

void Server::start() {
    log_header("Server started, waiting for client connections...");
    while (true) {
        tcp::socket sock(io_context);
        try {
            /* Accept a client connection */
            acceptor.accept(sock);
            log_header("Client connected");

            /* Create a new thread to handle the client communication */
            std::thread(&Server::handle_client, this, std::move(sock)).detach();
            
        } catch (const std::exception& e) {
            std::cerr << "Error accepting connection: " << e.what() << std::endl;
        }
    }
}

void Server::handle_client(tcp::socket sock) {
    try {
        
        /* Create a new request & Response*/
        Request request(sock);
        //Response responsee;

        /* Read the header */
        request.readHeader();

        /* Process the request */
        request.processRequest();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
