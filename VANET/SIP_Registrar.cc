/*
 * The Registrar server's application layer protocol. Replies to Register request messages.
 */

#include <omnetpp.h>
#include <math.h>
#include "SIP_Registrar.h"
#include "messages_m.h"
#include <stdio.h>
#include <string.h>

using namespace std;


// The module class needs to be registered with OMNeT++
Define_Module(SIP_Registrar);

/*

 */
void SIP_Registrar::initialize()
{


}//end of handleMessage();


void SIP_Registrar::handleMessage(cMessage *msg)
{
	SIP* request = check_and_cast<SIP *>(msg);   //cast to SIP message

	request->setCommand("Register OK");
	request->setDst(request->getSrc());  //this message is to be sent back to the sender
	request->setSrc("BS");   //set source as if it's the BS. that's just how we've designed it.

	send(request,"line_down$o");


}//end of handleMessage();


