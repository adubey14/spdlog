#include "zhelpers.h"

int main() {
    //  Create context
    zmq::context_t context(1);
    // Create client socket
    zmq::socket_t pull (context, ZMQ_PULL);
    pull.bind("tcp://*:5557");


    while(true) {
        std::vector<std::string> messages;
        s_recvmore(pull, messages);
        for (std::string x:messages) {
            std::cout << "Received: " << x << std::endl;
        }
    }
    pull.close();

}