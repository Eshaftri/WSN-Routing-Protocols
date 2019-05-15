
cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum MHeedRoutingPacket_Type {
	MHEED_ROUTING_ADV_PACKET 	= 1;		
	MHEED_ROUTING_JOIN_PACKET 	= 2;		
	MHEED_ROUTING_TDMA_PACKET 	= 3;		
	MHEED_ROUTING_DATA_PACKET 	= 4;
	MHEED_ROUTING_NIDV_PACKET   = 5;
}
struct NDInfo {
	int src;
	double eng;
}



packet MHeedRoutingPacket extends RoutingPacket {	
	int MHeedRoutingPacketKind enum (MHeedRoutingPacket_Type);   
	int cost;
	double eng;
	bool status;
	NDInfo clusterMembers[];		
}
