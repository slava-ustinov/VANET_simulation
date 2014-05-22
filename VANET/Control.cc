/*
 * The control modules receives relocation request message from vehicles and replies with messages that contain the new location
 * and if they've crashed or not.
 * This is the only module in the simulation that has the full picture of vehicle positions on the road.
 */

#include <omnetpp.h>
#include <math.h>
#include "Control.h"
#include "messages_m.h"
#include <stdio.h>
#include <string.h>
#define SCREEN_WIDTH 1200
#define COLLISION_DISTANCE 5
#define UPPER_LANE_Y_LOCATION 275
#define RELOCATION_PERIOD 2       //done to calculate the vehicle displacement
#define IS_STATIC false      //Switches between static and moving vehicles

using namespace std;


// The module class needs to be registered with OMNeT++
Define_Module(Control);

/*

 */
void Control::initialize()
{

	NumOfLanes = getAncestorPar("NumOfLanes"); //get the number of lanes
	NumOfVehicles = par("NumOfVehicles");
	RoadLength = getAncestorPar("Road_Length");
	SrvRange = getAncestorPar("SRV_Transmission_Range");

	PixelsPerMeter=(double)SCREEN_WIDTH/RoadLength;  //the amount of pixels that represent a meter

	Vehicles = new Vehicle* [NumOfLanes];

	for (int i=0; i< NumOfLanes ;i++)  //init the vehicles
		{
		Vehicles[i] = new Vehicle[NumOfVehicles];
		for (int j=0; j<NumOfVehicles ;j++)
			{
			Vehicles[i][j].isActive=false;
			Vehicles[i][j].CurrentSpeed=110;
			}
		}


}//end of initialize()

/* Handles a vehicle relocation request.
 * Calculates a new location for the requesting vehicle considering it's speed, road length, lane switch probability,
 * collision events.
 */
void Control::HandleVehicleRlocation(int ArrYindex, int ArrXindex, Control_msg* ctrl)
{
	int dx, ProposedX, ProposedY;
    EV << "Current vehicle x: " <<  Vehicles[ArrYindex][ArrXindex].Xpos << " Current y: " << Vehicles[ArrYindex][ArrXindex].Ypos << "\n";

	if (ctrl->getIsBreaking()) //if this vehicle is currently breaking due to a crash or a received flood. While breaking, vehicles can't crash
		{
	    EV << "This vehicle is breaking!\n";
		Vehicles[ArrYindex][ArrXindex].CurrentSpeed= 60;  //the breaking speed is a steady 60 kmh
		Vehicles[ArrYindex][ArrXindex].isBreaking=true;
		dx = RELOCATION_PERIOD* 60*1000/3600;      //calc the distnace this vehicle has passed in the past 5 seconds
		ProposedX = (ctrl->getCurrentXpos()-dx); //calc the new X pos
		ProposedY = ArrYindex+1;                 //the lane stays the same
		EV << "New vehicle x: " <<  ProposedX << " New y: " << ProposedY << "\n";
		SendControlMessageBack(ProposedX,ProposedY,false,ctrl,ArrXindex);
		}
	else   //this vehicle isn't currently breaking
		{
		Vehicles[ArrYindex][ArrXindex].isBreaking=false;
		dx = RELOCATION_PERIOD* Vehicles[ArrYindex][ArrXindex].CurrentSpeed*1000/3600;      //calc the distnace this vehicle has passed in the past 5 seconds

		if (rand()%101 < ((double)getAncestorPar("P_laneswtich")*100 ))   //we give a 30% percent chance of switching lanes
			{	//on a lane switch, we never allow a collision
			MoveLanesAndReturnControlMessage(ArrYindex,ArrXindex,ctrl,dx);
			return;
			}
		//We didn't switch lanes

		ProposedX = (ctrl->getCurrentXpos()-dx); //calc the new X pos
		ProposedY = ArrYindex+1;                 //the lane stays the same

		bool isCrash = CheckIfCrashed(ArrXindex,ArrYindex,ProposedX);

		if (isCrash)  //if a crash occurred, the vehicel's location stays the same
			{
			EV << "Crashed!\n";
			Vehicles[ArrYindex][ArrXindex].CurrentSpeed= 60;
			Vehicles[ArrYindex][ArrXindex].isBreaking= true;
			EV << "New vehicle x: " <<  Vehicles[ArrYindex][ArrXindex].Xpos << " New y: " << Vehicles[ArrYindex][ArrXindex].Ypos << "\n";
			SendControlMessageBack(Vehicles[ArrYindex][ArrXindex].Xpos,Vehicles[ArrYindex][ArrXindex].Ypos,true,ctrl,ArrXindex); //location stays the same
			}//crashed
		else  //no crash occurred
			{
			EV << "Didn't crash!\n";
			if(ctrl->getIsCrazy())
				Vehicles[ArrYindex][ArrXindex].CurrentSpeed = 110 + (rand()%31)-15; //calc the new speed
			else
				Vehicles[ArrYindex][ArrXindex].CurrentSpeed = 110 + (rand()%11)-5; //calc the new speed

			Vehicles[ArrYindex][ArrXindex].isBreaking=false;
			Vehicles[ArrYindex][ArrXindex].Xpos = CheckIfWentOutOfRange(ctrl,ProposedX);
			Vehicles[ArrYindex][ArrXindex].Ypos = ProposedY;
			EV << "New vehicle x: " <<  Vehicles[ArrYindex][ArrXindex].Xpos << " New y: " << ProposedY << "\n";
			SendControlMessageBack(Vehicles[ArrYindex][ArrXindex].Xpos,ProposedY,false,ctrl,ArrXindex); //make sure we're in the SRV's range and send the msg

			}//didn't crash

		}

}//end of HandleVehicleRlocation()

//Sends back the update location for this vehicle. Location units are pixels ready to be used by 'SetDisplayString()'
void Control::SendControlMessageBack (int newX, int newY, bool isCrashed, Control_msg* ctrl,int GateIndex)
{

	ctrl->setCurrentXpos(newX);   //store the new X in meters
	ctrl->setCurrentYpos(newY);   //store the new lane as the lane's index
	ctrl->setRelocateToX(newX*PixelsPerMeter);  //set X location in pixels
	ctrl->setRelocateToY((newY-1)*100 +UPPER_LANE_Y_LOCATION);  //set Y location in pixels
	ctrl->setIsCrashed(isCrashed);

	Vehicles[newY-1][GateIndex].Xpos = newX;
	Vehicles[newY-1][GateIndex].Ypos = newY;

	send(ctrl,"link$o",GateIndex);
}//end of SendControlMessageBack()


//checks if the ProposedX position has caused this vehicle to crash with another
bool Control::CheckIfCrashed(int ArrXindex,int ArrYindex,int ProposedX)
{
	for (int i=0; i< NumOfVehicles ;i++)
		{   //important to remember, the X values decrease as the vehicles move forward
		if (Vehicles[ArrYindex][i].isActive && i!=ArrXindex) //if this entry is active and it's not this vehicle
			{
			if (abs(ProposedX-Vehicles[ArrYindex][ArrXindex].Xpos) < COLLISION_DISTANCE ||
			( (Vehicles[ArrYindex][ArrXindex].Xpos > Vehicles[ArrYindex][i].Xpos) && (ProposedX < Vehicles[ArrYindex][i].Xpos) 	)  )
		//if we're too close to the next vehicle or we've completely overtaken it
				{
				return true;
				}
			}
		}
	return false;
}//end of CheckIfCrashed()

//Moves the vehicle to a random lane. May move to the same lane. No crash may occur on lane switching.
void Control::MoveLanesAndReturnControlMessage(int ArrYindex, int ArrXindex, Control_msg* ctrl,int dx)
{
	EV << "Switching lanes!\n";

	int y = 1+(rand()%NumOfLanes); // y is in the range [1,NumOfLanes]
	Vehicles[ArrYindex][ArrXindex].isActive=false;
	Vehicles[y-1][ArrXindex].isActive=true;

	Vehicles[y-1][ArrXindex].isBreaking=Vehicles[ArrYindex][ArrXindex].isBreaking;
	Vehicles[y-1][ArrXindex].gateIndex=Vehicles[ArrYindex][ArrXindex].gateIndex;

	if(ctrl->getIsCrazy())
		Vehicles[y-1][ArrXindex].CurrentSpeed =  110 + (rand()%31)-15; //calc the new speed
	else
		Vehicles[y-1][ArrXindex].CurrentSpeed = 110 + (rand()%11)-5; //calc the new speed

	int x = CheckIfWentOutOfRange(ctrl,ctrl->getCurrentXpos()-dx); //get the final x location

	Vehicles[y-1][ArrXindex].Xpos=x;
	Vehicles[y-1][ArrXindex].Ypos=y;

	SendControlMessageBack(x,y,false,ctrl,ArrXindex);

}//end of MoveLanesAndReturnControlMessage()

/* Checks if the newly calculated location is out of the SRV's transmission range.
 * @return - a valid X location for this vehicle
 */
int Control::CheckIfWentOutOfRange (Control_msg* ctrl, int ProposedX)
{

	int SrvIndex = ctrl->getSRVindex(); //get the SRV's column

	if (SrvIndex==-1) //if this vehicle is an SRV
		return ProposedX;

	int SrvXlocation;
	for (int i=0; i< NumOfLanes ;i++) //search all the lanes for the associated SRV
		{
		if (Vehicles[i][SrvIndex].isActive)
			{
			SrvXlocation = 	Vehicles[i][SrvIndex].Xpos;
			break;
			}
		}
	if (ProposedX-SrvXlocation > SrvRange)  //we're behind the SRV's range
		{
		return (SrvXlocation-SrvRange+10);
		}
	if (SrvXlocation-ProposedX > SrvRange) //we're in front of the SRV's range
		{
		return (SrvXlocation+SrvRange-10);
		}

	return ProposedX;    //if we're not out of the SRV's range
}//end of CheckIfWentOutOfRange()


void Control::handleMessage(cMessage* msg)
{
    if (IS_STATIC)   //if we're testing the system at a static condition
        {
        delete(msg);
        return;
        }

	 Control_msg* ctrl = check_and_cast<Control_msg *>(msg); //cast
	 int x = ctrl->getCurrentXpos();
	 int y = ctrl->getCurrentYpos();

	 int ArrXindex = ctrl->getArrivalGate()->getIndex();
	 int ArrYindex = y-1;

	 Vehicles[ArrYindex][ArrXindex].Xpos = x;
	 Vehicles[ArrYindex][ArrXindex].Ypos = y;
	 Vehicles[ArrYindex][ArrXindex].gateIndex = ArrXindex;


	 if (!Vehicles[ArrYindex][ArrXindex].isActive) //every vehicle can be stored in one of 'NumOfLanes' arrays, representing it's current lane.
		 //each vehicle will always be stored at the same column, but the row can change depending on it's current lane.
		 {
		 EV << "New vehicle registered at location x: " << x << " y: " << y <<"\n";
		 Vehicles[ArrYindex][ArrXindex].isActive=true;
		 delete(msg);
		 }
	 else
		 {
		 EV << "Calculating a new location\n";
		 HandleVehicleRlocation(ArrYindex,ArrXindex,ctrl);
		 }

}//end of handleMessage()
