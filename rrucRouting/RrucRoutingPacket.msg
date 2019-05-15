
cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum RrucRoutingPacket_Type
{
	RRUC_ROUTING_ADV_PACKET 	= 1;		
	RRUC_ROUTING_JOIN_PACKET 	= 2;		
	RRUC_ROUTING_TDMA_PACKET 	= 3;		
	RRUC_ROUTING_DATA_PACKET 	= 4;
	RRUC_ROUTING_COMPETECH_PACKET = 5;
	RRUC_ROUTING_FINALHEAD_PACKET = 6;
	RRUC_ROUTING_QUITELECTION_PACKET = 7;
	RRUC_ROUTING_ADJACENTCH_PACKET = 8;
	RRUC_ROUTING_AGGREGATEDADJACENT_PACKET = 9;
	RRUC_ROUTING_ROTAT_TDMA_PACKET = 10;
};

packet RrucRoutingPacket extends RoutingPacket
{	
	int RrucRoutingPacketKind enum (RrucRoutingPacket_Type);   
	int schedule[];	
	double x;
	double y;
	double RComp;
	double SpentEnergy;	
	double BSDistance;
};
