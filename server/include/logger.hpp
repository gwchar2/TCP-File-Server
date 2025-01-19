#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "request.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

#define BYTES_PER_LINE 16
#define MAX_ROW 7

void formatted_hexa(const unsigned char* data, size_t length);
void log_header(const std::string& msg);
void log_received_header(const RequestHeader& header);
void log_file_name(const std::string& file_name);
void log_data_received(size_t bytesReceived, size_t file_size,const std::string& data);
void log_response_header(const ResponseHeader& header);
void log_response_sent(const std::string& response);

#endif