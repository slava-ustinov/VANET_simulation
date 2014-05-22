


#ifndef UDP_IP_H_
#define UDP_IP_H_

#include "messages_m.h"
#include <cpacketqueue.h>
#include <string.h>

using namespace std;


class UDP_IP : public cSimpleModule
{

    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


};

#endif
