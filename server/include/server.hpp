#ifndef SERVER_HPP
#define SERVER_HPP

#include "../include/protocol.hpp"
#include "../include/request.hpp"
#include "../include/logger.hpp"
#include "../include/response.hpp"
#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <thread> 
#include <string>


#define DIRECTORY "server/backupsvr"

using boost::asio::ip::tcp;

class Server {
public:

    Server(int port);
    void start();

private:
    // Function to handle communication with a client
    void handle_client(tcp::socket sock);
    void logger(const std::vector<unsigned char>& data, const std::string& direction);

    boost::asio::io_context io_context;
    tcp::acceptor acceptor;
};

#endif
