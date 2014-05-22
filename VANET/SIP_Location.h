


#ifndef SIP_LOCATION_H_
#define SIP_LOCATION_H_

#include "messages_m.h"
#include <cpacketqueue.h>
#include <string.h>

using namespace std;


class SIP_Location : public cSimpleModule
{

    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


};

#endif
