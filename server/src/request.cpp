#include "../include/request.hpp"

/* Constructor for a request */
Request::Request(boost::asio::ip::tcp::socket& sock)
    : sock(sock), header(), buffer(MAX_BUFFER) {}


void Request::readHeader() {
    try {
        /* Read the size of the header to the buffer */
        bytes_read = sock.read_some(boost::asio::buffer(buffer.data(), sizeof(header)));

        /* Copy the data in the buffer to the header */ 
        memcpy(&header, buffer.data(), sizeof(header));
        
        /* Log Header */
        log_received_header(header);
        

    } catch (const std::exception& e) {
        std::cerr << "Error reading header: " << e.what() << std::endl;
    }
}

/* Process a request according to the op code*/
void Request::processRequest() {
    // Check the OpCode and process accordingly
    switch (header.op) {
        case OpCode::BACKUP_FILE_OP:
            return processBackupFile();
            break;
        case OpCode::RETRIEVE_FILE_OP:
            return processRetrieveFile();
            break;
        case OpCode::DELETE_FILE_OP:
            return processDeleteFile();
            break;
        case OpCode::LIST_FILES_OP:
            return processListFiles();
            break;
        default:
            std::cerr << "Unknown OpCode received!" << std::endl;
            break;
    }
}

void Request::processBackupFile() {
    try {
        
        /* Read the name of the file */
        bytes_read = sock.read_some(boost::asio::buffer(buffer.data(), header.name_len));  
        std::string file_name(reinterpret_cast<char*>(buffer.data()), static_cast<size_t>(header.name_len));  
        
        /* Log file name */
        log_file_name(file_name);
        
        /* As long as bytes sent < amount of file names, keep sending. we send MAX_BUFFER each time (2048 bytes) */
        size_t bytesReceived = 0;
        while (bytesReceived < header.file_size) {
            size_t chunkSize = std::min(static_cast<size_t>(MAX_BUFFER), header.file_size - bytesReceived);
            chunkSize = sock.read_some(boost::asio::buffer(buffer.data(), chunkSize));
            std::string data(reinterpret_cast<char*>(buffer.data()), static_cast<size_t>(chunkSize)); 
            bytesReceived += chunkSize;
            log_data_received(bytesReceived,header.file_size, data);
        }      
       

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Request::processRetrieveFile() {
    // Implement the logic for RetrieveFile
    std::cout << "Processing RetrieveFile" << std::endl;
}

void Request::processDeleteFile() {
    // Implement the logic for DeleteFile
    std::cout << "Processing DeleteFile" << std::endl;
}

void Request::processListFiles() {

    /* Define the directory path */
    std::filesystem::path dir = std::filesystem::absolute(DIRECTORY) / std::to_string(header.user_id);
    std::cout << "Searching for files in: " << dir << std::endl;
    
    /* We now check if the directory exists */
    if (!check_directory(dir)){
        responseEmptyDirectory(sock);
    }

    /* If it does exist, we make a list of all the files */
    std::vector<std::string> fileList;
    for (const auto& entry: std::filesystem::directory_iterator(dir)){
        if (std::filesystem::is_regular_file(entry)){
            fileList.push_back(entry.path().filename().string());
        }
    }

    /* We need to make the file names into a single string, so we can place it in the buffer */
    std::string fileNames;
    for (const auto& name : fileList){
        fileNames += name + "\n";
    }
    
    /* Create the correct response header, and send it back */
    responseListReturned(sock,fileNames);
}

bool Request::check_directory(std::filesystem::path dir){
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir) || std::filesystem::is_empty(dir)){
            return false;
    }
    return true;
}