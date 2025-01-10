#include "../include/server.hpp"
#include "../include/protocol.hpp"
#include "../include/request.hpp"


Server::Server(int port): io_context(),acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {}

void Server::start() {
    std::cout << "Server started, waiting for client connections...\n";
    while (true) {
        tcp::socket sock(io_context);
        try {
            /* Accept a client connection */
            acceptor.accept(sock);
            std::cout << "Client connected!\n";

            /* Create a new thread to handle the client communication */
            std::thread(&Server::handle_client, this, std::move(sock)).detach();  // Detach thread
        } catch (const std::exception& e) {
            std::cerr << "Error accepting connection: " << e.what() << std::endl;
        }
    }
}

void Server::handle_client(tcp::socket sock) {
    try {
        
        /* Create a new request */
        Request request(sock);

        /* Read the header */
        request.readHeader();

        /* Process the request according to the header */
        request.processRequest();



        // Send a response back to the client
        const char* response = "Message received";
        boost::asio::write(sock, boost::asio::buffer(response, strlen(response)));
        std::cout << "Response sent back to client.\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
