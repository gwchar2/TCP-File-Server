#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <thread>  // For creating new threads

using boost::asio::ip::tcp;

class Server {
public:

    Server(int port);
    void start();

private:
    // Function to handle communication with a client
    void handle_client(tcp::socket sock);

    boost::asio::io_context io_context;
    tcp::acceptor acceptor;
};

#endif // SERVER_HPP
