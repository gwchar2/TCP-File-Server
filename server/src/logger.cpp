#include "../include/logger.hpp"

/* Prints the binary data received from user, as hexa, and formatted */
void formatted_hexa(const unsigned char* data, size_t length) {
    for (size_t i = 0; i < length; i += BYTES_PER_LINE) {
        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            if (i + j < length) {
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                          << static_cast<int>(data[i + j]) << " ";
            } else std::cout << "   ";  
        }

        /* Prints the text of the message. If there is no ascii representation, prints '.' */
        std::cout << " | ";
        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            if (i + j < length) {
                unsigned char byte = data[i + j];
                std::cout << (std::isprint(byte) ? static_cast<char>(byte) : '.');
            } else std::cout << " ";
        }
        std::cout << std::endl; 
    }
}

/* Logs the header for specific message. (custom per message) */
void log_header(const std::string& msg) {
    std::time_t now = std::time(nullptr);           
    std::tm* tm_now = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(tm_now, "%Y-%m-%d %H:%M:%S") << " - " << msg;
    std::cout << "\n===== " << oss.str() << " =====\n";
}

/* Logs the header received from user - according to its fields. */
void log_received_header(const RequestHeader& header) {
    log_header("Header received from client");
    std::cout << "User ID: " << std::dec << header.user_id << std::endl;
    std::cout << "Version: " << std::dec << (int)header.version << std::endl;
    std::cout << "Op Code: " << (int)header.op << std::endl;
    std::cout << "Filename Length: " << header.name_len << std::endl;
    std::cout << "File Size: " << header.file_size << " bytes" << std::endl;  
    formatted_hexa(reinterpret_cast<const unsigned char*>(&header), sizeof(header));
}

/* Logs the file name received from user */
void log_file_name(const std::string& file_name) {
    log_header("File Name received from client");
    std::cout << "File Name: " << file_name << std::endl;
    formatted_hexa(reinterpret_cast<const unsigned char*>(file_name.data()), file_name.size());
}

/* Logs the data received from user. Prints the data on screen */
void log_data_received(size_t bytesReceived, size_t file_size, const std::string& data){
    std::string header = "Received " + std::to_string(bytesReceived) + "/" + (std::to_string)(file_size) + " Bytes";
    log_header(header);
    if (data.size() < 2048 ) formatted_hexa(reinterpret_cast<const unsigned char*>(data.data()), data.size());
}

/* Logs the header sent back to user according to its fields */
void log_response_header(const ResponseHeader& header) {
    log_header("Header sent to client");
    std::cout << "Version: " << std::dec << (int)header.version << std::endl;
    std::cout << "Status Code: " << std::dec << (int)header.status << std::endl;
    std::cout << "Filename Length: " << header.name_len << " bytes" << std::endl;
    std::cout << "Data Size: " << header.file_size << " bytes" << std::endl;  
    formatted_hexa(reinterpret_cast<const unsigned char*>(&header), sizeof(header));
}

/* Logs the response sent to user (data or file name etc) as formatted hexa */
void log_response_sent(const std::string& response) {
    log_header("Response sent to client");
    if (response.size() < 2000){
        std::cout << response << std::endl;
        formatted_hexa(reinterpret_cast<const unsigned char*>(response.data()), response.size());
    }
}