/*
 * Represents an AV on-board computer, that runs a SIP client application, has information
 * about the vehicle's location and generates FLOOD messages on collisions.
 * The movement across the road is done by communicating with the control_unit module.
 */

#include <omnetpp.h>
#include <math.h>
#include "AV_OnBoard_Computer.h"
#include "messages_m.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define UPPER_LANE_Y_LOCATION 250
#define RELOCATION_PERIOD 1

using namespace std;


// The module class needs to be registered with OMNeT++
Define_Module(AV_OnBoard_Computer);

/*

 */
void AV_OnBoard_Computer::initialize()
{

	string temp = "AV";
	char temp2[10];
	sprintf(temp2,"%d",getParentModule()->getIndex()); //convert the index to a string
	temp += temp2;                                    //temp now contains this AV's name string

	HelloMsgPeriodInSec = (double)getAncestorPar("Keep_Alive_Msg_Period");
	isCrazy=false;

	if(rand()%101 < (int)getAncestorPar("PercentageOfCrazyDrivers")) //check if this is a crazy driver
		isCrazy=true;

	LastFloodEventTime = -1000000;

	Name = temp;
	isInitialized=false;
	isRegsitered=false;

	FloodPropagationTimes.setName("Flood propagation times");
	LastFLOODmsgID=-1;

}//end of handleMessage();


void AV_OnBoard_Computer::handleMessage(cMessage *msg)
{
	if(!isInitialized)
		{
		SIP* init = check_and_cast<SIP *>(msg);   //cast to SIP message
		Init(init);
		isInitialized=true;  //init is complete
		delete(msg); //delete this message
		return;
		}

	if (!msg->isSelfMessage())
		{
		HandleNotSelfMsgHandler(msg);
		}

	else
		{
		handleSelfEvent(msg);
		}


}//end of handleMessage();


//Handles messages coming from the UDP/IP layer or the control_unit
void AV_OnBoard_Computer::HandleNotSelfMsgHandler(cMessage* msg)
{

	if (!strcmp(msg->getArrivalGate()->getBaseName(),"line_down")  )  //if the msg came from the UDP_IP layer
		{
		SIP* data = check_and_cast<SIP *>(msg);   //cast to SIP

		if (!strcmp(data->getCommand(),"FLOOD") ) //if this message is a FLOOD message
			HandleFloodMessage(data);

		else  //this is a register reply message
			{
			isRegsitered=true;
			}
		// SIP_PROXY doesn't change any of the field of the original message, which has the AV as source and the SRV as destination
		}//if this msg came from the UDP_IP layer

	else //this message came from the control module
		{
		Control_msg* ctrl = check_and_cast<Control_msg *>(msg);
		HandleControlMsg(ctrl);
		}

	delete(msg);

}//end of HandleNotSelfMsgHandler()

//Handles incoming control messages. Moves the vehicle across the road and generates FLOOD messages.
void AV_OnBoard_Computer::HandleControlMsg(Control_msg* ctrl)
{
	UpdateDisplayString(ctrl->getRelocateToX(),ctrl->getRelocateToY(),ctrl->getIsBreaking());
	Xpos = ctrl->getCurrentXpos();
	Ypos = ctrl->getCurrentYpos();

	EV << "New Xpixel = " << ctrl->getRelocateToX() << " New Ypisxel = "<< ctrl->getRelocateToY() <<
			"New X = " << Xpos << "New Y = " << Ypos <<"\n";

	if (ctrl->getIsCrashed()) //if an accident has occurred right now
		{
		getParentModule()->bubble("CRASHED! FLOODING!");
		LastFloodEventTime = simTime(); //mark that a crash has just occured

		  //Create and send a FLOOD message
		  SIP* flood = new SIP();
		  flood->setCommand("FLOOD");
		  flood->setSrc(Name.c_str());
		  flood->setDst(SRVName.c_str());
		  flood->setXpos(Xpos);
		  flood->setYpos(Ypos);
		  flood->setCall_ID(rand()%80000);
		  flood->setByteLength(300);
		  flood->setKind(0); //color the FLOOD messages red
		  flood->setTimestamp();  //set the timestamp
		  send(flood,"line_down$o");

		}
}//end of HandleControlMsg()


//Updates this AV's display string, thus moving it across the simulation GUI.
void AV_OnBoard_Computer::UpdateDisplayString(int Xpixels, int Ypixles,bool isBreaking)
{
	string Display = "p=";
	char temp[10];
	sprintf(temp,"%d",Xpixels);

	Display+=temp;
	Display += ",";

	sprintf(temp,"%d",Ypixles);
	Display+=temp;

    if (!strcmp(SRVName.c_str(),"inactive")) //if inactive, color it red
        Display += ";i=block/star,red";
    else //if active
        {
        if(!isBreaking)                 //if this vehicle isn't breaking
            Display += ";i=block/star,green";
        else
            Display += ";i=block/star,yellow";
        }

	EV << "New display string is: " <<Display <<"\n";
	getParentModule()->setDisplayString(Display.c_str()); //set the AV's display string
}//end of UpdateDisplayString()


//Handles incoming FLOOD messages. Checks if this FLOOD message is new and changes the vehicle's speed accordingly
void AV_OnBoard_Computer::HandleFloodMessage(SIP* msg)
{
	if (Xpos > msg->getXpos())   //if this AV is behind the event
	    LastFloodEventTime = simTime(); //mark the time this FLOOD was received

	//The next condition makes sure a FLOOD propagation time will only be recorded once
	if (msg->getCall_ID()!=LastFLOODmsgID) //if this is a new FLOOD message
        {
	    LastFLOODmsgID=msg->getCall_ID();
        FloodPropagationTimes.record(simTime()-msg->getTimestamp()); //record the prop. time for this flood message
        }

}//end of HandleFloodMessage()

//Handles self messages
void AV_OnBoard_Computer::handleSelfEvent(cMessage* msg)
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


//Sends a relocation request message to the control unit
void AV_OnBoard_Computer::CreateAndSendARelocationMsg()
{

 //Create and send a control message
	  Control_msg* ctrl = new Control_msg();
	  ctrl->setCurrentXpos(Xpos);
	  ctrl->setCurrentYpos(Ypos);
	  ctrl->setIsCrazy(isCrazy);
	  if (!strcmp(SRVName.c_str(),"inactive"))
	      ctrl->setSRVindex(-1);        //make an inactive vehicle act as an SRV
	  else
	      ctrl->setSRVindex(SRVName.at(3)-'0'); //get the SRV's index
	  ctrl->setIsCrashed(false);
	  ctrl->setKind(7);
	  ctrl->setIsBreaking(false);

	  if (SIMTIME_DBL(simTime()-LastFloodEventTime) < 2) //if the last FLOOD event was less than 2 seconds ago
		  ctrl->setIsBreaking(true);   //notify that this vehicle is traveling in regular speed

	  send(ctrl,"control$o");
}//end of CreateAndSendARelocationMsg()

//Creates and send a new HELLO message to the SRV
void AV_OnBoard_Computer::CreateAndSendAHelloMsg ()
{
	  //Create and send a HELLO message
	  SIP* Hello_msg = new SIP();
	  Hello_msg->setCommand("HELLO");
	  Hello_msg->setSrc(Name.c_str());
	  Hello_msg->setDst(SRVName.c_str());
	  Hello_msg->setXpos(Xpos);
	  Hello_msg->setYpos(Ypos);
	  Hello_msg->setCall_ID(rand()%40000);
	  Hello_msg->setByteLength(300);
	  Hello_msg->setKind(4); //color the register messages yellow
	  send(Hello_msg,"line_down$o");
}//end of CreateAndSendAHelloMsg()

//Receives the location and SRV information from the WiMAX
void AV_OnBoard_Computer::Init(SIP *msg)
{
  Xpos = msg->getXpos();
  Ypos = msg->getYpos();
  SRVName = msg->getSrc(); //in case this AV is inactive, it'll receive the value "inactive"

  //create and send an initial message to the control module
  Control_msg* ctrl = new Control_msg();
  ctrl->setCurrentXpos(Xpos);
  ctrl->setCurrentYpos(Ypos);
  ctrl->setIsCrazy(isCrazy);
  ctrl->setIsCrashed(false);
  ctrl->setIsBreaking(false);
  ctrl->setKind(7);

  send(ctrl,"control$o");

  //Create and send a register message
  SIP* Register_msg = new SIP();
  Register_msg->setCommand("Register");
  Register_msg->setSrc(Name.c_str());
  Register_msg->setDst(SRVName.c_str());
  Register_msg->setXpos(Xpos);
  Register_msg->setYpos(Ypos);
  Register_msg->setCall_ID(rand()%40000);
  Register_msg->setByteLength(381);
  Register_msg->setKind(3); //color the register messages white
  sendDelayed(Register_msg,(double)(rand()%11)/10,"line_down$o");

  SIP_Self_msg* selfmsg = new SIP_Self_msg();
  SIP_Self_msg* selfmsg_ = selfmsg->dup();
  selfmsg->setIsTimeForHello(true);
  selfmsg->setIsTimeToRelocate(false);
  scheduleAt(simTime()+(rand()%11)/10+HelloMsgPeriodInSec, selfmsg);  //schedule a HELLO msg

  selfmsg_->setIsTimeForHello(false);
  selfmsg_->setIsTimeToRelocate(true);
  scheduleAt(simTime()+RELOCATION_PERIOD, selfmsg_);  //schedule a relocation in 5 sec

}//end of Init()
