
cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum SHeedRoutingPacket_Type
{
	SHEED_ROUTING_ADV_PACKET 	= 1;		
	SHEED_ROUTING_JOIN_PACKET 	= 2;		
	SHEED_ROUTING_TDMA_PACKET 	= 3;		
	SHEED_ROUTING_DATA_PACKET 	= 4;
	SHEED_ROUTING_NIDV_PACKET   = 5;
	SHEED_ROUTING_RADV_PACKET   = 6;
};

struct NDInf {
	int src;
	double eng;
};

packet SHeedRoutingPacket extends RoutingPacket
{	
	int SHeedRoutingPacketKind enum (SHeedRoutingPacket_Type);   
	int cost;
	double eng;
	bool status;
	NDInf clusterMembers[];		
};
