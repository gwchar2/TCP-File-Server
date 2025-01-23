#include "../include/request.hpp"

/* Constructor for a request */
Request::Request(boost::asio::ip::tcp::socket& sock)
    : sock(sock), header(), buffer(MAX_BUFFER) {}

/* Retreives header */
RequestHeader Request::getHeader(){
    return header;
}

/* Reads the header received from user */
void Request::readHeader() {
    try {
        /* Read the size of the header to the buffer */
        bytes_read = sock.read_some(boost::asio::buffer(buffer.data(), sizeof(header)));

        /* Copy the data in the buffer to the header */ 
        memcpy(&header, buffer.data(), sizeof(header));
        
        /* Log Header */
        log_received_header(header);

    } catch (const boost::system::system_error& e) {
        throw;
    } catch (const std::exception& e){
        throw;
    }
}

/* Process a request according to the op code*/
void Request::processRequest() {
    /* Check the OpCode and process accordingly */
    switch (header.op) {
        case OpCode::BACKUP_FILE_OP:
            processBackupFile();
            break;
        case OpCode::RETRIEVE_FILE_OP:
            processRetrieveFile();
            break;
        case OpCode::DELETE_FILE_OP:
            processDeleteFile();
            break;
        case OpCode::LIST_FILES_OP:
            processListFiles();
            break;
        default:
            std::cerr << "Unknown OpCode received!" << std::endl;
            throw;
    }
}

/* Proccesses backup file request */
void Request::processBackupFile() {
    try {
        /* Read the name of the file */
        auto [file_name, dir] = getFileNameAndDirectory();
        std::cout << dir << std::endl;

        /* Log file name */
        log_file_name(file_name);
        
        /* If the directory does not exist, we make it */
        if (!check_directory(dir)){
            std::filesystem::create_directory(dir);
        }

        /* We prepare the file */
        std::filesystem::path file_path = dir / file_name;

        /* As long as bytes received < file size, we keep receiving and writing to file at file_path */
        size_t bytesReceived = 0;
        while (bytesReceived < header.file_size) {
            /* Initialize the chunk */
            size_t chunkSize = std::min(static_cast<size_t>(MAX_BUFFER), header.file_size - bytesReceived);
            chunkSize = sock.read_some(boost::asio::buffer(buffer.data(), chunkSize));
            std::string data(reinterpret_cast<char*>(buffer.data()), static_cast<size_t>(chunkSize)); 
            
            /* Write to file, if we already received data, append. else, we overwrite! */
            if (bytesReceived > 0)
                saveToFile(file_path,data,APP);
            else 
                saveToFile(file_path,data,OVR);


            /* Increment and log */
            bytesReceived += chunkSize;
            log_data_received(bytesReceived,header.file_size, data);
        }      
        responseOperationSuccess(sock, file_name);
    } catch (const std::exception& e) {
        responseGeneralError(sock,e);
    }
}

/* Processes file retreive request */
void Request::processRetrieveFile() {
    try{
        /* Read the name of the file */
        auto [file_name, dir] = getFileNameAndDirectory();
        std::cout << dir << std::endl;
        
        /* Check if the directory exists */
        if (!check_directory(dir)){
            responseFileNotFound(sock,file_name);   
            return;
        }
        
        responseFileRetrieved(sock,dir,file_name);

    } catch (const std::exception& e) {
        responseGeneralError(sock,e);
    }
}

/* Processes delete file request */
void Request::processDeleteFile() {
    try{
        /* Read the name of the file  */
        auto [file_name, dir] = getFileNameAndDirectory();
        std::cout << dir << std::endl;

        /* Check if the directory exists */
        if (!check_directory(dir)){
            responseFileNotFound(sock,file_name);   
            return;
        }
        std::filesystem::remove(dir);
        responseOperationSuccess(sock,file_name);

    } catch (const std::exception& e) {
        responseGeneralError(sock,e);
    }

}

/* Processes retreive file list request */
void Request::processListFiles() {
    /* Define the directory path */
    std::filesystem::path dir = std::filesystem::absolute(DIRECTORY) / std::to_string(header.user_id);
    std::cout << "Searching for files in: " << dir << std::endl;
    
    /* We now check if the directory exists */
    if (!check_directory(dir)){
        responseEmptyDirectory(sock);
        return;
    }

    /* If it does exist, we make a list of all the files */
    std::vector<std::string> fileList;
    for (const auto& entry: std::filesystem::directory_iterator(dir)){
        if (std::filesystem::is_regular_file(entry)){
            fileList.push_back(entry.path().filename().string());
        }
    }

    /* We make a file with a random 32 character long name */
    std::string randomFilename = generateRandomString(32) + ".txt";
    std::filesystem::path filePath = dir / randomFilename;

    /* We now write the file list into the new file */
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        for (const auto& name : fileList) {
            outFile << name << '\n';
        }
        outFile.close();
    }

    /* Send Response */
    responseListReturned(sock,filePath,randomFilename);

}

/* Checks if a directory exists */
bool Request::check_directory(std::filesystem::path dir){
    if (!std::filesystem::exists(dir) || std::filesystem::is_empty(dir))
        return false;
    return true;
}

/* Saves data to a file */
void saveToFile(const std::filesystem::path& file_path,const std::string& data,int status) {
    /* We open the file in binary and we overwrite it the first time, append if more data. */
    std::ios::openmode mode = (status == OVR) ? std::ios::binary : std::ios::app;
    std::ofstream out_file(file_path, mode);

    /* We write the ASCII value of the bytes received in data string */
    if  (out_file.is_open()) {
        for (size_t i = 0; i < data.size(); i++) {
            out_file.put(data[i]);  
        } 
        out_file.close();
    } else throw;
    
}

/* Generates a random 32 character string */
std::string generateRandomString(size_t length) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device random; 
    std::mt19937 generator(random());  
    std::uniform_int_distribution<size_t> distribution(0, characters.size() - 1);

    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }

    return randomString;
}

/* Returns a tuple of <file name , file path> */
std::tuple<std::string, std::filesystem::path> Request::getFileNameAndDirectory() {

    /* Read the name of the file */
    bytes_read = sock.read_some(boost::asio::buffer(buffer.data(), header.name_len));
    std::string file_name(reinterpret_cast<char*>(buffer.data()), static_cast<size_t>(header.name_len));
    std::filesystem::path dir;

    /* Construct directory according to Op Code */
    switch (header.op) {
        case OpCode::BACKUP_FILE_OP:
            dir = std::filesystem::absolute(DIRECTORY) / std::to_string(header.user_id);
            break;
        case OpCode::RETRIEVE_FILE_OP:
            dir = std::filesystem::absolute(DIRECTORY) / std::to_string(header.user_id) / file_name;
            break;
        case OpCode::DELETE_FILE_OP:
            dir = std::filesystem::absolute(DIRECTORY) / std::to_string(header.user_id) / file_name;
            break;
        default:
            throw;
            break;
    }
    /* Return tuple */
    return std::make_tuple(file_name, dir);
}