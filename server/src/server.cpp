#include "../include/server.hpp"

Server::Server(int port): io_context(),acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {}

/* Starts the server , waits to receive a connection -> makes a new thread */
void Server::start() {
    log_header("Server started, waiting for client connections...");
    while (true) {
        try {
            tcp::socket sock(io_context);

            /* Accept a client connection */
            acceptor.accept(sock);
            log_header("Client Connected");

            /* Create a new thread to handle the client communication */
            std::thread(&Server::handle_client, this, std::move(sock)).detach();
            
        } catch (const std::exception& e) {
            std::cerr << "Error accepting connection: " << e.what() << std::endl;
        }
    }
}

/* Handles the user interaction with server, reads header and processes requests. */
void Server::handle_client(tcp::socket sock) {
    while (sock.is_open()){
        try {
            /* Create a new request & Response*/
            Request request(sock);

            /* Read the header */
            request.readHeader();

            /* Process the request */
            request.processRequest();

        } catch (const boost::system::system_error& e) {
            if (e.code() == boost::asio::error::eof) 
                std::cerr << "\nClient closed connection.\n" << std::endl;
            sock.close();
            break;  
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl; 
        }
    }
}
