


#ifndef ETHERNET_H_
#define ETHERNET_H_

#include "messages_m.h"
#include <cpacketqueue.h>
#include <string.h>

using namespace std;


class Ethernet : public cSimpleModule
{
	int Type;
	cPacketQueue* PacketQueue;
	simtime_t MultipleTransmissionMutex;

    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void HandleBS_NotSelfEvent(cMessage* msg);
    void HandleServer(cMessage* msg);
    void HandleServerSelfEvent (cMessage*);
    void HandleBS_SelfEvent(cMessage*);

};

#endif
