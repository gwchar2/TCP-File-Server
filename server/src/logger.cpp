#include "../include/logger.hpp"



void formatted_hexa(const unsigned char* data, size_t length) {
    // Loop through the data in chunks of 16 bytes
    for (size_t i = 0; i < length; i += BYTES_PER_LINE) {
        // Print hex values
        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            if (i + j < length) {
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                    << static_cast<int>(data[i + j]) << " ";
            } else {
                std::cout << "  ";  // Padding for incomplete rows
            }
        }

        // Print ASCII representation
        std::cout << " | ";
        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            if (i + j < length) {
                unsigned char byte = data[i + j];
                std::cout << (std::isprint(byte) ? static_cast<char>(byte) : '.');
            } else {
                std::cout << " ";  // Padding for incomplete rows
            }
        }

        std::cout << std::endl; // Finish a line
    }
}


void log_header(const std::string& msg) {
    std::time_t now = std::time(nullptr);
    std::tm* tm_now = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(tm_now, "%Y-%m-%d %H:%M:%S") << " - " << msg;
    std::cout << "\n===== " << oss.str() << " =====\n";
}

void log_received_header(const RequestHeader& header) {
    log_header("Header received");

    std::cout << "User ID: " << std::dec << header.user_id << std::endl;
    std::cout << "Version: " << std::dec << (int)header.version << std::endl;
    std::cout << "Op Code: " << (int)header.op << std::endl;
    std::cout << "Filename Length: " << header.name_len << std::endl;
    std::cout << "File Size: " << header.file_size << " bytes" << std::endl;  
    formatted_hexa(reinterpret_cast<const unsigned char*>(&header), sizeof(header));
}

void log_file_name(const std::string& file_name) {
    log_header("File Name received");
    std::cout << "File Name: " << file_name << std::endl;
    formatted_hexa(reinterpret_cast<const unsigned char*>(file_name.data()), sizeof(file_name));
}

void log_processing_request(const std::string& request_type) {
    log_header("Processing request");
    std::cout << "Request Type: " << request_type << std::endl;
}

void log_response_header(const ResponseHeader& header) {
    log_header("Header sent");

    std::cout << "Version: " << std::dec << (int)header.version << std::endl;
    std::cout << "Status Code: " << std::dec << (int)header.status << std::endl;
    std::cout << "Filename Length: " << header.name_len << " bytes" << std::endl;
    std::cout << "Data Size: " << header.file_size << " bytes" << std::endl;  
    formatted_hexa(reinterpret_cast<const unsigned char*>(&header), sizeof(header));
}

void log_response_sent(const std::string& response) {
    log_header("Response sent to client");
    std::cout << response << std::endl;
    formatted_hexa(reinterpret_cast<const unsigned char*>(response.data()), response.size());
}