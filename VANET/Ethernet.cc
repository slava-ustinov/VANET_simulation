/*
 * Simulates the Ethernet controller. A BS and servers behave differently.
 * For a BS: all incoming messages are simply decapsulated and passed on.
 * For a server: a message is send onward depending on the server's type and the message's command.
 */

#include <omnetpp.h>
#include <math.h>
#include "Ethernet.h"
#include "messages_m.h"
#include <stdio.h>
#include <string.h>

using namespace std;


// The module class needs to be registered with OMNeT++
Define_Module(Ethernet);

void Ethernet::initialize()
{
 Type = par("type");

 PacketQueue = new cPacketQueue();

 MultipleTransmissionMutex = -1;

}//end of handleMessage();


void Ethernet::handleMessage(cMessage *msg)
{
	if (Type==2)  //if this is a BS. We use the Type variable to differentiate between servers and the base station.
		{
		if (!msg->isSelfMessage())
			HandleBS_NotSelfEvent(msg);
		else
			{
		    HandleBS_SelfEvent(msg);
			}
		}

	else   //this is a server
		{
		if (!msg->isSelfMessage())
			HandleServer(msg);
		else
			HandleServerSelfEvent(msg);
		}



}//end of handleMessage()

//Handles a self event on a Base Station's Ethernet
void Ethernet::HandleBS_SelfEvent(cMessage* self)
{

	Eth_Frame* frame = (Eth_Frame*)PacketQueue->front();

	if (frame==NULL || MultipleTransmissionMutex==simTime()) //if we've already entered this section at this time or the queue is empty
		{
		delete(self);
		return;
		}

	MultipleTransmissionMutex=simTime();

	frame = (Eth_Frame*)PacketQueue->pop(); //pop the next frame

	send(frame,"link$o",0); //send to the guard server
	scheduleAt(getParentModule()->gate("Guard_link$o")->getChannel()->getTransmissionFinishTime(),self); //reschedule to when the line clears

}//end of HandleBS_SelfEvent()


//Handles a message coming from the line or WiMAX layer at a base station
void Ethernet::HandleBS_NotSelfEvent(cMessage* msg)
{

	if (!strcmp(msg->getArrivalGate()->getBaseName(),"link")  )  //if the msg came from the line
		{
		Eth_Frame* packet = check_and_cast<Eth_Frame *>(msg);   //cast to Eth frame message
		send(packet->decapsulate(),"line_up$o"); //decaps and send onward to the WiMAX
		delete(packet);
		}
	else //this message came from the Wimax
		{

		UDP_IP_Packet* packet = check_and_cast<UDP_IP_Packet *>(msg);   //cast to Wimax frame message

		Eth_Frame* eth = new Eth_Frame();
		eth->setSrc(packet->getSrc());
		eth->setDst(packet->getDst());
		eth->setCall_ID(packet->getCall_ID());
		eth->setXpos(packet->getXpos());
		eth->setYpos(packet->getYpos());
		eth->setCommand(packet->getCommand());
		eth->setKind(packet->getKind());
		eth->encapsulate(packet);  //replace the wimax with eth
		eth->addByteLength(18); //add the eth header length

		PacketQueue->insert(eth); //enqueue

		cMessage* self = new cMessage();
		scheduleAt(max(simTime(),getParentModule()->gate("Guard_link$o")->getChannel()->getTransmissionFinishTime()),self);
		}

}//end of HandleBS_NotSelfEvent()

//Handles a message coming from the UDP/IP layer or the line at a server
void Ethernet::HandleServer(cMessage* msg)
{
	if (!strcmp(msg->getArrivalGate()->getBaseName(),"link")  )  //if the msg came from the line
		{
		Eth_Frame* packet = check_and_cast<Eth_Frame *>(msg);   //cast to Eth frame message
		send(packet->decapsulate(),"line_up$o");
		delete(packet);
		}

	else 												//this msg came from the UDP/IP
		{
		UDP_IP_Packet* packet = check_and_cast<UDP_IP_Packet *>(msg);   //cast to Eth frame message

		Eth_Frame* eth = new Eth_Frame();
		eth->setSrc(packet->getSrc());
		eth->setDst(packet->getDst());
		eth->setCall_ID(packet->getCall_ID());
		eth->setXpos(packet->getXpos());
		eth->setYpos(packet->getYpos());
		eth->setCommand(packet->getCommand());
		eth->setKind(packet->getKind());
		eth->encapsulate(packet);  //replace the wimax with eth
		eth->addByteLength(18); //add the eth header length

		PacketQueue->insert(eth);

		//Now, we have to schedule a self event according to which server and message this is

		cMessage* self = new cMessage();

		if(!strcmp(eth->getCommand(),"FLOOD") ) //if this is a FLOOD message. Guard server only
			{
			scheduleAt(max(simTime(),getParentModule()->gate("BS_link$o")->getChannel()->getTransmissionFinishTime()),self);
			return;
			}

		if(!strcmp(eth->getCommand(),"Register") ) //if this is a Register message. Guard server only
			{
			scheduleAt(max(simTime(),getParentModule()->gate("Registrar_link$o")->getChannel()->getTransmissionFinishTime()),self);
			return;
			}

		if(!strcmp(eth->getCommand(),"Register OK") ) //if this is a Register-reply message. Guard and Registrar servers
			{
			if(!strcmp(getParentModule()->getName(),"Registrar_S") )  //if we're at the registrar server
				scheduleAt(max(simTime(),getParentModule()->gate("Location_link$o")->getChannel()->getTransmissionFinishTime()),self);
			else //we're at the Guard server
				scheduleAt(max(simTime(),getParentModule()->gate("BS_link$o")->getChannel()->getTransmissionFinishTime()),self);
		    return;
			}

		if(!strcmp(eth->getCommand(),"HELLO") ) //if this is a HELLO message. Guard server only
			{
			scheduleAt(max(simTime(),getParentModule()->gate("Location_link$o")->getChannel()->getTransmissionFinishTime()),self);
		    return;
			}

		}

}//end of HandleServer()


//Handles a self event on a server. Sends a message according to which server this is and the message command type.
void Ethernet::HandleServerSelfEvent (cMessage* self)
{

	Eth_Frame* frame = (Eth_Frame*)PacketQueue->front();

	if (frame==NULL || MultipleTransmissionMutex==simTime()) //if we've already entered this section at this time or the queue is empty
		{
		delete(self);
		return;
		}

	frame = (Eth_Frame*)PacketQueue->pop(); //pop the next frame

	MultipleTransmissionMutex = simTime(); //update the entry time


	if(!strcmp(getParentModule()->getName(),"Registrar_S") )  //if we're at the registrar server
		{
		send(frame->dup(),"link$o",1); //send this message to the location server
		send(frame,"link$o",0); //a registrar server will send this msg to the guard, and a guard will send it to a BS
		scheduleAt(getParentModule()->gate("Guard_link$o")->getChannel()->getTransmissionFinishTime(),self);

		} //if registrar server

	if(!strcmp(getParentModule()->getName(),"Guard_S") )  //if we're at the guard server
		{
	    if (getParentModule()->gate("BS_link$o")->getChannel()->isBusy()) //if the channel is currently busy
	        {
	        scheduleAt(getParentModule()->gate("BS_link$o")->getChannel()->getTransmissionFinishTime(),self);
	        return;
	        }

		if (!strcmp(frame->getCommand(),"HELLO") ) //if this is a HELLO msg
			{
			send(frame,"link$o",2); //send this message to the location server
			scheduleAt(getParentModule()->gate("Location_link$o")->getChannel()->getTransmissionFinishTime(),self);
			}
		if (!strcmp(frame->getCommand(),"Register") ) //if this is a Register message
			{
			send(frame,"link$o",1); //send this message to the registrar server
			scheduleAt(getParentModule()->gate("Registrar_link$o")->getChannel()->getTransmissionFinishTime(),self);
			}
		if (!strcmp(frame->getCommand(),"Register OK") ) //if this is a Register OK message
			{
			send(frame,"link$o",0); //send this message to the BS
			scheduleAt(getParentModule()->gate("BS_link$o")->getChannel()->getTransmissionFinishTime(),self);
			}
		if (!strcmp(frame->getCommand(),"FLOOD") ) //if this is a FLOOD message
			{
			send(frame->dup(),"link$o",0); //send this message to the BS
			send(frame,"link$o",2); //send this message to the location server
			scheduleAt(getParentModule()->gate("BS_link$o")->getChannel()->getTransmissionFinishTime(),self);
			}

		} //if guard server
}//end of HandleServerSelfEvent()

