#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <cstdint>

// OpCode definitions
enum class OpCode : uint8_t {
    BackupFile = 100,           // all header fields are full
    RetrieveFile = 200,         // size,payload fields do not exist.
    DeleteFile = 201,           // size,payload files do not exist.
    ListFiles = 202             // size,payload,filename,namelen do not exist.
};

// Response status definitions
enum class ResponseStatus : uint16_t {
    FileRetrieved = 210,
    ListReturned = 211,
    OperationSuccessful = 212,
    FileNotFound = 1001,
    NoFilesForClient = 1002,
    GeneralError = 1003
};

// Request header
struct RequestHeader {
    uint32_t user_id;
    uint8_t version;
    OpCode op;
    uint16_t name_len;
    //filename will come dynamically after the length, since it is not a fixed size. best practice is keeping it outside the struct.
    uint32_t file_size;
    //payload comes after this, dynamically.
};

// Response header
struct ResponseHeader {
    uint8_t version;
    ResponseStatus status;
    uint16_t name_len;
    //filename will come dynamically after the length, since it is not a fixed size. best practice is keeping it outside the struct.
    uint32_t file_size;
    //payload comes after this, dynamically.
};

#endif 
