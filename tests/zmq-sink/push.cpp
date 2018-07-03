#include "zhelpers.h"
#include <time.h>
#include <stdlib.h>


int main() {
    //  Create context
    zmq::context_t context(2);
    srand(time(NULL));   // should only be called once

    std::string r = std::to_string(rand());
    // Create server socket
    zmq::socket_t push (context, ZMQ_PUSH);
    push.connect("tcp://localhost:5557");


    // Send message from server to client

    s_sendmore  (push, r+": My Message part 1");
    s_sendmore  (push, r+": My Message part 2");
    s_sendmore  (push, r+": My Message part 3");
    s_sendmore  (push, r+": My Message part 4");
    s_sendmore  (push, r+": My Message part 5");
    s_send  (push, r+": My Message part end");

    sleep(500);


    push.close();
}