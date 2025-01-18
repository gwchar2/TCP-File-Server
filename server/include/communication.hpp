#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include <iostream>
#include <cstring>
#include <boost/asio.hpp>
#include <iomanip>
#include <ctime>

void convertToBigEndian(void* data, size_t size);
void convertToLittleEndian(void* data, size_t size);


#endif 