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
    int option=0;
    push.setsockopt(ZMQ_SNDTIMEO,&option,sizeof(option));


    // Send message from server to client

   for (int i =0;i<10000;i++)
{
    std::cout<<"step 1" <<" iteration "<<i<<"\n";
    s_sendmore  (push, r+": My Message part 1");
    s_sendmore  (push, r+": My Message part 2");
    s_sendmore  (push, r+": My Message part 3");
    s_sendmore  (push, r+": My Message part 4");
    s_sendmore  (push, r+": My Message part 5");
    s_send  (push, r+": My Message part end");
}

    std::cout<<"sent all messages\n";
    sleep(5);


    push.close();
}
