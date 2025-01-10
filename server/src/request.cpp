#include "../include/request.hpp"
#include "../include/server.hpp"

/* Constructor for a request */
Request::Request(boost::asio::ip::tcp::socket& sock)
    : sock(sock), header() {}


void Request::readHeader() {
    try {
        /* Read the size of the header */
        boost::asio::read(sock, boost::asio::buffer(&header, sizeof(RequestHeader)));

         /* Convert fields to host byte order. We do not convert OP field since it is to small! */
        header.user_id = ntohl(header.user_id);  
        header.version = ntohs(header.version); 
        header.name_len = ntohs(header.name_len); 
        header.file_size = ntohl(header.file_size);  

        /* Print Header */
        std::cout << "Header received:\n";
        std::cout << "User ID: " << header.user_id << "\n";
        std::cout << "Version: " << static_cast<int>(header.version) << "\n";
        std::cout << "Op Code: " << static_cast<int>(header.op) << "\n";
        std::cout << "Filename Length: " << header.name_len << "\n";
        std::cout << "File Size: " << header.file_size << " bytes\n";


    } catch (const std::exception& e) {
        std::cerr << "Error reading header: " << e.what() << std::endl;
    }
}

/* Process a request according to the op code*/
void Request::processRequest() {
    // Check the OpCode and process accordingly
    switch (header.op) {
        case OpCode::BackupFileOp:
            processBackupFile();
            break;
        case OpCode::RetrieveFileOp:
            processRetrieveFile();
            break;
        case OpCode::DeleteFileOp:
            processDeleteFile();
            break;
        case OpCode::ListFilesOp:
            processListFiles();
            break;
        default:
            std::cerr << "Unknown OpCode received!" << std::endl;
            break;
    }
}

void Request::processBackupFile() {
    try {
        /* Read the filename based on name_len */ 
        std::vector<char> filename_buffer(header.name_len);
        boost::asio::read(sock, boost::asio::buffer(filename_buffer.data(), header.name_len));
        std::string filename(filename_buffer.begin(), filename_buffer.end());
        std::cout << "Filename: " << filename << "\n";

        /* Read the file payload based on file_size */
        std::ofstream output_file(filename, std::ios::binary);
        if (!output_file.is_open()) {
            throw std::runtime_error("Failed to open file for writing");
        }

        /* Initialize buffer for receiving the file in chunks */
        const size_t buffer_size = 8192; 
        std::vector<char> buffer(buffer_size);
        size_t bytes_remaining = header.file_size;

        /* While we still have bytes to read, read them. */
        while (bytes_remaining > 0) {
            size_t bytes_to_read = std::min(buffer_size, bytes_remaining);      // Bytes to read is the minimum between the two options (max or file_size)
            size_t bytes_read = sock.read_some(boost::asio::buffer(buffer.data(), bytes_to_read));
            output_file.write(buffer.data(), bytes_read);
            bytes_remaining -= bytes_read;
        }

        std::cout << "File transfer completed.\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    std::cout << "Processing BackupFile" << std::endl;
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
    // Implement the logic for ListFiles
    std::cout << "Processing ListFiles" << std::endl;
}