
#ifndef _RCAROUTING_H_
#define _RCAROUTING_H_

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
#include "RcaRoutingPacket_m.h"
#include "ApplicationPacket_m.h"
#include "NoMobilityManager.h"


using namespace std;

enum RcaRoutingTimers {
	START_ROUND               = 1,	
	SEND_ADV                  = 2,	
	JOIN_CH                   = 3,		
	MAKE_TDMA                 = 4,			
	START_SLOT                = 5,	
	END_SLOT                  = 6,
	START_COMPETITION         = 7,
	FINISH_COMPETITION        = 8,
	ADJACENT_CH_ADVERTISEMENT = 9,
	SEND_QUIT                 = 10,
	START_ROTAT               = 11,
	MAKE_ROTAT_TDMA           = 12,
	SEND_HELLO                = 13,
	SEND_BS                   = 14,
	BS_BROADCAST			  = 15,
	INFO_COLLA                = 16,
};

struct CHInfo
{
	int src;
	double rssi;
};

struct CHCompete{
	int src;					//sorgente (ID)
	double RComp;			//raggio di competenza
	double Wght;		//energia spesa 
	double x;				//coordinata x nodo 
	double y;
};
	
struct CHAdjacent{
	int src;
	double Wght;
	double BSDistance;
	double x;
	double y;
};

class RcaRouting : public VirtualRouting {

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
	double percentage;
	double probability;
	double roundLength;
	double totalResiduaEn;
	double MaxRemingEn;
	double MaxBsDs;
	double tn;
	double Wght;
	int roundNumber;
	int CHcunt;
	int dataSN;
	int i;

	
	bool isCH;
	bool isSink;
	bool isCt;
	bool isBs;
	bool endFormClus;

	vector<RoutingPacket> bufferAggregate;
	vector<int> powers;
	queue <cPacket *> tempTXBuffer;
	vector <int> clusterMembers;
	list <CHInfo> CHcandidates;
	
	//EEUC STUFF
	double iterazioneFinish;
	
	bool found;
	bool newTentativeCH;
	bool isTentativeCH;
	double CompetitionResidualEnergy;
	//double residualEnergy ;
	double initialEnergy ;
	double CHprob ;
	double CHprevious;
	double xlocal;
	double ylocal;
	double RComp;
	double C;
	double DMax;
	double DMin;
	double RZeroComp;
	double BSDistance;
	double timer;
	double K;
	double TD_Max;
	CHAdjacent nextRelay;
	CHAdjacent nextRelayForward;
	
	list <CHCompete> CHCompetitors;			//aggiunto da EEUC
	list <CHAdjacent> CHNeighbors;
	list <CHCompete> Sch;

protected:

	void startup();
	void fromApplicationLayer(cPacket *, const char *);
	void fromMacLayer(cPacket *, int, double, double);
	void timerFiredCallback(int);
	void processBufferedPacket();
	
	void sendAggregate();
	void sendToBS();
	void BsBroadcast();
	void setPowerLevel(double);
	void setStateSleep();
	void setStateRx();
	void levelTxPower(int);	
	void readXMLparams();

	VirtualMobilityManager *nodePosition;		//aggiunto da EEUC
	ResourceManager *energy;				//aggiunto da EEUC

};
bool rcaCmpRssi(CHInfo a, CHInfo b);
bool rcaBSDis(CHAdjacent a, CHAdjacent b);
bool rcaComEn(CHCompete a, CHCompete b);
#endif			
