//****************************************************************************
//*  Copyright (c) Federal University of Para, brazil - 2011                 *
//*  Developed at the Research Group on Computer Network and Multimedia      *
//*  Communication (GERCOM)     				             *
//*  All rights reserved    				                     *
//*                                                                          *
//*  Permission to use, copy, modify, and distribute this protocol and its   *
//*  documentation for any purpose, without fee, and without written         *
//*  agreement is hereby granted, provided that the above copyright notice,  *
//*  and the author appear in all copies of this protocol.                   *
//*                                                                          *
//*  Module:   HEED Clustering Protocol for Castalia Simulator              *
//*  Version:  0.2                                                           *
//*  Author(s): Adonias Pires <adonias@ufpa.br>                              *
//*             Claudio Silva <claudio.silva@itec.ufpa.br>                   *
//****************************************************************************/

cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum RHeedRoutingPacket_Type
{
	RHEED_ROUTING_ADV_PACKET 	= 1;		
	RHEED_ROUTING_JOIN_PACKET 	= 2;		
	RHEED_ROUTING_TDMA_PACKET 	= 3;		
	RHEED_ROUTING_DATA_PACKET 	= 4;
	RHEED_ROUTING_NIDV_PACKET   = 5;
	RHEED_ROUTING_RADV_PACKET   = 6;
};

packet RHeedRoutingPacket extends RoutingPacket
{	
	int RHeedRoutingPacketKind enum (RHeedRoutingPacket_Type);   
	int schedule[];
	int cost;
	bool status;		
};
