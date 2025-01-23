#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "../include/server.hpp"
#include <boost/asio.hpp>
#include <filesystem>

class Response {
    
private:

    boost::asio::ip::tcp::socket& sock;     
    ResponseHeader header;
    std::vector<unsigned char> buffer;                      

public:    
    
    Response(boost::asio::ip::tcp::socket& sock, uint8_t version, ResponseStatus status, uint16_t name_len, uint32_t file_size);    // Constructor to initialize request from a socket  
    const std::vector<unsigned char>& getBuffer() const;                                                                            // Retreives the response buffer
    void setBuffer(const std::string& data);                                                                                        // Sets data into the buffer
    void packHeader();                                                                                                              // Packs header
    void packHeaderWithData(const std::string& data);                                                                               // Packs header with extra data (name)
    ResponseHeader getHeader();                                                                                                     // Retreives header
};

void responseFileRetrieved(boost::asio::ip::tcp::socket& sock, std::filesystem::path filePath, std::string file_name);              // Response 210
void responseListReturned(boost::asio::ip::tcp::socket& sock,std::filesystem::path path,std::string file_name);                     // Response 211
void responseOperationSuccess(boost::asio::ip::tcp::socket& sock, const std::string file_name);                                     // Response 212
void responseFileNotFound(boost::asio::ip::tcp::socket& sock , const std::string file_name);                                        // Response 1001
void responseEmptyDirectory(boost::asio::ip::tcp::socket& sock);                                                                    // Response 1002
void responseGeneralError(boost::asio::ip::tcp::socket& sock,const std::exception& e);                                              // Response 1003
size_t getFileSize(std::ifstream& inFile);                                                                                          // Gets file size
void sendFile(boost::asio::ip::tcp::socket& sock, std::ifstream& inFile, size_t fileSize);                                          // Sends complete file to user




#endif 
