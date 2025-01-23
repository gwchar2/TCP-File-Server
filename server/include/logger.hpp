#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "server.hpp"

#define BYTES_PER_LINE 16
#define MAX_ROW 7

void formatted_hexa(const unsigned char* data, size_t length);                                      // Prints in formatted hexa.
void log_header(const std::string& msg);                                                            // Logs the current message header (custom).
void log_received_header(const RequestHeader& header);                                              // Logs the received message.
void log_file_name(const std::string& file_name);                                                   // Logs the file name specifically (since it is dynamic)
void log_data_received(size_t bytesReceived, size_t file_size,const std::string& data);             // Logs the data received.
void log_response_header(const ResponseHeader& header);                                             // Logs the header sent as a response.
void log_response_sent(const std::string& response);                                                // Logs the response data that is sent.

#endif