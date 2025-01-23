#include "../include/server.hpp"

int main() {
    /* Server listens to port 8080 */
    int port = 8080;    

    /* Creates and starts new server */
    Server server(port);
    server.start(); 

    return 0;
}