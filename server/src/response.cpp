#include "../include/response.hpp"


/* Constructor for a response */
Response::Response(boost::asio::ip::tcp::socket& sock, uint8_t version, ResponseStatus status, uint16_t name_len, uint32_t file_size) : sock(sock), header(), buffer(MAX_BUFFER) {
    header.version = version;
    header.status = status;
    header.name_len = name_len;
    header.file_size = file_size;
}

const std::vector<unsigned char>& Response::getBuffer() const {
    return buffer;
}

void Response::setBuffer(const std::string& data) {
    buffer.clear();
    buffer.resize(data.size());
    std::memcpy(buffer.data(), data.c_str(), data.size());
}

void Response::packHeader() {
    buffer.clear();
    buffer.resize(sizeof(header));  
    std::memcpy(buffer.data(), &header, sizeof(header));
}

void Response::packHeaderWithData(const std::string& data){
    buffer.clear();
    buffer.resize(sizeof(header)+data.size());
    std::memcpy(buffer.data(),&header, sizeof(header));
    std::memcpy(buffer.data()+sizeof(header),data.data(), data.size());
}

ResponseHeader Response::getHeader(){
    return header;
}
/* Creates a response for Status Code FILE_RETRIVED 210 */
void responseFileRetrieved(boost::asio::ip::tcp::socket& sock){

}

/* Creates a response for Status Code LIST_RETURNED 211 */
void responseListReturned(boost::asio::ip::tcp::socket& sock, std::filesystem::path filePath, std::string file_name){
    /* Open the file in binary */
    std::ifstream inFile(filePath, std::ios::binary);
    size_t fileSize = getFileSize(inFile);

    /* We send the header */
    Response response(sock,1, ResponseStatus::LIST_RETURNED, file_name.size(), fileSize);
    response.packHeaderWithData(file_name);
    boost::asio::write(sock, boost::asio::buffer(response.getBuffer()));
    log_response_header(response.getHeader());
    
    /* As long as bytes sent < amount of file names, keep sending. we send MAX_BUFFER each time (2048 bytes) */
    std::vector<char> buffer(MAX_BUFFER);
    size_t bytesSent = 0;
    while (bytesSent < fileSize) {
        /* Set the chunk size */
        size_t chunkSize = std::min(static_cast<size_t>(MAX_BUFFER),fileSize - bytesSent);
        
        /* Read the next chunk from the file */
        inFile.read(buffer.data(),chunkSize);
        size_t bytesRead = static_cast<size_t>(inFile.gcount());
        
        /* We send the chunk & log it */
        boost::asio::write(sock, boost::asio::buffer(buffer.data(), bytesRead));
        bytesSent += bytesRead;
        log_response_sent(std::string(buffer.data(), bytesRead));
    }  
}

/* Creates a response for Status Code OPERATION_SUCCESS 212 */
void responseOperationSuccess(boost::asio::ip::tcp::socket& sock,const std::string file_name){
    Response response(sock,1, ResponseStatus::OPERATION_SUCCESS, file_name.size(), 0);
    response.packHeaderWithData(file_name);
    boost::asio::write(sock, boost::asio::buffer(response.getBuffer()));
    log_response_header(response.getHeader());
}

/* Creates a response for Status Code FILE_NOT_FOUND 1001 */
void responseFileNotFound(boost::asio::ip::tcp::socket& sock,const std::string file_name){
    Response response(sock,1, ResponseStatus::FILE_NOT_FOUND, file_name.size(), 0);
    response.packHeaderWithData(file_name);
    boost::asio::write(sock, boost::asio::buffer(response.getBuffer()));
    log_response_header(response.getHeader());

}

/* Creates a response for Status Code EMPTY_DIRECTORY 1002 */
void responseEmptyDirectory(boost::asio::ip::tcp::socket& sock) {
    Response response(sock, response.getHeader().version, ResponseStatus::EMPTY_DIRECTORY, 0, 0);
    response.packHeader();
    boost::asio::write(sock, boost::asio::buffer(response.getBuffer()));
    log_response_header(response.getHeader());
}

/* Creates a response for Status Code FILE_NOT_FOUND 1003 */
void responseGeneralError(boost::asio::ip::tcp::socket& sock){

}

size_t getFileSize(std::ifstream& inFile){
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file " << std::endl;
        return 0;
    }
    inFile.seekg(0, std::ios::end);
    size_t fileSize = static_cast<size_t>(inFile.tellg());
    inFile.seekg(0, std::ios::beg);
    return fileSize;
}

