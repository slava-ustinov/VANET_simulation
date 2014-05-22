


#ifndef SIP_PROXY_H_
#define SIP_PROXY_H_

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

class SIP_Proxy : public cSimpleModule
{

    int Xpos;
    int Ypos;
	simtime_t LastFloodEventTime;
    int SrvRange;
    string Name;
    bool isInitialized;
	LogEntry* FloodLog;
    double HelloMsgPeriodInSec;
    int TotalNumberOfFloods;
    cOutVector TotalNumberOfFloodsVector;


    void Init(SIP *msg);
    void HandleFloodMessage(SIP* msg);
    void CreateAndSendARelocationMsg();
    void CreateAndSendAHelloMsg ();
    void HandleControlMsg(Control_msg*);
    void UpdateDisplayString(int, int, bool);
    void handleSelfEvent(cMessage* );
    void HandleNotSelfMsgHandler(cMessage*);
    bool CheckIfThisFLOODisNew (SIP*);
    void finish ();


    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
