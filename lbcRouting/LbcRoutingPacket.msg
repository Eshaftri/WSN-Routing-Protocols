
cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum LbcRoutingPacket_Type
{
	LBC_ROUTING_ADV_PACKET 	              = 1;		
	LBC_ROUTING_JOIN_PACKET 	          = 2;		
	LBC_ROUTING_TDMA_PACKET 	          = 3;		
	LBC_ROUTING_DATA_PACKET 	          = 4;
	LBC_ROUTING_COMPETECH_PACKET          = 5;
	LBC_ROUTING_FINALHEAD_PACKET          = 6;
	LBC_ROUTING_QUITELECTION_PACKET       = 7;
	LBC_ROUTING_ADJACENTCH_PACKET         = 8;
	LBC_ROUTING_AGGREGATEDADJACENT_PACKET = 9;
	LBC_ROUTING_ROTAT_TDMA_PACKET         = 10;
	LBC_ROUTING_BS_PACKET                 = 11;
	LBC_ROUTING_BROADCAST_BS_PACKET		  = 12;
	LBC_ROUTING_AGGREGATED_BS_PACKET      = 13;
	
};

packet LbcRoutingPacket extends RoutingPacket
{	
	int LbcRoutingPacketKind enum (LbcRoutingPacket_Type);   
	int schedule[];	
	double x;
	double y;
	double Tn;
	double RComp;
	double ResidualEnergy;
	double BSDistance;
};
