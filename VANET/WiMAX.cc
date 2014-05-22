/*
 * Simulates the WIMAX protocol to the level of transmission and reception of data frames.
 * The mechanism implemented here is a S&W with ACK. There's also a priority mechanism for transmitting FLOOD frames
 * before regular frames. To simulate errors, we use an error function who's full details appear in the documentation.
 */

#include <omnetpp.h>
#include <math.h>
#include "WiMAX.h"
#include "messages_m.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#define SCREEN_WIDTH 1200
#define UPPER_LANE_Y_LOCATION 275
#define ACK_FRAME_SIZE
#define TIMEOUT 0.5
#define WIMAX_HEADER_LENGTH 100
#define WIMAX_ACK_SIZE 100

using namespace std;


// The module class needs to be registered with OMNeT++
Define_Module(WiMAX);

void WiMAX::initialize()
{
	//Var init
	Emergency_FLOOD_Transmission_Time = (double)getAncestorPar("Emergency_FLOOD_Transmission_Time_In_Seconds"); //get the FLOOD duration
	SRV_Range = getAncestorPar("SRV_Transmission_Range");  //get the SRV's range
    MaxQueueLength = getAncestorPar("WimaxQueueSize"); //get the buffer size
	int MaxNumOfFreq = par("NumOfFrequencies");        //get the number of frequencies
	int NumOfAvsPerSRV = getAncestorPar("Num_Of_AVs_Per_SRV");

	Type = par("type");  //get the station's type
	Xpos = getAncestorPar("Xpos");		//get the Xpos
	Ypos = getAncestorPar("Ypos");		//get the Ypos

    numOfFreq = min(MaxNumOfFreq,NumOfAvsPerSRV+1); //set this value to be the actual amount of used frequencies

    if (Type==3)     //if this is a BS, the number of freq. is the number of SRVs
        numOfFreq = MaxNumOfFreq;

	isWaitingForRegularACK = new bool[numOfFreq];
	isWaitingForFLOODACK = new bool[numOfFreq];

	int i;

	PacketQueue = new cPacketQueue*[numOfFreq];    //create arrays of pointers to packet queues
	FLOODQueue = new cPacketQueue;             //create a single FLOOD packet queue

	for (i=0; i< numOfFreq ;i++)
		{
		PacketQueue[i] = new cPacketQueue(NULL,NULL);   //create a new packet queue

		isWaitingForRegularACK[i] = false;
		isWaitingForFLOODACK[i] = false;
		}

	isActive=true;
	isInitialized=false;
	isFLOODing=false;
	MultipleTransmissionMutex = new simtime_t[numOfFreq];

	Connections = new Connection[numOfFreq];  //create

	for (i=0; i<numOfFreq ;i++) //init
		{
		Connections[i].isActive = false; //set this entry as inactive
		MultipleTransmissionMutex[i] = -1; //init
		}

    TotalThrownPacketsVector.setName("Total number of thrown packets"); //set stat. vector
    TotalThrownPackets=0;

    TotalCorruptPacketsVector.setName("Total number of received corrupt packets");
    TotalCorruptPackets =0;

	//end of var init.

	switch (Type)
	{
	case 1: //this is an AV
		if (! getParentModule()->gate("Gates$o",0)->isConnectedOutside()) //if it's an AV and the channel isn't connected
			{
			//mark this AV as inactive
			isActive=false;
			HandleInactiveAV(NULL);
			}//if

		break;
	case 2:
		break;
	case 3: //this is a BS
			isInitialized=true;   //mark as initialized
			string srv = "SRV";
			for (i=0; i< numOfFreq; i++) //send an init msg to all SRVs
				{
				InitMsg* msg = new InitMsg(); //create a new init msg
				msg->setSourceName("BS");
				msg->setSrcXPos(Xpos);
				msg->setSrcYPos(Ypos);
				send(msg,"link$o",i);         //send an init msg to all SRVs

				}
		break;

	}//end of switch

}//end of initialize()

void WiMAX::handleMessage(cMessage *msg)
{

	if (!isActive)     //if this AV is inactive
		{
		if(!isInitialized)
		    {
		    HandleInactiveAV(msg);
		    delete(msg);
		    }
        DeletePacket((cPacket*)msg);
		return;
		}

	if (!isInitialized) //if it's an uninitialized AV or SRV
		{
		InitializeWimax(msg);
		return;
		}

	switch (Type)
	{
	case 1:
		AV_WiMAX_Handler(msg);
		break;
	case 2:
		SRV_WiMAX_Handler(msg);
		break;
	case 3:
		BS_WiMAX_Handler(msg);
		break;

	}//switch

}//end of handleMessage()

void WiMAX::AV_WiMAX_Handler(cMessage *msg)
{

	if (!msg->isSelfMessage())
		HandleNotSelfMsgHandler(msg);

	else
	  handleSelfEvent(msg);



}//end of AV_WiMAX_Handler()

void WiMAX::SRV_WiMAX_Handler(cMessage *msg)
{
	if (!msg->isSelfMessage())
		HandleNotSelfMsgHandler(msg);

	else
		handleSelfEvent(msg);

}//end of SRV_WiMAX_Handler()

//Handles a self event. Self events are scheduled at timeouts and when channels finish transmitting.
void WiMAX::handleSelfEvent (cMessage* selfMsg)
{
	WiMAX_SelfMsg *msg = check_and_cast<WiMAX_SelfMsg *>(selfMsg);   //cast to self msg

	if (msg->getIsFinishedFlooding())
		{
		isFLOODing=false;
		getParentModule()->bubble("Finished FLOODing!");
		if (!FLOODQueue->isEmpty())
		    DeletePacket(FLOODQueue->pop());
		delete(msg);
		return;
		}

	if(msg->getIsTimeOut()) //if it's a TO event
		HandleTimeOutEvent(msg->getQueueIndex(),msg->getCall_ID(),msg->getIsFLOOD()); //call the TO handler
	else
		HandleNotTimeOutEvent(msg->getQueueIndex(),msg->getCall_ID(),msg->getIsFLOOD()); //call the Not-TO handler

	delete(msg);

}//end of handleSelfEvent()

//Handles timeout self events
void WiMAX::HandleTimeOutEvent (int GateIndex, int ID, bool isFLOOD)
{

	UDP_IP_Packet* pack;
	if (isFLOOD)   //if this TO is for the FLOOD queue
		{
		pack = (UDP_IP_Packet*)FLOODQueue->front(); //get the 1st packet from the FLOOD queue
		if (pack==NULL)  //if the FLOOD queue is empty, meaning an ACK has already arrived for this msg. RELEVANT ONLY FOR AN AV
			{
			return;
			}

		if (ID == pack->getCall_ID())
			{
			isWaitingForFLOODACK[GateIndex]=false;           //set the state to a state when a new FLOOD message has arrived from the upper layer
			CreateFutureSelfEvent(false,false,GateIndex,ID,simTime(),false);  //re-enter the handler with a non-TO event
			}
		}//isFLOOD
	else    //this TO is for the regular queue
		{
		pack = (UDP_IP_Packet*)PacketQueue[GateIndex]->front(); //get the 1st packet from the regular queue
		if (pack==NULL)  //if the FLOOD queue is empty
			{
			return;
			}

		if (ID == pack->getCall_ID()) //if the TO is for a frame that has been ACKed (we don't cancel self events!)
			{
			isWaitingForRegularACK[GateIndex]=false;     //set the state to a state when a new regular message has arrived from the upper layer
			CreateFutureSelfEvent(false,false,GateIndex,ID,simTime(),false);  //re-enter the handler with a non-TO event
			}

		}
	EV << "FLOOD_Queue size: " << FLOODQueue->getLength() <<
			" Regular queue size: " << PacketQueue[GateIndex]->getLength() << "\n";

}//end of HandleTimeOutEvent()


//Handles the case the triggering event isn't a timeout, meaning the channels is now clear.
void WiMAX::HandleNotTimeOutEvent (int GateIndex, int ID, bool isFLOOD)
{
	bool isSent=false;

	Wimax_Frame* frame = GetTheNextFrameToBeSent(GateIndex); //get a copy of the next packet

	if (simTime() == MultipleTransmissionMutex[GateIndex]) //if this code section was already executed at this time-point
	    {
	    DeletePacket(frame); //delete this frame copy
		return;
	    }

	MultipleTransmissionMutex[GateIndex] = simTime(); //this basically creates a mutex for every active channel

	if(getParentModule()->gate("Gates$o",GateIndex)->getChannel()->isBusy() )
		//if we've entered here and the channel isn't empty, it means an ack is being transmitted now
		{
		//come back here when the channel clears.
		CreateFutureSelfEvent(false,false,GateIndex,ID,getParentModule()->gate("Gates$o",GateIndex)->getChannel()->getTransmissionFinishTime(),false);
		return;
		}

	if (frame==NULL) //IF BOTH QUEUES ARE EMPTY
		{
		return;
		}

		if (frame->getIsFLOOD() && !isWaitingForFLOODACK[GateIndex] && !frame->getIsACK()) //if the current message is a FLOOD message and we can send it right now
			{
			if(Type==1) //Only if this station is an AV, we'll wait for a ACK on a flood msg
				{
				isWaitingForFLOODACK[GateIndex]=true;   //set flag
				getParentModule()->bubble("Sending a FLOOD message!");
				send(frame,"link$o",GateIndex); //send
				isSent=true;
				CreateFutureSelfEvent(true,true,GateIndex,ID,simTime()+TIMEOUT,false); //create a TO event
				}
			else    //if this station is an SRV or a BS, we don't wait for an ACK.
				{
				isWaitingForFLOODACK[GateIndex]=false;   //set flag
				getParentModule()->bubble("Sending a FLOOD message!");
				send(frame,"link$o",GateIndex); //send
				isSent=true;
				CreateFutureSelfEvent(false,false,GateIndex,ID,getParentModule()->gate("Gates$o",GateIndex)->getChannel()->getTransmissionFinishTime(),false);
				//create a self event to when the channel clears
				if (!isFLOODing)
					{
					isFLOODing=true;
					getParentModule()->bubble("Sending a FLOOD message!");
					CreateFutureSelfEvent(false,false,GateIndex,ID,simTime()+Emergency_FLOOD_Transmission_Time,true); //set a self event to when the FLOOD should stop
					}
				}
			} //if there's a FLOOD msg waiting to be sent and we can send it

		else //we can't send a FLOOD msg right now
			{
			//ACKs must be sent immediately, even if we're waiting for an ACK.

			if (frame->getIsACK()) //if the regular frame is an ACK
				{
			//	isWaitingForRegularACK[GateIndex]=false;
				delete(PacketQueue[GateIndex]->pop()); //dequeue this ack
				frame->setKind(1); //set packet color to green
		//		getParentModule()->bubble("Sending an ack!");
				send(frame,"link$o",GateIndex); //send
				isSent=true;
				CreateFutureSelfEvent(false,false,GateIndex,ID,getParentModule()->gate("Gates$o",GateIndex)->getChannel()->getTransmissionFinishTime(),false);
				}
			else
                {
                    if (!isWaitingForRegularACK[GateIndex] && !isWaitingForFLOODACK[GateIndex]) //this message is not an ACK and we're not waiting on any ack
                        {
                        isWaitingForRegularACK[GateIndex]=true;   //set flag
                      //  getParentModule()->bubble("Sending a normal message!");
                        CreateFutureSelfEvent(true,false,GateIndex,ID,simTime()+TIMEOUT,false); //create a TO event
                        send(frame,"link$o",GateIndex); //send
                        isSent=true;
                        }
                }//else

			}//if not waiting for a FLOOD ack

	if(!isSent) //if we weren't able to send a frame this time
		DeletePacket(frame);


	EV << "Flood ack waiting: " << isWaitingForFLOODACK[GateIndex] << ", Regular ACK waiting: " << isWaitingForRegularACK[GateIndex] << "\n";

}//end of HandleNotTimeOutEvent()

//Handle the case that a message came from the line or the UDP/IP layer.
void WiMAX::HandleNotSelfMsgHandler(cMessage* msg)
{
	int GateIndex=0;


	if (!strcmp(msg->getArrivalGate()->getBaseName(),"line_up")  )  //if the msg came from the UDP_IP
		{

	    if (CalcTotalNumOfPacketsInQueues()>=MaxQueueLength) //if the queues are full, we need to throw this packet
	        {
	        DeletePacket((cPacket*)msg); //delete
	        TotalThrownPackets++;
	        return;
	        }

		bool isFlood=true;
		UDP_IP_Packet *IP_pack = check_and_cast<UDP_IP_Packet *>(msg);   //cast to IP_pck

		UpdateSelfLocation(IP_pack);  //update the current vehicle's location


		if (strcmp( IP_pack->getCommand(), "FLOOD" ))             //if it's not a FLOOD msg
			{
			if (Type==3) //if this is a BS, the index of the target SRV is stored in the SIP
				{
				GateIndex = IP_pack->getHandlingSRVindex();
				}
			else  //if this isn't a BS, got and look in the entry table
				GateIndex = GetDestinationGate(IP_pack->getDst()); //search the gate this destination is at

			PacketQueue[GateIndex]->insert(IP_pack);          //enqueue the packet
			isFlood=false;
			}
		else                                 //if it's a FLOOD msg
			FLOODQueue->insert(IP_pack);

		//AT THIS STAGE, WE HAVE THE PACKET THAT HAS TO BE TRANSMITTED
		EV << "New packet was enqueud! FLOOD_Queue size: " << FLOODQueue->getLength() <<
				" Regular queue size: " << PacketQueue[GateIndex]->getLength() << "\n";

		//Now we have to schedule a single self event, to when the next packet should be sent over the line

		if (isFlood) //if this message is the only FLOOD message in the system, we'de like to generate self events on all channels. Works for all station types
			{
			for (int i=0; i<numOfFreq  ;i++) //for every available channel
				{
				if (Connections[i].isActive) //if this gate is active
					{
					CreateFutureSelfEvent(false,false,i,IP_pack->getCall_ID(),
							max(simTime(),getParentModule()->gate("Gates$o",i)->getChannel()->getTransmissionFinishTime()),false);
					}
				}//for every available active channel
			}//if isFLOOD

		else  //if this isn't a FLOOD msg
			{
			CreateFutureSelfEvent(false,false,GateIndex,IP_pack->getCall_ID(),
					max(simTime(),getParentModule()->gate("Gates$o",GateIndex)->getChannel()->getTransmissionFinishTime()),false);
			}
		}//if the msg came from the UDP_IP

	else  //this message came from the line
		{
		Wimax_Frame *Wimax_frame = check_and_cast<Wimax_Frame *>(msg);   //cast to Wimax frame

		UpdateConnections(msg);    //update the info for this connection (location and activity)

		GateIndex = Wimax_frame->getArrivalGate()->getIndex();

		if (Wimax_frame->getIsCorrupted()) //if this packet is corrupt
			{
			DeletePacket(Wimax_frame);  //delete this corrupted packet
	        TotalCorruptPackets++;
			return;
			}

		if (Wimax_frame->getIsACK()) //if this is an ACK frame
			{
			EV << "Received an ACK!\n";
			if (Wimax_frame->getIsFLOOD()) //if it's an ACK for a sent FLOOD. Happens only at an AV
				{
				UDP_IP_Packet* flood_pck = (UDP_IP_Packet*)FLOODQueue->front(); //get the FLOOD packet from the head of the FLOOD queue
				if (flood_pck!=NULL && Wimax_frame->getCall_ID() == flood_pck->getCall_ID() ) //it's a legit FLOOD ack
					{
					isWaitingForFLOODACK[GateIndex] = false;  //lower the flag
					DeletePacket(FLOODQueue->pop()); //remove the FLOOD msg at the head of the queue

					CreateFutureSelfEvent(false,false,GateIndex,Wimax_frame->getCall_ID(),
							max(simTime(),getParentModule()->gate("Gates$o",GateIndex)->getChannel()->getTransmissionFinishTime()),false);
					}
				}//if FLOOD ACK

			else //THIS IS AN ACK FOR A REGULAR FRAME
				{ //we don't check for ack corruption since we assume that acks are always received correctly

				UDP_IP_Packet* pack = (UDP_IP_Packet*)PacketQueue[GateIndex]->front();
				if (pack!=NULL && Wimax_frame->getCall_ID() == pack->getCall_ID()) //if this ack is relevant
					{
					isWaitingForRegularACK[GateIndex]=false;  //lower the flag
					DeletePacket(PacketQueue[GateIndex]->pop());   //pop and delete the pack
					EV << "FLOOD_Queue size: " << FLOODQueue->getLength() <<
								" Regular queue size: " << PacketQueue[GateIndex]->getLength() << "\n";

					CreateFutureSelfEvent(false,false,GateIndex,Wimax_frame->getCall_ID(),
							max(simTime(),getParentModule()->gate("Gates$o",GateIndex)->getChannel()->getTransmissionFinishTime()),false);
					}
				}
			delete(Wimax_frame); //delete the ack
			}//end of if ACK

		else //this is a data frame
			{
			EV << "Received a regular data frame!\n";

				send(Wimax_frame->decapsulate(),"line_up$o");

				if ( !Wimax_frame->getIsFLOOD() || (Type==2 && Wimax_frame->getArrivalGate()->getIndex()!=0) ) //if the message is not a FLOOD message
					//or this is an SRV and the FLOOD came from an AV -> Send ACK
					{
					Wimax_frame->setIsCorrupted(false);
					Wimax_frame->setIsACK(true);
					string temp(Wimax_frame->getSrc()); //save the src
					Wimax_frame->setSrc(Wimax_frame->getDst());   //set the dst as the current src
					Wimax_frame->setDst(temp.c_str());         //set the dst as the former src
					Wimax_frame->setXpos(Xpos);
					Wimax_frame->setYpos(Ypos);
					Wimax_frame->setByteLength(WIMAX_ACK_SIZE);

					//It's crucial that an ACK will be pushed to the head of the queue, or we'll have a chance of livelocking.

					if (!PacketQueue[GateIndex]->isEmpty()) //if the packet queue isn't empty
						PacketQueue[GateIndex]->insertBefore(PacketQueue[GateIndex]->front(),Wimax_frame); //insert this ack at the head of the queue
					else
						PacketQueue[GateIndex]->insert(Wimax_frame);//insert this ack at the head of the queue

					CreateFutureSelfEvent(false,false,GateIndex,Wimax_frame->getCall_ID(),
							max(simTime(),getParentModule()->gate("Gates$o",GateIndex)->getChannel()->getTransmissionFinishTime()),false);
					}
				else   //we don't need to send an ACK for this FLOOD msg
					{
					delete(Wimax_frame);
					}
			}//if this is a data frame
		}//if this message came from the line
}//end of AV_WiMAX_NotSelfMsgHandler()

//Updates the current location of this vehicle. Location data is extracted from outgoing messages.
void WiMAX::UpdateSelfLocation(UDP_IP_Packet* msg)
{
	Xpos = msg->getXpos();
	Ypos = msg->getYpos();
}//end of UpdateSelfLocation()


//Handles the case this is a BS
void WiMAX::BS_WiMAX_Handler(cMessage *msg)
{

	if (!msg->isSelfMessage())
		HandleNotSelfMsgHandler(msg);

	else
		handleSelfEvent(msg);

}//end of BS_WiMAX_Handler()

/*On a new message arrival, updates the location of the transmitter. Done to
* Calculate error probability if we'll need to send a message to that transmitter.
*/
void WiMAX::UpdateConnections(cMessage* msg)
{
	Wimax_Frame *Wimax_frame = check_and_cast<Wimax_Frame *>(msg);   //cast to Wimax frame
	int GateIndex =  Wimax_frame->getArrivalGate()->getIndex();
	string src(Wimax_frame->getSrc());

	if (Type==1 || (Type==2 && GateIndex!=0) || Type==3)
		{ //update entry details only if: this is an AV or this is an SRV and this message didn't come from the BS or
		//this is a BS and this message was originated at an SRV
		if (!Connections[GateIndex].isActive) //if this entry is still inactive
			{
			Connections[GateIndex].RecepientName = Wimax_frame->getSrc();
			Connections[GateIndex].isActive = true;
			Connections[GateIndex].gateIndex = GateIndex;
			}

			//anyway, update it's location
			Connections[GateIndex].Xpos = Wimax_frame->getXpos();
			Connections[GateIndex].Ypos = Wimax_frame->getYpos();
		}
}//end of UpdateConnections()

//Returns the gate corresponding with the given destination name string
int WiMAX::GetDestinationGate(string dst)
{
	int i=0;

	while (i < numOfFreq) //for all available connections
		{
		if (!Connections[i].RecepientName.compare(dst.c_str())) //if this connection is the one who's gate we need
			{
			return i;
			}
		i++;
		}
	return 0;   //if no destination is found, meaning that this is an SRV and the message is to be relayed to the BS
}//end of GetDestinationGate()


//Creates a self event
void WiMAX::CreateFutureSelfEvent (bool isTimeOut,bool isFLOOD, int GateIndex, int ID, simtime_t time, bool isFinishedFlooding)
{
	WiMAX_SelfMsg *selfMsg = new WiMAX_SelfMsg();
	selfMsg->setIsTimeOut(isTimeOut);
	selfMsg->setIsFLOOD(isFLOOD);
	selfMsg->setQueueIndex(GateIndex);
	selfMsg->setCall_ID(ID);
	selfMsg->setIsFinishedFlooding(isFinishedFlooding);
	scheduleAt(time,selfMsg);  //schedule an event
}//end of CreateFutureSelfEvent()

/*
 * Returns a copy of the next frame to be sent, considering that FLOOD messages have priorities.
 * Doesn't dequeue packets.
 */
Wimax_Frame* WiMAX::GetTheNextFrameToBeSent (int GateIndex)
{
	Wimax_Frame* frame  = new Wimax_Frame;

	UDP_IP_Packet* packet = (UDP_IP_Packet*) FLOODQueue->front(); //get a ptr to the head of the FLOOD queue

	double distance= CalcEuclidianDistance(Xpos,Ypos,Connections[GateIndex].Xpos,Connections[GateIndex].Ypos); //calc the distance between this station and the dst

	if (packet!=NULL) //if the flood queue isn't empty
		{
		packet = packet->dup();  //create a copy of the packet at the head of the queue
		frame->encapsulate(packet); //encaps
		frame->setIsFLOOD(true);
		frame->setIsCorrupted(CalcCorruptionProb(distance));
		frame->setIsACK(false);
		frame->setCall_ID(packet->getCall_ID());
		frame->setSrc(packet->getSrc());
		frame->setDst(packet->getDst());
		frame->setKind(packet->getKind());
		frame->setXpos(Xpos);
		frame->setYpos(Ypos);
		return frame;
		}

	//the FLOOD queue is empty.

	cPacket* temp =  PacketQueue[GateIndex]->front(); //get a ptr to the head of the regular queue

	if (temp!=NULL) //if the regular queue isn't empty
		{
		if (temp->getEncapsulatedPacket()==NULL) //if this is actually an ACK that was queued
			{
			return (Wimax_Frame*)temp->dup(); //return a copy of this ACK
			}

		EV << "The next frame is a regular frame!\n";
		packet = (UDP_IP_Packet*) temp; //cast to packet
		packet = packet->dup();   //create a copy of the packet at the head of the queue
		frame->encapsulate(packet); //encaps
		frame->setIsFLOOD(false);
		frame->setIsCorrupted(CalcCorruptionProb(distance));
		frame->setIsACK(false);
		frame->setCall_ID(packet->getCall_ID());
		frame->setDst(packet->getDst());
		frame->setSrc(packet->getSrc());
		frame->setKind(packet->getKind());
		frame->setXpos(Xpos);
		frame->setYpos(Ypos);
		return frame;
		}

	return NULL;

}//end of GetTheNextFrameToBeSent()


//Deletes a packet
void WiMAX::DeletePacket(cPacket* pckt)
{
	cPacket* encaps;

	if(!pckt)
	    return;

	while(pckt->getEncapsulatedPacket()!=NULL) //while there's still encapsulated packets
		{
		encaps = pckt->decapsulate();  //decaps
		delete(pckt);					//delete the encapsulating frame
		pckt = encaps;
		}

	if (pckt!=NULL)
	delete(pckt);   //delete the innermost data
}//end of DeletePacket()


//Handles an inactive AV. Occurs when there are too many AVs and not enough freq. at the SRVs.
void WiMAX::HandleInactiveAV(cMessage *msg)
{
	if (!isInitialized)
		{
		ostringstream stream1, stream2;
		string DisplayString("p=");

		Ypos = (int) (rand()% (int)getAncestorPar("NumOfLanes"))+1;   //draw a random lane in the range [1,NumOfLanes]
		Xpos = (int) (rand()% (int)getAncestorPar("Road_Length"))+1;   //set the X location for this AV
		//Setting the display string
		stream1 << (Xpos*(double)SCREEN_WIDTH/(int)getAncestorPar("Road_Length"));
		DisplayString += stream1.str();
		DisplayString += ",";
		stream2 << ( (Ypos-1)*100 +UPPER_LANE_Y_LOCATION ) ;   //set the Y location for this AV
		DisplayString += stream2.str();
		DisplayString += ";i=block/star,red";
		getParentModule()->setDisplayString(DisplayString.c_str());

		SIP* SIPiniMsg = new SIP();
		SIPiniMsg->setXpos(Xpos);
		SIPiniMsg->setYpos(Ypos);
		SIPiniMsg->setSrc("inactive");

		UDP_IP_Packet* temp = new UDP_IP_Packet();
		temp->encapsulate(SIPiniMsg);
		send(temp,"line_up$o"); //send an init message to the SIP

		isInitialized=true;
		}

}//end of HandleInactiveAV()


//Handles the initialization process we've created to place all vehicles on the road at T=0.
void WiMAX::InitializeWimax(cMessage *msg)
{
	InitMsg *IniMsg = check_and_cast<InitMsg *>(msg);   //cast

	string NameStr(IniMsg->getSourceName());
	string DisplayString("p=");
	ostringstream stream1, stream2;
	string SelfName = "";

	switch(Type)
		{
		case 1:   //it's an AV
			{
				EV << "Entered the event handler at an AV\n";
				Connections[0].RecepientName = NameStr;
				Connections[0].gateIndex = msg->getArrivalGate()->getIndex(); //get the arrival gate's index
				Connections[0].isActive = true;
				Connections[0].Xpos = IniMsg->getSrcXPos();
				Connections[0].Ypos = IniMsg->getSrcYPos();

				int NumOfLanes = getAncestorPar("NumOfLanes");

				Ypos = (int) ((rand()%NumOfLanes)+1);   //draw a random lane in the range [1,NumOfLanes]

				do
				{
				 Xpos = (int) (  (rand()% ((2*SRV_Range)+1) )-SRV_Range + Connections[0].Xpos); //draw a random x position within the SRV's range
				}while ( Xpos < 0 || Xpos > (int)getAncestorPar("Road_Length"));

				//Setting the display string
				stream1 << (Xpos * SCREEN_WIDTH/(int)getAncestorPar("Road_Length"));   //set the X location for this AV
				DisplayString += stream1.str();
				DisplayString += ",";
				stream2 << ( (Ypos-1)*100 +UPPER_LANE_Y_LOCATION ) ;   //set the Y location for this AV
				DisplayString += stream2.str();
				DisplayString += ";i=block/star,green";
				getParentModule()->setDisplayString(DisplayString.c_str());

				//now we have to set a random position for this AV around the SRV
			}
			break;
		case 2:	//it's an SRV
				Connections[0].RecepientName = NameStr;
				Connections[0].gateIndex = msg->getArrivalGate()->getIndex(); //get the arrival gate's index
				Connections[0].isActive = true;
				Connections[0].Xpos = IniMsg->getSrcXPos();
				Connections[0].Ypos = IniMsg->getSrcYPos();

			    SelfName += "SRV";
			    SelfName += (char)(getParentModule()->getIndex()+'0');  //create a name string for the current SRV

				for (int i=1; i<numOfFreq ;i++)  //there are numOfFreq-1 AVs, starting from index 1 (index 0 is for the BS)
					{
					InitMsg* msg = new InitMsg();
					msg->setSourceName(SelfName.c_str()); //convert a string to const char* and set it
					msg->setSrcXPos(Xpos);
					msg->setSrcYPos(Ypos);
					send(msg,"link$o",i);         //send an init msg to all AVs
					}

				//Setting the display string
				stream1 << (Xpos * SCREEN_WIDTH/(int)getAncestorPar("Road_Length"));   //set the X location for this SRV
				DisplayString += stream1.str();
				DisplayString += ",";
				stream2 << ( (Ypos-1)*100 +UPPER_LANE_Y_LOCATION ) ;   //set the Y location for this SRV
				DisplayString += stream2.str();
				DisplayString += ";i=block/broadcast";
				getParentModule()->setDisplayString(DisplayString.c_str());
			break;
		}//switch
	//Sending a message with init data to the SIP
	SIP* SIPiniMsg = new SIP();
	SIPiniMsg->setXpos(Xpos);
	SIPiniMsg->setYpos(Ypos);
	SIPiniMsg->setSrc(NameStr.c_str());

	UDP_IP_Packet* temp = new UDP_IP_Packet();
	temp->encapsulate(SIPiniMsg);
	send(temp,"line_up$o"); //send an init message to the SIP

	EV << "FINISHED INIT \n";
	isInitialized=true;
	delete(msg);
}//end of InitializeWimax()

//Calculates a Euclidian distance between 2 points.
int WiMAX::CalcEuclidianDistance (int x1, int y1, int x2, int y2)
{
	return (int)sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)  ); //calc the Euclidian dist.
}//end of CalcEuclidianDistance()


/**
 * this function get a distance from the other-side station
 * and returns the error probability
 *
 * PRE= precentceOutOfMaxDistans
 *P_erroe[%_of_max_distance]= 0.01 e^[-6000/((%_of_max_distance)^2)]
 */
bool WiMAX::CalcCorruptionProb(double distance)
{
	double ErrProb;
	double precentceOutOfMaxDistance;

	if (distance>SRV_Range) //meaning the station on the other side is the BS
		precentceOutOfMaxDistance=(distance/(int)getAncestorPar("Road_Length"))*100;
	else                    //the other station is an AV
		precentceOutOfMaxDistance=(distance/SRV_Range)*100;

	double temp = -4000/(precentceOutOfMaxDistance*precentceOutOfMaxDistance);
	ErrProb = pow(2.71,temp)/2;

	temp = rand()%101;
	return ( (100*ErrProb)>temp)?true:false;
}//end of setCorruption(double distance)

//Returns the total number of packets at all queues.
int WiMAX::CalcTotalNumOfPacketsInQueues ()
{
    int total=0;

    for (int i=0; i<numOfFreq ;i++)
        {
        total += PacketQueue[i]->getLength();
        }

    return total+FLOODQueue->getLength();
}//end of CalcTotalNumOfPacketsInQueues()

//Records collected statistics
void WiMAX::finish ()
{
    TotalThrownPacketsVector.record(TotalThrownPackets);   //record the total number of thrown packets at this station
    TotalCorruptPacketsVector.record(TotalCorruptPackets);  //record the total number of corrupt packets
}


