message Control_msg
{
    int CurrentXpos;
    int CurrentYpos;
    int SRVindex;
    bool isBreaking;
    bool isCrashed;
    bool isCrazy;
    int RelocateToX;
    int RelocateToY;
}


message WiMAX_SelfMsg
{	
    bool isTimeOut;
    bool isFLOOD; //indicates whether this self event is related to a FLOOD msg
    int QueueIndex;
    int Call_ID;
    bool isFinishedFlooding;
}

message InitMsg
{
 string SourceName;
 int SrcXPos;
 int SrcYPos;
}

packet SIP 
{
    string command;
    string src;
    string dst;
    int HandlingSRVindex;
    int Xpos;
    int Ypos;
    int Call_ID;
}

packet SIP_Self_msg
{
    bool isTimeForHello;
    bool isTimeToRelocate;
}

packet Wimax_Frame
{
    bool isFLOOD;
    bool isCorrupted;
    bool isACK;
    int Call_ID;
    int Xpos;
    int Ypos;
    string src;
    string dst;
    
}

packet Eth_Frame
{
    string command;
    int Call_ID;
    int Xpos;
    int Ypos;
    string src;
    string dst;
}

packet UDP_IP_Packet
{
    string command;
    string src;
    string dst;
    int Call_ID;
    int Xpos;
    int Ypos;
    int HandlingSRVindex;
}
