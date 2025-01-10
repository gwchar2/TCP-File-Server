#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include "../include/protocol.hpp"  // Assuming RequestHeader is in a separate header
#include "../include/server.hpp"

class Request {
public:    
// Constructor to initialize request from a socket
    Request(boost::asio::ip::tcp::socket& sock);

    // Function to read the request header from the socket
    void readHeader();

    // Function to process the request based on OpCode
    void processRequest();

    // Functions to process data for each OpCode
    void processBackupFile();
    void processRetrieveFile();
    void processDeleteFile();
    void processListFiles();
    void processRequest(tcp::socket& sock, const RequestHeader& request); 
    void readFile(tcp::socket& sock, const RequestHeader& request);

private:
    boost::asio::ip::tcp::socket& sock;  // Socket to receive data
    RequestHeader header;         // Store the request header

    // Helper function to read the data into the request header
    void readData(char* buffer, size_t size);
};

#endif 
