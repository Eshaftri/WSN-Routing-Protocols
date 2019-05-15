
cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum HeedRoutingPacket_Type
{
	HEED_ROUTING_ADV_PACKET 	= 1;		
	HEED_ROUTING_JOIN_PACKET 	= 2;		
	HEED_ROUTING_TDMA_PACKET 	= 3;		
	HEED_ROUTING_DATA_PACKET 	= 4;
	HEED_NEIGHBOURS_DISCOVERY_PACKET     = 5;

};

packet HeedRoutingPacket extends RoutingPacket
{	
	int HeedRoutingPacketKind enum (HeedRoutingPacket_Type);   
	int schedule[];
	int cost;
	bool status;		
};
