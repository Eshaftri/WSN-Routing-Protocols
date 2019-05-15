
cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum EeucRoutingPacket_Type
{
	EEUC_ROUTING_ADV_PACKET 	= 1;		
	EEUC_ROUTING_JOIN_PACKET 	= 2;		
	EEUC_ROUTING_TDMA_PACKET 	= 3;		
	EEUC_ROUTING_DATA_PACKET 	= 4;
	EEUC_ROUTING_COMPETECH_PACKET = 5;
	EEUC_ROUTING_FINALHEAD_PACKET = 6;
	EEUC_ROUTING_QUITELECTION_PACKET = 7;
	EEUC_ROUTING_ADJACENTCH_PACKET = 8;
	EEUC_ROUTING_AGGREGATEDADJACENT_PACKET = 9;
};

packet EeucRoutingPacket extends RoutingPacket
{	
	int EeucRoutingPacketKind enum (EeucRoutingPacket_Type);   
	int schedule[];	
	double x;
	double y;
	double RComp;
	double SpentEnergy;	
	double BSDistance;
};
