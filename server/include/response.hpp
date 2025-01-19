#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "../include/protocol.hpp" 
#include "../include/server.hpp"
#include "../include/communication.hpp"

class Response {
    
private:

    boost::asio::ip::tcp::socket& sock;     
    ResponseHeader header;
    std::vector<unsigned char> buffer;                      

public:    
    
    Response(boost::asio::ip::tcp::socket& sock, uint8_t version, ResponseStatus status, uint16_t name_len, uint32_t file_size);    // Constructor to initialize request from a socket  
    const std::vector<unsigned char>& getBuffer() const;
    void setBuffer(const std::string& data);
    void packHeader();
    ResponseHeader getHeader();
    void responseFilesReceived();
    void responseListReturned();
    void responseOperationSuccess();
    void responseFileNotFound();
    void responseGeneralError();
};

void responseEmptyDirectory(boost::asio::ip::tcp::socket& sock);
void responseListReturned(boost::asio::ip::tcp::socket& sock, cons std::string& data);





#endif 
