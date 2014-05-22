


#ifndef WIMAX_H_
#define WIMAX_H_

#include "messages_m.h"
#include <cpacketqueue.h>
#include <string.h>

using namespace std;

struct Connection
{
  string RecepientName; //will be recepient's name
  int gateIndex;
  bool isActive;
  int Xpos, Ypos;  //the coordinates of the recepient

};

class WiMAX : public cSimpleModule
{
  protected:
    //variables:
	int Xpos, Ypos;
	double Emergency_FLOOD_Transmission_Time;
	int numOfFreq;
	int SRV_Range;
	int Type;
	int MaxQueueLength;
	simtime_t* MultipleTransmissionMutex;
	/* Since the location of all AVs can be set only after the SRV's positions are set,
	 * every SRV will notify all of his AVs about it's location at simtime()=0, thus allowing them
	 * to position themselves around it.
	 */
	bool isInitialized;    //will indicate whether this station was initialized by the SRV or not
	bool isActive;
	bool isFLOODing;
	bool* isWaitingForRegularACK;        //states if we're waiting for an ACK for a normal frame
	bool* isWaitingForFLOODACK;			//states if we're waiting for an ACK for a FLOOD frame
	cPacketQueue** PacketQueue;	  		//a queue that'll hold all the packets
	cPacketQueue* FLOODQueue;     //a queue that'll hold the FLOOD messages
	Connection *Connections;      //the connections data-base
	cMessage *TimeOutEvent;      //a message that'll act as TO event

    int TotalThrownPackets;
    cOutVector TotalThrownPacketsVector;
    int TotalCorruptPackets;
    cOutVector TotalCorruptPacketsVector;


    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *);
    int CalcEuclidianDistance(int,int,int,int);
    void handleSelfEvent (cMessage* );
    void InitializeWimax(cMessage *);
    void HandleInactiveAV(cMessage *);
    void AV_WiMAX_Handler(cMessage *);
    void SRV_WiMAX_Handler(cMessage *);
    void BS_WiMAX_Handler(cMessage *);
    void HandleNotSelfMsgHandler(cMessage*);
    void DeletePacket(cPacket*);
    Wimax_Frame* GetTheNextFrameToBeSent (int);
    void CreateFutureSelfEvent (bool,bool,int,int,simtime_t,bool);
    void HandleTimeOutEvent (int , int , bool );
    void HandleNotTimeOutEvent (int , int , bool );
    bool CalcCorruptionProb(double);
    int GetDestinationGate(string);
    void UpdateConnections(cMessage*);
    void UpdateSelfLocation(UDP_IP_Packet*);
    int CalcTotalNumOfPacketsInQueues ();
    void finish ();

};

#endif
