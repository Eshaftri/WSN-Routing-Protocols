
cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum RhucRoutingPacket_Type
{
	RHUC_ROUTING_ADV_PACKET 	= 1;		
	RHUC_ROUTING_JOIN_PACKET 	= 2;		
	RHUC_ROUTING_TDMA_PACKET 	= 3;		
	RHUC_ROUTING_DATA_PACKET 	= 4;
	RHUC_ROUTING_COMPETECH_PACKET = 5;
	RHUC_ROUTING_FINALHEAD_PACKET = 6;
	RHUC_ROUTING_QUITELECTION_PACKET = 7;
	RHUC_ROUTING_ADJACENTCH_PACKET = 8;
	RHUC_ROUTING_AGGREGATEDADJACENT_PACKET = 9;
	RHUC_ROUTING_ROTAT_TDMA_PACKET = 10;
};

packet RhucRoutingPacket extends RoutingPacket
{	
	int RhucRoutingPacketKind enum (RhucRoutingPacket_Type);   
	int schedule[];	
	double x;
	double y;
	double RComp;
	double ResidualEnergy;
	double BSDistance;
};
