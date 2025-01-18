#include "../include/communication.hpp"

void convertToBigEndian(void* data, size_t size) {
    if (size == 2) {  // 16-bit data, use ntohs
        uint16_t* value = static_cast<uint16_t*>(data);
        *value = ntohs(*value);
    } else if (size == 4) {  // 32-bit data, use ntohl
        uint32_t* value = static_cast<uint32_t*>(data);
        *value = ntohl(*value);
    }
}

void convertToLittleEndian(void* data, size_t size) {
    if (size == 2) {  // 16-bit data, use ntohs (reverse operation)
        uint16_t* value = static_cast<uint16_t*>(data);
        *value = ntohs(*value);  // Reverse of ntohs for little-endian
    } else if (size == 4) {  // 32-bit data, use ntohl (reverse operation)
        uint32_t* value = static_cast<uint32_t*>(data);
        *value = ntohl(*value);  // Reverse of ntohl for little-endian
    }
}
