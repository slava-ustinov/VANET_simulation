/*
 * The Guard server's application layer protocol.
 * Keeps track of FLOOD messages across the network and makes sure all relevant FLOODs reach their destinations.
 */

#include <omnetpp.h>
#include <math.h>
#include "SIP_Guard.h"
#include "messages_m.h"
#include <stdio.h>
#include <string.h>
#define LOGLENGTH 1000
using namespace std;


// The module class needs to be registered with OMNeT++
Define_Module(SIP_Guard);

/*

 */
void SIP_Guard::initialize()
{
	FloodLog = new LogEntry[LOGLENGTH];  //create

	for (int i=0; i< LOGLENGTH; i++) //init
		{
		FloodLog[i].isValid=false;
		}

}//end of handleMessage();


void SIP_Guard::handleMessage(cMessage *msg)
{
	SIP* data = check_and_cast<SIP *>(msg);   //cast to SIP message
	string dst (data->getDst()); //create a string with the destination's name

		if(!strcmp(data->getCommand(),"FLOOD")) //if this is a FLOOD message
			{
			if (CheckIfThisFLOODisNew(data)) //if this is a new FLOOD message
				send(data,"line_down$o");  //this message has to be sent to the location server and back to the BS, the ETH will take care of that

			else
				delete(data);
			}//if FLOOD
		else   //this isn't a FLOOD message
			send(data,"line_down$o"); //let the ETH to handle the routing


}//end of handleMessage();

//Checks if this FLOOD message is a new one. If so, sends it down to the UDP/IP layer.
bool SIP_Guard::CheckIfThisFLOODisNew (SIP* data)
{
	for (int i=0; i<LOGLENGTH ;i++)
		{
		if (FloodLog[i].isValid && data->getCall_ID()==FloodLog[i].Call_ID) //if already have a flood entry with the same ID
			return false;

		if(!FloodLog[i].isValid) //if this entry wasn't initialized yet -> this is a valid new FLOOD
			{
			FloodLog[i].isValid=true;
			FloodLog[i].Call_ID = data->getCall_ID();
			FloodLog[i].time = simTime();
			return true;
			}
		}
	return true;
}//end of CheckIfThisFLOODisNew()
