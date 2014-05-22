

package vanet;

simple Control
{
    parameters:
        int NumOfVehicles;
    gates:
        inout link[NumOfVehicles];
}

simple WiMAX
{
    parameters:
        int type;  //type = 1 means AV, type = 2 means SRV, type = 3 means BS.
        int NumOfFrequencies;
    gates:
        inout line_up;
        inout link[NumOfFrequencies];      //set a dynamic link array, since we don't know how many connectins there will be.
}

simple Ethernet
{
    parameters:
        int type;
        int NumOfLinks;
    gates:
        inout line_up;
        inout link[NumOfLinks];
}

simple UDP_IP
{
    gates:
        inout line_up;
        inout line_down;
}

simple SIP_Guard
{
    gates:
        inout line_down;
}

simple SIP_Registrar
{
    gates:
        inout line_down;
}

simple SIP_Location
{
    gates:
        inout line_down;
}

simple SIP_Proxy
{
    gates:
        inout line_down;
        inout control;
}

simple AV_OnBoard_Computer
{
    parameters:
        int KeepAliveMsgPeriod;
    gates:
        inout line_down;
        inout control;
}

module AV
{
    parameters:
        int Xpos;
        int Ypos;
        int Keep_Alive_Time;
    gates:
        inout Gates[1];
        inout control;
    submodules:
        comp: AV_OnBoard_Computer {
            KeepAliveMsgPeriod = Keep_Alive_Time;
            @display("p=65,47");
        }
        udp_ip: UDP_IP {
            @display("p=65,119");
        }
        wimax: WiMAX {
            type = 1;
            NumOfFrequencies = 1;
            @display("p=65,202");
        }
    connections:
        comp.line_down <--> udp_ip.line_up;
        udp_ip.line_down <--> wimax.line_up;
        wimax.link[0] <--> Gates[0];
        comp.control <--> control;
}

module SRV
{
    parameters:
        int NumOfAvs;
        int NumOfFreq;
        int Xpos;
        int Ypos;
    gates:
        inout Gates[NumOfAvs+1]; //the max amount of gates is the amount of AVs +1 (for the BS)
        inout control;

    submodules:
        sip: SIP_Proxy {
            @display("p=57,46");
        }
        udp_ip: UDP_IP {
            @display("p=57,121");
        }
        wimax: WiMAX {
            type = 2;
            NumOfFrequencies = NumOfFreq; //max amount of AVs + BS
            @display("p=57,196");
        }

    connections allowunconnected:
        sip.line_down <--> udp_ip.line_up;
        udp_ip.line_down <--> wimax.line_up;
        sip.control <--> control;


        for i=0..NumOfAvs {
            wimax.link[i] <--> Gates[i] if NumOfAvs<NumOfFreq;
        }

        for i=0..NumOfFreq-1 {
            wimax.link[i] <--> Gates[i] if NumOfAvs>=NumOfFreq;
        }

}

module BS
{
    parameters:
        int NumOfSRVz;
        int Xpos;
        int Ypos;
    gates:
        inout Gates[NumOfSRVz];
        inout Guard_link;
    submodules:
        eth: Ethernet {
            NumOfLinks = 1;
            type = 2;
            @display("p=182,88");
        }
        wimax: WiMAX {
            type = 3;
            NumOfFrequencies = NumOfSRVz;
            @display("p=93,88");
        }
    connections:
        eth.line_up <--> wimax.line_up;
        eth.link[0] <--> Guard_link;

        for i=0..NumOfSRVz-1 {
            wimax.link[i] <--> Gates[i];
        }

}

module Guard_Server
{
    parameters:

    gates:
        inout BS_link;
        inout Registrar_link;
        inout Location_link;
    submodules:
        sip: SIP_Guard {
            @display("p=60,51");
        }
        udp_ip: UDP_IP {
            @display("p=60,141");
        }
        eth: Ethernet {
            type = 4;
            NumOfLinks = 3;
            @display("p=60,239");
        }
    connections:
        sip.line_down <--> udp_ip.line_up;
        udp_ip.line_down <--> eth.line_up;
        eth.link[0] <--> BS_link;
        eth.link[1] <--> Registrar_link;
        eth.link[2] <--> Location_link;
}

module Registrar_Server
{
    parameters:

    gates:
        inout Guard_link;
        inout Location_link;
    submodules:
        sip: SIP_Registrar {
            @display("p=70,49");
        }
        udp_ip: UDP_IP {
            @display("p=70,131");
        }
        eth: Ethernet {
            type = 4;
            NumOfLinks = 2;
            @display("p=70,216");
        }
    connections:
        sip.line_down <--> udp_ip.line_up;
        udp_ip.line_down <--> eth.line_up;
        eth.link[0] <--> Guard_link;
        eth.link[1] <--> Location_link;
}

module Location_Server
{
    parameters:

    gates:
        inout Guard_link;
        inout Registrar_link;
    submodules:
        sip: SIP_Location {
            @display("p=75,41");
        }
        udp_ip: UDP_IP {
            @display("p=75,131");
        }
        eth: Ethernet {
            type = 4;
            NumOfLinks = 2;
            @display("p=75,223");
        }
    connections:
        sip.line_down <--> udp_ip.line_up;
        udp_ip.line_down <--> eth.line_up;
        eth.link[0] <--> Guard_link;
        eth.link[1] <--> Registrar_link;
}

network vanet
{
    parameters:
        int Road_Length;   // the length of the simulated road segment
        int Num_Of_SRVs;
        int Num_Of_AVs_Per_SRV;
        int Amount_Of_Frequencies_At_SRV;   //since we work with OFDM, there is a limited amount of AVs a SRV can support
        int SRV_Transmission_Range;
        double Emergency_FLOOD_Transmission_Time_In_Seconds;   //a Bcast message will be flooded for 64*this_time seconds
        double Keep_Alive_Msg_Period;
        int NumOfLanes;
        int PercentageOfCrazyDrivers;
        double P_laneswtich;
        int WimaxQueueSize;

        @display("bgb=1500,600,grey30;t=VANET;bgg=250,05,#CD9405");
    types:
        channel ETH_Channel extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            @display("ls=black,2,s");
        }
        channel Wireless_Channel extends ned.DatarateChannel
        {
            datarate = 40Mbps;
            @display("ls=blue,1,da");
        }
        channel Control_Channel extends ned.DatarateChannel
        {
            @display("ls=blue,0,da"); //set as invisible
        }

    submodules:

        Control_Unit: Control {
            NumOfVehicles = (Num_Of_AVs_Per_SRV+1)*Num_Of_SRVs;
            @display("p=574,21;i=old/telnet");
        }

        AV[Num_Of_AVs_Per_SRV*Num_Of_SRVs]: AV {
            Keep_Alive_Time = Keep_Alive_Msg_Period;
            Xpos = -1;
            Ypos = -1;
            @display("p=116,92");
        }

        SRV[Num_Of_SRVs]: SRV {
            NumOfAvs = Num_Of_AVs_Per_SRV;
            NumOfFreq = Amount_Of_Frequencies_At_SRV;
            Xpos = uniform(0, Road_Length+1);
            Ypos = uniform(1, NumOfLanes+1);
            @display("p=281,140");
        }

        BS: BS {
            NumOfSRVz = Num_Of_SRVs;
            Xpos = uniform(0, Road_Length);
            Ypos = 0;
            @display("p=873,62;i=msg/bcast");
        }

        Guard_S: Guard_Server {
            @display("p=1027,27;i=device/server2");
        }
        Registrar_S: Registrar_Server {
            @display("p=1124,80;i=device/server2");
        }
        Location_S: Location_Server {
            @display("p=1225,27;i=device/server2");
        }

    connections allowunconnected:

        for i=0..Num_Of_SRVs-1, for j=0..Num_Of_AVs_Per_SRV-1 {
            AV[(Num_Of_AVs_Per_SRV * i)+j].Gates[0] <--> Wireless_Channel <--> SRV[i].Gates[j+1] if j < Amount_Of_Frequencies_At_SRV-1; //1 freq. per SRV is dedicated to the BS
        }

        for i=0..Num_Of_SRVs-1 {
            SRV[i].Gates[0] <--> Wireless_Channel <--> BS.Gates[i];         //connect all SRVs to the BS
            Control_Unit.link[i] <--> Control_Channel <--> SRV[i].control;                       //link all SRVs to the control module
        }

        for i=0..Num_Of_AVs_Per_SRV*Num_Of_SRVs-1 {
            AV[i].control <--> Control_Channel <--> Control_Unit.link[i+Num_Of_SRVs]; //link all AVs to the control module
        }

        BS.Guard_link <--> ETH_Channel <--> Guard_S.BS_link;
        Guard_S.Registrar_link <--> ETH_Channel <--> Registrar_S.Guard_link;
        Guard_S.Location_link <--> ETH_Channel <--> Location_S.Guard_link;
        Location_S.Registrar_link <--> ETH_Channel <--> Registrar_S.Location_link;
}




