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


void Response::setBytesSent(size_t bytes){
    bytes_sent = bytes;
}

size_t Response::getBytesSent(){
    return bytes_sent;
}

ResponseHeader Response::getHeader(){
    return header;
}