


#ifndef SIP_GUARD_H_
#define SIP_GUARD_H_

#include "messages_m.h"
#include <cpacketqueue.h>
#include <string.h>

using namespace std;

struct LogEntry
{
	int Call_ID;
	simtime_t time;
	bool isValid;
};

class SIP_Guard : public cSimpleModule
{

	LogEntry* FloodLog;
    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    bool CheckIfThisFLOODisNew (SIP* data);

};

#endif
