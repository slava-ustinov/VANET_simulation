


#ifndef CONTROL_H_
#define CONTROL_H_

#include "messages_m.h"
#include <cpacketqueue.h>
#include <string.h>

using namespace std;

struct Vehicle
{
  int gateIndex;
  bool isActive;
  int Xpos, Ypos;  //the coordinates of the vehicle
  int CurrentSpeed;
  bool isBreaking;
};

class Control : public cSimpleModule
{

	Vehicle** Vehicles;
	int NumOfLanes;
	int NumOfVehicles;
	int RoadLength;
	int SrvRange;
	double PixelsPerMeter;

    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void HandleVehicleRlocation(int, int, Control_msg*);
    void MoveLanesAndReturnControlMessage(int, int, Control_msg*,int);
    bool CheckIfCrashed(int,int,int);
    void SendControlMessageBack (int, int, bool, Control_msg*,int);
    int CheckIfWentOutOfRange (Control_msg*, int);



};

#endif
