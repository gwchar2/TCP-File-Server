#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../include/server.hpp"
#include <boost/asio.hpp>
#include <filesystem>

#define OVR 1
#define APP 2

class Request {
    
private:

    boost::asio::ip::tcp::socket& sock;                                                     // Socket to receive data
    RequestHeader header;
    std::vector<unsigned char> buffer;                                                      // Holds the data we read
    size_t bytes_read = 0;                                                                  // The amount of bytes we are currently reading

public:    

    Request(boost::asio::ip::tcp::socket& sock);                                            // Constructor to initialize request from a socket  
    void readHeader();                                                                      // Function to read the request header from the socket
    RequestHeader getHeader();
    void processRequest();                                                                  // Function to process the request based on OpCode
    void processBackupFile();                                                               // Process BackupFile OP
    void processRetrieveFile();                                                             // Process RetrieveFile OP
    void processDeleteFile();                                                               // Process DeleteFile OP
    void processListFiles();                                                                // Process ListFiles OP
    bool check_directory(std::filesystem::path dir);                                        // Checks if the directory exists
    std::tuple<std::string, std::filesystem::path> getFileNameAndDirectory();               // Returns the name of a file and the directory path
};

void saveToFile(const std::filesystem::path& file_path, const std::string& data,int status);        // Saves data to a file
std::string generateRandomString(size_t length);                                                    // Generates a random string 32 characters long

#endif 
