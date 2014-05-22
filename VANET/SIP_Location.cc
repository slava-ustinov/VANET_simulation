/*
 * The Location server's application layer protocol. Does nothing.
 */

#include <omnetpp.h>
#include <math.h>
#include "SIP_Location.h"
#include "messages_m.h"
#include <stdio.h>
#include <string.h>

using namespace std;


// The module class needs to be registered with OMNeT++
Define_Module(SIP_Location);

/*

 */
void SIP_Location::initialize()
{


}//end of handleMessage();


void SIP_Location::handleMessage(cMessage *msg)
{

	delete(msg);

}//end of handleMessage();


