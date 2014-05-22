


#ifndef AV_ONBOARD_COMPUTER_H_
#define AV_ONBOARD_COMPUTER_H_

#include "messages_m.h"
#include <cpacketqueue.h>
#include <string.h>

using namespace std;


class AV_OnBoard_Computer : public cSimpleModule
{

    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    int Xpos;
    int Ypos;
    double HelloMsgPeriodInSec;
    int LastFLOODmsgID;
    simtime_t LastFloodEventTime;
    string Name;
    string SRVName;
    bool isInitialized;
	bool isRegsitered;
	bool isActive;
	bool isCrazy;

    cOutVector FloodPropagationTimes;

    void Init(SIP *msg);
    void HandleNotSelfMsgHandler(cMessage*);
    void handleSelfEvent(cMessage* );
    void HandleFloodMessage(SIP*);
    void CreateAndSendAHelloMsg ();
    void CreateAndSendARelocationMsg();
    void HandleControlMsg(Control_msg*);
    void UpdateDisplayString(int, int,bool );

};

#endif
