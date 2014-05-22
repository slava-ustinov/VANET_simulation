/*
 * The SRV's application layer protocol. In charge of relaying messages from the core network to the AVs and vice versa.
 * Relocated along the road by messaging the control unit.
 */

#include <omnetpp.h>
#include <math.h>
#include "SIP_Proxy.h"
#include "messages_m.h"
#include <stdio.h>
#include <string.h>
#define LOGLENGTH 1000
#define RELOCATION_PERIOD 2

using namespace std;


// The module class needs to be registered with OMNeT++
Define_Module(SIP_Proxy);


void SIP_Proxy::initialize()
{

	string temp = "SRV";
	temp += (char)(getParentModule()->getIndex()+'0');

	Name = temp;
	isInitialized=false;

    SrvRange = getAncestorPar("SRV_Transmission_Range");

	FloodLog = new LogEntry[LOGLENGTH];  //create

	for (int i=0; i< LOGLENGTH; i++) //init
		{
		FloodLog[i].isValid=false;
		}

	LastFloodEventTime = -1000000;
	HelloMsgPeriodInSec = (double)getAncestorPar("Keep_Alive_Msg_Period");

	TotalNumberOfFloods=0;
	TotalNumberOfFloodsVector.setName("Total number of different FLOODs at SRV");


}//end of handleMessage();


void SIP_Proxy::handleMessage(cMessage *msg)
{
	if(!isInitialized)
		{
		SIP* init = check_and_cast<SIP *>(msg);   //cast to SIP message
		Init(init);
		isInitialized=true;  //init is complete
		return;
		}

	if (!msg->isSelfMessage())
		HandleNotSelfMsgHandler(msg);

	else
		handleSelfEvent(msg);


}//end of handleMessage()

//Handles a message coming from the UDP/IP layer or from the control unit
void SIP_Proxy::HandleNotSelfMsgHandler(cMessage* msg)
{

	if (!strcmp(msg->getArrivalGate()->getBaseName(),"line_down")  )  //if the msg came from the UDP_IP layer
		{
		SIP* data = check_and_cast<SIP *>(msg);   //cast to SIP

		if (!strcmp(data->getCommand(),"FLOOD") ) //if this message is a FLOOD message
			{
			HandleFloodMessage(data);
			}

		else  //this is a regular message
			{
			if ( (!strcmp(data->getSrc(),"BS") && !strcmp(data->getDst(),Name.c_str())) || (!strcmp(data->getCommand(),"HELLO")) )
				//if this message is designated to the BS (Happens only with Register-reply messages)
				//or this is a HELLO message from an AV
				{
				delete(data);
				}

				else
				{
				data->setHandlingSRVindex(getParentModule()->getIndex()); //enter the index of the SRV that handles this relay
				send(msg,"line_down$o");  //send it as it is. Currently dst="SRV" but the Wimax will know to relay it to the BS.
				}
			}
		// SIP_PROXY doesn't change any of the field of the original message, which has the AV as source and the SRV as destination
		}//if this msg came from the UDP_IP layer

	else //this message came from the control module
		{
		Control_msg* ctrl = check_and_cast<Control_msg *>(msg);
		HandleControlMsg(ctrl);
		}
}//end of HandleNotSelfMsgHandler()


/*Handles a received control message. Relocates according to the calculation of the control unit.
 * May also be notified that it has crashed, on which case it colors itself yellow.
*/
void SIP_Proxy::HandleControlMsg(Control_msg* ctrl)
{
	UpdateDisplayString(ctrl->getRelocateToX(),ctrl->getRelocateToY(), ctrl->getIsBreaking());
	Xpos = ctrl->getCurrentXpos();
	Ypos = ctrl->getCurrentYpos();

	EV << "New Xpixel = " << ctrl->getRelocateToX() << " New Ypisxel = "<< ctrl->getRelocateToY() <<
			"New X = " << Xpos << "New Y = " << Ypos <<"\n";

	if (ctrl->getIsCrashed()) //if an accident has occurred right now
		{
	    TotalNumberOfFloods++;

		getParentModule()->bubble("CRASHED! FLOODING!");
		LastFloodEventTime = simTime(); //mark that a crash has just occured

		  //Create and send a FLOOD message
		  SIP* flood = new SIP();
		  flood->setCommand("FLOOD");
		  flood->setSrc(Name.c_str());
		  flood->setDst("BS");
		  flood->setXpos(Xpos);
		  flood->setYpos(Ypos);
		  flood->setCall_ID(rand()%40000);
		  flood->setByteLength(300);
		  flood->setTimestamp();  //set the timestamp
		  flood->setKind(0); //color the FLOOD messages red
		  send(flood,"line_down$o");

		  CheckIfThisFLOODisNew(flood);  //log this flood message
		} //if crashed



	delete(ctrl);
}//end of HandleControlMsg()


//Updates the parent module's display string.
void SIP_Proxy::UpdateDisplayString(int Xpixels, int Ypixles, bool isBreaking)
{
	string Display = "p=";
	char temp[10];
	sprintf(temp,"%d",Xpixels);

	Display+=temp;
	Display += ",";

	sprintf(temp,"%d",Ypixles);
	Display+=temp;

	if(!isBreaking)   //if this SRV isn't breaking
	    Display += ";i=block/broadcast";
	else
	    Display += ";i=block/broadcast,yellow";

	EV << "New display string is: " <<Display <<"\n";
	getParentModule()->setDisplayString(Display.c_str()); //set the AV's display string
}//end of UpdateDisplayString()


//Handles a self message
void SIP_Proxy::handleSelfEvent(cMessage* msg)
{
	SIP_Self_msg* self = check_and_cast<SIP_Self_msg *>(msg); //cast

	if(self->getIsTimeForHello()) //if we need to send a new HELLO msg
		{
		CreateAndSendAHelloMsg();
		scheduleAt(simTime()+HelloMsgPeriodInSec,msg); //schedule a HELLO msg
		}
	else  //we need to relocate
		{
		CreateAndSendARelocationMsg();
		scheduleAt(simTime()+RELOCATION_PERIOD, msg);  //schedule a relocation in 5 sec
		}
}//end of handleSelfEvent()


//Handles a FLOOD message incoming from the UDP/IP
void SIP_Proxy::HandleFloodMessage(SIP* msg)
{

	if (!CheckIfThisFLOODisNew(msg)) //if we've already received this flood message
		delete(msg);

	else //this is a new flood message
		{
	    if (!strcmp(msg->getDst(),Name.c_str())) //we want to count only the flood that are created by this SRV or his AVs only.
	        {
	        TotalNumberOfFloods++;
	        }

	    if (Xpos > msg->getXpos())   //if this AV is behind the event
	        LastFloodEventTime = simTime(); //mark the time this FLOOD was received

		if(msg->getXpos() < Xpos+SrvRange) //if this SRV covers an area affected by the crash
		    {
		    EV << "A new flood event is within range!\n";
		    EV << "Current location is X: " << Xpos << " Y: " << Ypos << "\n";
		    send(msg,"line_down$o"); //send this message to the UDP/IP layer
		    }
		else
		    {
		    EV << "The new flood event is out of  range!\n";
		    EV << "Current location is X: " << Xpos << " Y: " << Ypos << "\n";
		    delete(msg);
		    }
		}
}//end of HandleFloodMessage()


//Checks if this FLOOD message's Call_ID is seen for the 1st time at this SRV
bool SIP_Proxy::CheckIfThisFLOODisNew (SIP* data)
{
	EV << "Checking if this FLOOD is new!\n";

	for (int i=0; i<LOGLENGTH ;i++)
		{
		if (FloodLog[i].isValid && data->getCall_ID()==FloodLog[i].Call_ID) //if already have a flood entry with the same ID
			{
			return false;
			}

		if(!FloodLog[i].isValid) //if this entry wasn't initialized yet -> this is a valid new FLOOD
			{
			FloodLog[i].isValid=true;
			FloodLog[i].Call_ID = data->getCall_ID();
			FloodLog[i].time = simTime();
			return true;
			}
		}//for
	return true;
}//end of CheckIfThisFLOODisNew()

//Receives the location and SRV information from the WiMAX
void SIP_Proxy::Init(SIP *msg)
{
  Xpos = msg->getXpos();
  Ypos = msg->getYpos();
  delete(msg);

  SIP* Register_msg = new SIP();

  Register_msg->setCommand("Register");
  Register_msg->setSrc(Name.c_str());
  Register_msg->setDst("BS");
  Register_msg->setXpos(Xpos);
  Register_msg->setYpos(Ypos);
  Register_msg->setCall_ID(rand()%40000);
  Register_msg->setHandlingSRVindex(getParentModule()->getIndex());
  Register_msg->setKind(3); //color the register messages white
  send(Register_msg,"line_down$o");

  //create and send an initial message to the control module
  Control_msg* ctrl = new Control_msg();
  ctrl->setCurrentXpos(Xpos);
  ctrl->setCurrentYpos(Ypos);
  ctrl->setIsCrazy(false);
  ctrl->setIsBreaking(false);
  ctrl->setKind(7);

  send(ctrl,"control$o");


  SIP_Self_msg* selfmsg = new SIP_Self_msg();
  SIP_Self_msg* selfmsg_ = selfmsg->dup();
  selfmsg->setIsTimeForHello(true);
  selfmsg->setIsTimeToRelocate(false);
  scheduleAt(simTime()+(rand()%11)/10+HelloMsgPeriodInSec, selfmsg);  //schedule a HELLO msg

  selfmsg_->setIsTimeForHello(false);
  selfmsg_->setIsTimeToRelocate(true);
  scheduleAt(simTime()+RELOCATION_PERIOD, selfmsg_);  //schedule a relocation in 5 sec

}//end of Init()

//Sends a relocation request message up to the control unit
void SIP_Proxy::CreateAndSendARelocationMsg()
{

 //Create and send a control message
	  Control_msg* ctrl = new Control_msg();
	  ctrl->setCurrentXpos(Xpos);
	  ctrl->setCurrentYpos(Ypos);
	  ctrl->setIsCrazy(false);
	  ctrl->setSRVindex(-1);  //SRVs set their index as -1
	  ctrl->setIsCrashed(false);
	  ctrl->setKind(7);
	  ctrl->setIsBreaking(false);

	  if (SIMTIME_DBL(simTime()-LastFloodEventTime) < 2) //if the last FLOOD event was less than 2 seconds ago
		  ctrl->setIsBreaking(true);   //notify that this vehicle is traveling in regular speed

	  send(ctrl,"control$o");
}//end of CreateAndSendARelocationMsg()

//Sends a HELLO message down to the UDP/IP
void SIP_Proxy::CreateAndSendAHelloMsg ()
{
	  //Create and send a HELLO message
	  SIP* Hello_msg = new SIP();
	  Hello_msg->setCommand("HELLO");
	  Hello_msg->setSrc(Name.c_str());
	  Hello_msg->setDst("BS");
	  Hello_msg->setXpos(Xpos);
	  Hello_msg->setYpos(Ypos);
	  Hello_msg->setCall_ID(rand()%40000);
	  Hello_msg->setByteLength(300);
	  Hello_msg->setKind(4); //color the HELLO messages yellow
	  send(Hello_msg,"line_down$o");
}//end of CreateAndSendAHelloMsg()

//record the statistics
void SIP_Proxy::finish ()
{
    TotalNumberOfFloodsVector.record(TotalNumberOfFloods);   //record the total number of FLOOD packets at this station
}
