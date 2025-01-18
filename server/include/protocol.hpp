#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>


#define MAX_BUFFER 2048

/* OpCode definitions */
enum class OpCode : uint8_t {
    BACKUP_FILE_OP = 100,           // all header fields are full
    RETRIEVE_FILE_OP = 200,         // size,payload fields do not exist.
    DELETE_FILE_OP = 201,           // size,payload files do not exist.
    LIST_FILES_OP = 202             // size,payload,filename,namelen do not exist.
};

/* Response status definitions */
enum class ResponseStatus : uint16_t {
    FILES_RETREIVED = 210,
    LIST_RETURNED = 211,
    OPERATION_SUCCESS = 212,
    FILE_NOT_FOUND = 1001,
    EMPTY_DIRECTORY = 1002,
    GENERAL_ERROR = 1003
};

/* A request header */
struct RequestHeader {
        uint32_t user_id;
        uint8_t version;
        OpCode op;
        uint16_t name_len;
        uint32_t file_size; 
        //filename will come dynamically after the length, since it is not a fixed size. best practice is keeping it outside the struct.
        //payload comes after this, dynamically.
};

/* A response header */
struct ResponseHeader {
    uint8_t version;
    ResponseStatus status;
    uint16_t name_len;
    //filename will come dynamically after the length, since it is not a fixed size. best practice is keeping it outside the struct.
    uint32_t file_size;
    //payload comes after this, dynamically.
};

#endif 
