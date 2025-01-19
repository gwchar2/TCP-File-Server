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
    buffer.resize(sizeof(ResponseHeader));  
    std::memcpy(buffer.data(), &header, sizeof(header));
}

ResponseHeader Response::getHeader(){
    return header;
}

/* Creates a response for Status Code EMPTY_DIRECTORY */
void responseEmptyDirectory(boost::asio::ip::tcp::socket& sock) {
    Response response(sock, response.getHeader().version, ResponseStatus::EMPTY_DIRECTORY, 0, 0);
    response.packHeader();
    boost::asio::write(sock, boost::asio::buffer(response.getBuffer()));
    log_response_header(response.getHeader());
    const char* responseMessage = "No such directory!";
    boost::asio::write(sock, boost::asio::buffer(responseMessage, std::strlen(responseMessage)));
}

/* Creates a response for Status Code LIST_RETURNED */
void responseListReturned(boost::asio::ip::tcp::socket& sock, const std::string& data){
    Response response(sock,header.version, ResponseStatus::LIST_RETURNED, header.name_len, fileNames.size());
    response.packHeader();
    boost::asio::write(sock, boost::asio::buffer(response.getBuffer()));
    log_response_header(response.getHeader());

    /* As long as bytes sent < amount of file names, keep sending. we send MAX_BUFFER each time (2048 bytes) */
    size_t bytesSent = 0;
    while (bytesSent < fileNames.size()) {
        size_t chunkSize = std::min(static_cast<size_t>(MAX_BUFFER), fileNames.size() - bytesSent);
        std::string chunk = fileNames.substr(bytesSent, chunkSize);
        
        boost::asio::write(sock, boost::asio::buffer(chunk));
        bytesSent += chunkSize;
        log_response_sent(chunk);
    }  
}