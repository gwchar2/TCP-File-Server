#ifndef SERVER_HPP
#define SERVER_HPP

#include "../include/protocol.hpp"
#include "../include/request.hpp"
#include "../include/logger.hpp"
#include "../include/response.hpp"
#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/error.hpp>
#include <fstream>
#include <iostream>
#include <thread> 
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cstdint>
#include <vector>
#include <filesystem>
#include <random>


#define DIRECTORY "server/backupsvr"                                                        // Server backup directory

using boost::asio::ip::tcp;

class Server {
public:

    Server(int port);
    void start();

private:
    
    void handle_client(tcp::socket sock);                                                   // Handles communication with client
    void logger(const std::vector<unsigned char>& data, const std::string& direction);      // Logs on client

    boost::asio::io_context io_context;                                                     // io context
    tcp::acceptor acceptor;                                                                 // boost tcp acceptor
};

#endif
