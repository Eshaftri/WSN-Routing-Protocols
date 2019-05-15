
#ifndef _MHEEDROUTING_H_
#define _MHEEDROUTING_H_

#include <queue>
#include <vector>
#include <omnetpp.h>
#include <algorithm>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "VirtualRouting.h"
#include "VirtualApplication.h"	
#include "MHeedRoutingPacket_m.h"
#include "ApplicationPacket_m.h"
#include "NoMobilityManager.h"


using namespace std;

enum MHeedRoutingTimers {
	START_ROUND = 1,	
	SEND_ADV    = 2,
	JOIN_CH     = 3,		
	MAKE_TDMA   = 4,			
	START_SLOT  = 5,	
	END_SLOT    = 6,
	NEB_DIS     = 7,
	REPEAT      = 8,
	FINALIZE    = 9,
	INITIALIZE  = 10,
	START_ROT   = 11,
	
};



struct CHInfo
{
	int src;
	int cost;	 // number of one hop neighbours
	double rssi;

};

class MHeedRouting : public VirtualRouting {

private:
	
	string applicationID;
	int advPacketSize;
	int tdmaPacketSize;
	int dataPacketSize;
	int joinPacketSize;

	double maxPower;
	double sensibility;
	double aggrConsumption;
	
	double slotLength;
	int clusterLength;
	int neighbourLength;
	double percentage;
	double probability;
	double roundLength;
	double rClustrLen;
	double CHprob;
	double EngAvrg ;
	double CHprevious;
	double timer;
	double randomNumber;
	int roundNumber;
	int cost;
	int count;
	
	bool isCH;
	bool isSink;
	bool endFormClus;
	bool isFinalCH;
	bool status;

	vector<RoutingPacket> bufferAggregate;
	vector<int> powers;
	queue <cPacket *> tempTXBuffer;
	vector <int> neighboursMembers;
	list <CHInfo> Sch;
	list <CHInfo> Sfinal;
	vector<NDInfo> clusterMembers;

protected:

	void startup();
	void fromApplicationLayer(cPacket *, const char *);
	void fromMacLayer(cPacket *, int, double, double);
	void timerFiredCallback(int);
	void processBufferedPacket();
	void neighboursDiscovery();
	
	void sendAggregate();
	void setPowerLevel(double);
	void setStateSleep();
	void setStateRx();
	void levelTxPower(int);	
	void readXMLparams();
	double getCHprob(void);
	double getEngAvrg(void);

};
	bool cmpCost(CHInfo a, CHInfo b);
	bool cmpEng (NDInfo a, NDInfo b);

#endif			
