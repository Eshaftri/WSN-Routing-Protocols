
cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum RcaRoutingPacket_Type
{
	RCA_ROUTING_ADV_PACKET 	              = 1;		
	RCA_ROUTING_JOIN_PACKET 	          = 2;		
	RCA_ROUTING_TDMA_PACKET 	          = 3;		
	RCA_ROUTING_DATA_PACKET 	          = 4;
	RCA_ROUTING_COMPETECH_PACKET          = 5;
	RCA_ROUTING_FINALHEAD_PACKET          = 6;
	RCA_ROUTING_QUITELECTION_PACKET       = 7;
	RCA_ROUTING_ADJACENTCH_PACKET         = 8;
	RCA_ROUTING_AGGREGATEDADJACENT_PACKET = 9;
	RCA_ROUTING_ROTAT_TDMA_PACKET         = 10;
	RCA_ROUTING_BS_PACKET                 = 11;
	RCA_ROUTING_BROADCAST_BS_PACKET		  = 12;
	RCA_ROUTING_AGGREGATED_BS_PACKET      = 13;
	RCA_ROUTING_HELLO_PACKET              = 14;
	
};

packet RcaRoutingPacket extends RoutingPacket
{	
	int RcaRoutingPacketKind enum (RcaRoutingPacket_Type);   
	int schedule[];	
	double x;
	double y;
	double Tn;
	double RComp;
	double ResidualEnergy;
	double BSDistance;
	double Wght;
};
