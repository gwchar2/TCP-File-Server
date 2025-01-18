#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../include/protocol.hpp" 
#include "../include/server.hpp"
#include "../include/communication.hpp"
#include "../include/logger.hpp"
#include "../include/response.hpp"

#include <filesystem>


class Request {
    
private:

    boost::asio::ip::tcp::socket& sock;     // Socket to receive data
    RequestHeader header;
    std::vector<unsigned char> buffer;      // Holds the data we read
    size_t bytes_read = 0;                  // The amount of bytes we are currently reading

public:    

    Request(boost::asio::ip::tcp::socket& sock);    // Constructor to initialize request from a socket  
    void readHeader();          // Function to read the request header from the socket
    void processRequest();      // Function to process the request based on OpCode
    void processBackupFile();   // Process BackupFile OP
    void processRetrieveFile(); // Process RetrieveFile OP
    void processDeleteFile(); // Process DeleteFile OP
    void processListFiles();  // Process ListFiles OP

};

#endif 
