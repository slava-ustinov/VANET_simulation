/*
 * Simulated the 3rd and 4th level protocols. Only encapsulates and decapsulates data that passes through it.
 */

#include <omnetpp.h>
#include <math.h>
#include "UDP_IP.h"
#include "messages_m.h"
#include <stdio.h>
#include <string.h>

using namespace std;


// The module class needs to be registered with OMNeT++
Define_Module(UDP_IP);

/*

 */
void UDP_IP::initialize()
{

}//end of handleMessage();


void UDP_IP::handleMessage(cMessage *msg)
{
	if (!strcmp(msg->getArrivalGate()->getBaseName(),"line_up")  )  //if the msg came from the SIP
		{
		SIP* sip_data = check_and_cast<SIP *>(msg);   //cast to sip

		UDP_IP_Packet* packet  = new UDP_IP_Packet;       //create a new packet and copy the fields
		packet->setCommand(sip_data->getCommand());
		packet->setSrc(sip_data->getSrc());
		packet->setDst(sip_data->getDst());
		packet->setCall_ID(sip_data->getCall_ID());
		packet->setXpos(sip_data->getXpos());
		packet->setYpos(sip_data->getYpos());
		packet->setHandlingSRVindex(sip_data->getHandlingSRVindex());
		packet->setKind(sip_data->getKind());

		packet->encapsulate(sip_data);
		packet->addByteLength(20+4);   //add the length of the IP and UDP headers

		send(packet,"line_down$o");  //send the frame down to the WiMAX
		}
	else    //this msg came from the WiMAX
		{
		UDP_IP_Packet* frame = check_and_cast<UDP_IP_Packet *>(msg);   //cast to WiMAX frame

		send(frame->decapsulate(),"line_up$o");   //send the decapsulated data to the SIP
		delete(frame);   //remove the frame
		}

}//end of handleMessage()


