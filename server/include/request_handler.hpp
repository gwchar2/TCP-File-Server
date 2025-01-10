#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include "protocol.hpp"

class RequestHandler {
public:
    void processRequest(const RequestHeader& request); 
    // Add additional methods for specific request types
};

#endif 
