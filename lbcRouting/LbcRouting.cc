
#include "LbcRouting.h"

Define_Module(LbcRouting);

double xBSlbc = 275;  //700
double yBSlbc = 125;   //30

void LbcRouting::startup()
{	
	/*--- The .ned file's parameters ---*/
	percentage = par("percentage");
	roundLength = par("roundLength");
	isSink = par("isSink");
	slotLength = par("slotLength");
	advPacketSize = par("advPacketSize");
	joinPacketSize = par("joinPacketSize");
	tdmaPacketSize = par("tdmaPacketSize");
	dataPacketSize = par("dataPacketSize");
	applicationID = par("applicationID").stringValue(); 

	/*--- Class parameters ---*/
	CHcandidates.clear();
	clusterMembers.clear();
	Sch.clear();
	roundNumber=0;
	j = 0;
	i = 0;
	probability = 0;
	isCH = false;
	endFormClus = false;
	isCt = false;
	isBs = false;

	//EEUC STUFF
	bool found = false;
	newTentativeCH= false;
	xlocal = 0;
	ylocal = 0;
	RComp = 0;
	timer = 0;
	CompetitionResidualEnergy = 0;
	//CompetitionSpentEnergy = 0;
	//residualEnergy = 0;
	cntPktCon = 0;
	initialEnergy = 0;
	totalResiduaEn =0;
	CHprob = 0;
	tn=0;
	CHprevious =0;
	CHCompetitors.clear();
	CHNeighbors.clear();
	BSDistance = 0;
	DMin = par ("DMin");
	DMax = par ("DMax");
	C = par ("C");
	RZeroComp = par ("RZeroComp");
	K = par("K");
	TD_Max = par("TD_Max");
	CHAdjacent nextRelay;
	CHAdjacent nextRelayForward;


	nodePosition = check_and_cast<VirtualMobilityManager*>(getParentModule()->getParentModule()->getSubmodule("MobilityManager")); 
	energy = check_and_cast<ResourceManager*>(getParentModule()->getParentModule()->getSubmodule("ResourceManager"));
	


	xlocal = nodePosition->getLocation().x;								//trovo la mia x
	ylocal = nodePosition->getLocation().y;			
	BSDistance = sqrt(pow((xlocal-xBSlbc),2) + pow((ylocal-yBSlbc),2));	    //trovo la mia distanza dalla BS
	RComp = (1-(C*((DMax-BSDistance)/(DMax-DMin))))*RZeroComp;			//calcolo il mio raggio di competenza
	//RComp = 100;
	//trace() << "Node " << self << " RComp "<<  RComp ;


	readXMLparams();
	//if(!isSink) 

		setTimer(START_ROUND, 0);
	
}

void LbcRouting::fromApplicationLayer(cPacket *pkt, const char *destination){	
	if(!isSink)
	{
		string dst(destination);
		LbcRoutingPacket *netPacket = new LbcRoutingPacket("Lbc routing data packet", NETWORK_LAYER_PACKET);
		netPacket->setLbcRoutingPacketKind(LBC_ROUTING_DATA_PACKET);
		netPacket->setByteLength(dataPacketSize);
		netPacket->setSource(SELF_NETWORK_ADDRESS);
		encapsulatePacket(netPacket, pkt);
		if (!isCH && endFormClus)
		{
			CHInfo info = *CHcandidates.begin();
			stringstream buffer;
			buffer << info.src;
			string dst = buffer.str();
			netPacket->setDestination(dst.c_str());	
			bufferPacket(netPacket);
		}	
		else if (!isCH && !endFormClus) 
		{
			tempTXBuffer.push(netPacket);
		}
		else if (isCH) 
		{
			bufferAggregate.push_back(*netPacket);
		}
	}		
}

void LbcRouting::fromMacLayer(cPacket *pkt, int macAddress, double rssi, double lqi){
	LbcRoutingPacket *netPacket = dynamic_cast <LbcRoutingPacket*>(pkt);

	if (!netPacket)
		return;

	switch (netPacket->getLbcRoutingPacketKind()) {

		case LBC_ROUTING_BS_PACKET:{
			string dst(netPacket->getDestination());
			if (isCH && dst.compare(SELF_NETWORK_ADDRESS) == 0){
				//trace() << "Node " << self << " Aggregate BS Re_Cluster from " << netPacket->getSource()<<"\n";
				bufferAggregate.push_back(*netPacket);	
			}else if (dst.compare(SINK_NETWORK_ADDRESS) == 0 && isSink) {
				trace() << "Node " << self << " Processing BS Re_Cluster from "<<netPacket->getSource()<<"\n";
				toApplicationLayer(decapsulatePacket(netPacket));
				isBs = true;
			}
			break;	
		}

		case LBC_ROUTING_BROADCAST_BS_PACKET:{
			if(!isSink){
				if(!isCt) {
				trace() << "Node " << self << " isCt " ;	
					isCt=true;
					timer = uniform(0,0.5); 
					setTimer(BS_BROADCAST,timer);
				}
			}
	 		break;
		}

		case LBC_ROUTING_DATA_PACKET:{
			string dst(netPacket->getDestination());
			if (isCH && dst.compare(SELF_NETWORK_ADDRESS) == 0){
				//trace() << "Node " << self << " Aggregate Data Frame \n";
				bufferAggregate.push_back(*netPacket);	
			}else if (dst.compare(SINK_NETWORK_ADDRESS) == 0 && isSink) {
				trace() << "Node " << self << " Processing Data Packet from "<<netPacket->getSource()<<"\n";
				toApplicationLayer(decapsulatePacket(netPacket));
			}
			break;	
		}

		case LBC_ROUTING_ADV_PACKET:{
			if(!isCH && !isSink){
				CHInfo rec;
				rec.src = atoi(netPacket->getSource());
				rec.rssi = rssi;
				CHcandidates.push_front(rec);
			}
			break;
		}
		case LBC_ROUTING_JOIN_PACKET:{
			string dst(netPacket->getDestination());
			if(isCH && dst.compare(SELF_NETWORK_ADDRESS) == 0) {
				//trace() << "Node " << self << " Received a Join Request. Adding to clusterMembers\n";
				clusterMembers.push_back(atoi(netPacket->getSource()));
				totalResiduaEn=totalResiduaEn+netPacket->getResidualEnergy();									
			}
	 		break;
		}
		case LBC_ROUTING_TDMA_PACKET:{
			if(!isCH && !isSink)
			{
				clusterLength = netPacket->getScheduleArraySize();
				for(int i=0; i<netPacket->getScheduleArraySize(); i++) {
					if (netPacket->getSchedule(i)==atoi(SELF_NETWORK_ADDRESS)) {	
						setStateSleep();
						setTimer(START_SLOT, i*slotLength);
						tn=netPacket->getTn();
						//trace() << "Node " << self << " Received TDMA pkt, I am: "<< i << "th \n";
						trace() << "Node " << self << " Received tn: "<<  tn << " from CH: "<< netPacket->getSource() << " Cluster size " << netPacket->getScheduleArraySize();
						for( int i=0; i < netPacket->getScheduleArraySize(); i++) {
							//	trace() << "Node " << netPacket->getClusterMembers(i).src << " I am:The  "<< i << " from " << netPacket->getSource() <<" with Eng " <<netPacket->getClusterMembers(i).eng;
					         clusterMembers.push_back(netPacket->getSchedule(i));
					     }
					    // trace() << "Node " << self << " clusterLength "<<  clusterMembers.size() ;
					    
						break;
					}			
				}
			}
			break;
		}

		case LBC_ROUTING_ROTAT_TDMA_PACKET:{
			if(!isCH && !isSink)
			{
				clusterLength = netPacket->getScheduleArraySize();
				for(int i=0; i<netPacket->getScheduleArraySize(); i++) {
					if (netPacket->getSchedule(i)==atoi(SELF_NETWORK_ADDRESS)) {	
						setStateSleep();
						setTimer(START_SLOT, i*slotLength);
						//trace() << "Node " << self << " Received TDMA pkt, I am: "<< i << "th \n";
						break;
					}			
				}
			}
			break;
		}

		case LBC_ROUTING_COMPETECH_PACKET:{
			if(!isSink){
				if (newTentativeCH){				
					CHCompete comp;
					comp.src = atoi(netPacket->getSource());					//estraggo il mittente
					comp.RComp = netPacket->getRComp();						//estraggo il suo raggio di competenza
					comp.ResidualEnergy = netPacket->getResidualEnergy();			//estraggo la sua energia spesa 
					comp.x = netPacket->getX();								//estraggo la sua x
					comp.y = netPacket->getY();								//estraggo la sua y

					double distance = sqrt(pow((xlocal-comp.x),2) + pow((ylocal-comp.y),2));

					if ((distance < RComp) || (distance < comp.RComp)){																					//se la distanza ? minore del mio o del suo raggio di competenza
						CHCompetitors.push_front(comp);							//lo includo nella lista dei competitors

					}

				}else{
					CHCompete comp;
					comp.src = atoi(netPacket->getSource());					//estraggo il mittente
					comp.RComp = netPacket->getRComp();							//estraggo il suo raggio di competenza
					comp.ResidualEnergy = netPacket->getResidualEnergy();
					Sch.push_front(comp);										//lo includo nella lista dei competitors
				}
			}
			break;
		}
		/*
		case LBC_ROUTING_FINALHEAD_PACKET:{
			//if(newTentativeCH){// && (CHCompetitors.size() != 0)){				
				int packetSource = atoi(netPacket->getSource());
							
				list <CHCompete>::iterator p;
				p = CHCompetitors.begin();
				
				while((found == false) && (p !=CHCompetitors.end())){
					if (packetSource == (*p).src){
						found = true;
						double timerQuit = uniform(0,1);
						setTimer(SEND_QUIT, timerQuit);
						newTentativeCH = false;
					}
					p++;
				}
			//}			
			break;
		}
		*/
		case LBC_ROUTING_QUITELECTION_PACKET:{
				
				int packetSource = atoi(netPacket->getSource());

				bool foundToErase = false;

				list <CHCompete>::iterator p;
				p = CHCompetitors.begin();
				while ((foundToErase == false) && (p != CHCompetitors.end())){
					if (packetSource == (*p).src){
						foundToErase = true;
						CHCompetitors.erase(p);
					}	
					p++;
				}
			//}
			break;
		}
		case LBC_ROUTING_ADJACENTCH_PACKET:{
			if(isCH){
				CHAdjacent near;								//creo un nuovo elemento near
				near.src = atoi(netPacket->getSource());			//setto il mittente
				near.ResidualEnergy = netPacket->getResidualEnergy();	//setto la sua energia rimanente
				near.BSDistance = netPacket->getBSDistance();		//setto la sua distanza dalla BS
				near.x = netPacket->getX();						//setto la sua x
				near.y = netPacket->getY();						//setto la sua y

				double distance = sqrt(pow((xlocal-near.x),2) + pow((ylocal-near.y),2));
				
				if ((distance <= K*RComp)&&(near.BSDistance < BSDistance)){
					CHNeighbors.push_front(near);				//inserisco il CH nella mia lista dei CH vicini
				}				
			}
			break;
		}

			case LBC_ROUTING_AGGREGATED_BS_PACKET:{
			string dst(netPacket->getDestination());
			if ((isCH) && (dst.compare(SELF_NETWORK_ADDRESS) == 0)){

				if (BSDistance<TD_Max || CHNeighbors.size()==0){					
					double bitsLength = bufferAggregate.size() * dataPacketSize * 1000;
					double energyBit = (aggrConsumption / pow(10,9)) * bitsLength;
					powerDrawn(energyBit);
					LbcRoutingPacket *aggrPacket = new LbcRoutingPacket("ClusterHead Aggredated Packet", NETWORK_LAYER_PACKET);
					aggrPacket->setByteLength(dataPacketSize+4);
					aggrPacket->setLbcRoutingPacketKind(LBC_ROUTING_BS_PACKET);
					aggrPacket->setSource(SELF_NETWORK_ADDRESS);
					aggrPacket->setDestination(SINK_NETWORK_ADDRESS);

					ApplicationPacket *newPacket = new ApplicationPacket("App generic packet", APPLICATION_PACKET);
					newPacket->setData(0);
					newPacket->getAppNetInfoExchange().destination = string("0");
					newPacket->getAppNetInfoExchange().source = selfAddress;
					newPacket->getAppNetInfoExchange().timestamp = simTime();
					newPacket->setApplicationID(applicationID.c_str());
					encapsulatePacket(aggrPacket, newPacket);

					bufferPacket(aggrPacket);
				}else{

					if (CHNeighbors.size()>1){


						CHNeighbors.sort(cmoBSDis);	

						CHAdjacent neighbor_1 = CHNeighbors.back();
						CHNeighbors.pop_back();
						CHAdjacent neighbor_2 = CHNeighbors.back();
						CHNeighbors.push_back(neighbor_1);

						if (neighbor_1.ResidualEnergy >= neighbor_2.ResidualEnergy){
							nextRelayForward = neighbor_1;
						}else{
							nextRelayForward = neighbor_2;
						}	

						//nextRelayForward = CHNeighbors.back();

						
					}else{
						nextRelayForward = CHNeighbors.back();
					}

					stringstream buffer;
					buffer << nextRelayForward.src;
					string dst = buffer.str();

					LbcRoutingPacket *aggrPacket = new LbcRoutingPacket("ClusterHead Aggredated Packet", NETWORK_LAYER_PACKET);
					aggrPacket->setByteLength(dataPacketSize+4);
					aggrPacket->setLbcRoutingPacketKind(LBC_ROUTING_AGGREGATED_BS_PACKET);
					aggrPacket->setSource(SELF_NETWORK_ADDRESS);
					aggrPacket->setDestination(dst.c_str());

					toMacLayer(aggrPacket, BROADCAST_MAC_ADDRESS);
					cntPktCon++;
				}				
			}
			break;
		}
		case LBC_ROUTING_AGGREGATEDADJACENT_PACKET:{
			string dst(netPacket->getDestination());
			if ((isCH) && (dst.compare(SELF_NETWORK_ADDRESS) == 0)){
				if (BSDistance<TD_Max || CHNeighbors.size()==0){					
					double bitsLength = bufferAggregate.size() * dataPacketSize * 1000;
					double energyBit = (aggrConsumption / pow(10,9)) * bitsLength;
					powerDrawn(energyBit);
					LbcRoutingPacket *aggrPacket = new LbcRoutingPacket("ClusterHead Aggredated Packet", NETWORK_LAYER_PACKET);
					aggrPacket->setByteLength(dataPacketSize+4);
					aggrPacket->setLbcRoutingPacketKind(LBC_ROUTING_DATA_PACKET);
					aggrPacket->setSource(SELF_NETWORK_ADDRESS);
					aggrPacket->setDestination(SINK_NETWORK_ADDRESS);

					ApplicationPacket *newPacket = new ApplicationPacket("App generic packet", APPLICATION_PACKET);
					newPacket->setData(0);
					newPacket->getAppNetInfoExchange().destination = string("0");
					newPacket->getAppNetInfoExchange().source = selfAddress;
					newPacket->getAppNetInfoExchange().timestamp = simTime();
					newPacket->setApplicationID(applicationID.c_str());
					encapsulatePacket(aggrPacket, newPacket);

					bufferPacket(aggrPacket);
				}else{
					if (CHNeighbors.size()>1){


						CHNeighbors.sort(cmoBSDis);	

						CHAdjacent neighbor_1 = CHNeighbors.back();
						CHNeighbors.pop_back();
						CHAdjacent neighbor_2 = CHNeighbors.back();
						CHNeighbors.push_back(neighbor_1);

						if (neighbor_1.ResidualEnergy >= neighbor_2.ResidualEnergy){
							nextRelayForward = neighbor_1;
						}else{
							nextRelayForward = neighbor_2;
						}	

						//nextRelayForward = CHNeighbors.back();

						
					}else{
						nextRelayForward = CHNeighbors.back();
					}

					stringstream buffer;
					buffer << nextRelayForward.src;
					string dst = buffer.str();

					LbcRoutingPacket *aggrPacket = new LbcRoutingPacket("ClusterHead Aggredated Packet", NETWORK_LAYER_PACKET);
					aggrPacket->setByteLength(dataPacketSize+4);
					aggrPacket->setLbcRoutingPacketKind(LBC_ROUTING_AGGREGATEDADJACENT_PACKET);
					aggrPacket->setSource(SELF_NETWORK_ADDRESS);
					aggrPacket->setDestination(dst.c_str());

					toMacLayer(aggrPacket, BROADCAST_MAC_ADDRESS);
					cntPktCon++;
				}				
			}
			break;
		}
	}
}

void LbcRouting::timerFiredCallback(int index){
	switch (index) {
		case START_ROUND:{
			setTimer(START_ROTAT, roundLength);
			isBs = false;
			isCt = false;
			if(!isSink){
				setStateRx();
				setPowerLevel(maxPower);
				endFormClus = false;
				CHcandidates.clear();
				clusterMembers.clear();
				CHCompetitors.clear();
				Sch.clear();
				if (getTimer(START_SLOT) != 0) { 
					cancelTimer(START_SLOT);
				}
				found = false;
				if (isCH){
					isCH = false;
					CHNeighbors.clear();
					nextRelay.src = 0;
					//nextRelay.SpentEnergy = 0;
					nextRelay.BSDistance = 0;
					nextRelay.x = 0;
					nextRelay.y = 0;
					nextRelayForward.src = 0;
					//nextRelayForward.SpentEnergy = 0;
					nextRelayForward.BSDistance = 0;
					nextRelayForward.x = 0;
					nextRelayForward.y = 0;
				}
				timer = uniform(0,1); 											//to allow initialization of all nodes	
				newTentativeCH = false;	
				setTimer(INITIALIZE,timer);
				//setTimer(START_COMPETITION,timer);
				setTimer(FINISH_COMPETITION, timer+2.0);
				setTimer(SEND_ADV, timer+3.0);
				setTimer(ADJACENT_CH_ADVERTISEMENT, 4.5+timer);
				setTimer(MAKE_TDMA, 6.0+timer);
				
				roundNumber++;
				//setTimer(START_ROTAT, roundLength);
				//setTimer(START_ROUND, roundLength);
			}
			break;
		}

		case INITIALIZE:{
			if (roundNumber <= 1){
			CompetitionResidualEnergy = energy->getRemainingEnergy()- uniform(0,5);
  			initialEnergy = energy->par("initialEnergy");
  			probability = percentage/(1-percentage*(roundNumber % (int) (1/percentage)));
  			CHprob = probability * (CompetitionResidualEnergy/initialEnergy);
			//CompetitionSpentEnergy = energy->getSpentEnergy() - uniform(0.0001,0.0002); //this allow to have different levels of remaining energy among all nodes at the first round
			}else{
			CompetitionResidualEnergy = energy->getRemainingEnergy();
  			initialEnergy = energy->par("initialEnergy");
  			probability = percentage/(1-percentage*(roundNumber % (int) (1/percentage)));
  			CHprob = probability * (CompetitionResidualEnergy/initialEnergy);
			//CompetitionSpentEnergy = energy->getSpentEnergy();
			}
			//CHprob = getCHprob();
			//double ttimer = ((1/CHprob)/60);
			//trace() << "Node " << self << " ttimer " << ttimer;
			CHprevious =0;
			trace() << "Node " << self << " probability " << probability;
			trace() << "Node " << self << " CHprob " << CHprob;
			//trace() << "Node " << self << " randomNumber " << randomNumber;
			trace() << "Node " << self << " CompetitionResidualEnergy " << CompetitionResidualEnergy;
			do{
				double randomNumber = uniform(0,1);
  				if(Sch.size()!=0){
  					trace() << "Node " << self << " ArraySaiz " << Sch.size();	
  					Sch.sort(lbcComEn);
  					CHCompete info = *Sch.begin();
					stringstream buffer;
					buffer << info.src;
					string dst = buffer.str();
					trace() << "Node " << info.src << " EnRemaing " << info.ResidualEnergy;
					trace() << "Node " << self << " EnRemaing " << CompetitionResidualEnergy;
  						if(CompetitionResidualEnergy > info.ResidualEnergy){
  							setTimer(START_COMPETITION,0); //cluster_head_msg(NodeID,tentative_CH,cost)
  							newTentativeCH = true;	
  							trace() << "Node " << self << " send com in randomNumber <= CHprob ";
  							trace() << "Node " << self << " CHprob " << CHprob;
		    				trace() << "Node " << self << " randomNumber " << randomNumber;
		    			 	break;
			   			}else{
			   				 	setTimer(START_COMPETITION,0);
			   			}
  				}else{
					if(randomNumber < CHprob)
  					setTimer(START_COMPETITION,0); //cluster_head_msg(NodeID,tentative_CH,cost)
  					//newTentativeCH = true;	
  				}
				CHprevious = round(CHprob);
				CHprob = CHprob * 2;
				trace() << "CHprevious " << CHprevious;
			}while(CHprevious < 1);
		/////////////////////////////////////////////////
			if((!newTentativeCH) && (Sch.size() == 0)){
  				newTentativeCH = true;	
  				setTimer(START_COMPETITION,0); //cluster_head_msg(NodeID,final_CH,cost)
  				trace() << "Node " << self << " SchArray " << Sch.size();	
				trace() << "Node " << self << " send com in !newTentativeCH ";
			}
			break;
		}

		case SEND_ADV:{	
		
			if (!isCH){
				setTimer(JOIN_CH, timer+0.5);
			}else{
		
				LbcRoutingPacket *crtlPkt = new LbcRoutingPacket("ClusterHead Announcement Packet", NETWORK_LAYER_PACKET);
				crtlPkt->setByteLength(advPacketSize);
				crtlPkt->setLbcRoutingPacketKind(LBC_ROUTING_ADV_PACKET);
				crtlPkt->setSource(SELF_NETWORK_ADDRESS);
				crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
				toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
				cntPktCon++;
				//trace() << "Node " << self << " Sent Beacon";
				clusterMembers.push_back(atoi(SELF_NETWORK_ADDRESS));

			}
			break;
		}
		case JOIN_CH:{

			double ResidualEnergy = energy->getRemainingEnergy();
			if(CHcandidates.size()!=0){	

				CHcandidates.sort(lbcCmpRssi);
				LbcRoutingPacket *crtlPkt = new LbcRoutingPacket("ClusterMember Join Packet", NETWORK_LAYER_PACKET);
				crtlPkt->setLbcRoutingPacketKind(LBC_ROUTING_JOIN_PACKET);
				crtlPkt->setByteLength(joinPacketSize);	
				crtlPkt->setSource(SELF_NETWORK_ADDRESS);
				crtlPkt->setResidualEnergy(ResidualEnergy);									//setto l'energia spesa
				CHInfo info = *CHcandidates.begin();
				stringstream buffer;
				buffer << info.src;
				string dst = buffer.str();
				crtlPkt->setDestination(dst.c_str());			
				toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
				cntPktCon++;
				endFormClus = true;
				trace() << "Node " << self << " Sent Join Request to CH " << dst ;

			}
			break;
		}
		case MAKE_TDMA:{
			if (isCH){
			clusterMembers.push_back(atoi(SELF_NETWORK_ADDRESS));
			tn=totalResiduaEn/clusterMembers.size();
			trace() << "Node " << self << " totalResiduaEn "<<  totalResiduaEn ;
			trace() << "Node " << self << " tn "<<  tn ;
				if (clusterMembers.size()!=0){
					 trace() << "Node " << self << " CH NB "<<  clusterMembers.size() ;
					LbcRoutingPacket *crtlPkt = new LbcRoutingPacket("ClusterHead TDMA Packet", NETWORK_LAYER_PACKET);
					crtlPkt->setByteLength(tdmaPacketSize);
					crtlPkt->setLbcRoutingPacketKind(LBC_ROUTING_TDMA_PACKET);
					crtlPkt->setSource(SELF_NETWORK_ADDRESS);
					crtlPkt->setTn(tn);
					crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
					clusterLength = clusterMembers.size();	
					crtlPkt->setScheduleArraySize(clusterMembers.size());	
					for(int i=0; i<clusterLength; i++) crtlPkt->setSchedule(i,clusterMembers[i]);
					toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
				cntPktCon++;
					//trace() << "Node " << self << " Sent TDMA pkt";
					setTimer(START_SLOT, clusterLength*slotLength);
				}
				else setTimer(START_SLOT, slotLength);
			}
			break;
		}

case MAKE_ROTAT_TDMA:{
			if (isCH){
				
				if (clusterMembers.size()!=0){
					 trace() << "Node " << self << " CH NB "<<  clusterMembers.size() ;
					LbcRoutingPacket *crtlPkt = new LbcRoutingPacket("ClusterHead TDMA Packet", NETWORK_LAYER_PACKET);
					crtlPkt->setByteLength(tdmaPacketSize);
					crtlPkt->setLbcRoutingPacketKind(LBC_ROUTING_ROTAT_TDMA_PACKET);
					crtlPkt->setSource(SELF_NETWORK_ADDRESS);
					crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
					clusterLength = clusterMembers.size();	
					crtlPkt->setScheduleArraySize(clusterMembers.size());	
					for(int i=0; i<clusterLength; i++) crtlPkt->setSchedule(i,clusterMembers[i]);
					toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
				cntPktCon++;
					//trace() << "Node " << self << " Sent TDMA pkt";
					setTimer(START_SLOT, clusterLength*slotLength);
				}
				else setTimer(START_SLOT, slotLength);
			}
			break;
		}

		case START_ROTAT:{
			trace() << "Node " << self << " cntPktCon " << cntPktCon;
			setTimer(START_ROTAT, roundLength);
			if(!isCt){
				if(isBs){
					setTimer(BS_BROADCAST,0.25);
					trace() << "Node " << self << " BS = true ";	
					isCt=true;
				}
				if(!isSink){
						setStateRx();
						setPowerLevel(maxPower);
						CHcandidates.clear();
						if (getTimer(START_SLOT) != 0) { 
							cancelTimer(START_SLOT);
						}
						endFormClus = false;
					//if (isCH){
						isCH = false;
						CHNeighbors.clear();
						nextRelay.src = 0;
						//nextRelay.SpentEnergy = 0;
						nextRelay.BSDistance = 0;
						nextRelay.x = 0;
						nextRelay.y = 0;
						nextRelayForward.src = 0;
						//nextRelayForward.SpentEnergy = 0;
						nextRelayForward.BSDistance = 0;
						nextRelayForward.x = 0;
						nextRelayForward.y = 0;
				//	}			
					double ResidualEnergy = energy->getRemainingEnergy();

					if (clusterMembers.size()!=0) {
						while(j< clusterMembers.size()){
			    			if (clusterMembers[i]==atoi(SELF_NETWORK_ADDRESS)){
								isCH = true;
								setTimer(ADJACENT_CH_ADVERTISEMENT, 1.0+timer);
								setTimer(MAKE_ROTAT_TDMA, timer+3.0);
								trace() << "Node " << self << " CH after Rotate wit count "<< i << " and "<< clusterMembers[i];
								if(tn >= ResidualEnergy){
									trace() << "Node " << self << " 1tn "<< tn << " RE-ResidualEnergy  "<< ResidualEnergy;
									setTimer(SEND_BS, timer+2.0);
								}
							}else{
								CHInfo rec;
								rec.src = clusterMembers[i];
								CHcandidates.push_front(rec);
								endFormClus = true;
								trace() << "Node " << self << " cluster Members wit CH "<< clusterMembers[i];
							}	
						break;
						}
							i=(i+1)%clusterMembers.size();
							trace() << "mommmooo " << i  ;
					}
				}
			}else{
				cancelTimer(START_ROTAT);
				setTimer(START_ROUND, 0);	
				trace() << "NEW  START_ROUND"   ;

			}	
			break;
		}

		case START_SLOT:{
			if(isCH && clusterMembers.size()==0) setTimer(START_SLOT, slotLength);	
			else setTimer(START_SLOT, clusterLength*slotLength);
			if (isCH) {
				sendAggregate(); 
				processBufferedPacket();
				//trace() << "Node " << self << " Sent Pkt Aggr"  << "\n";
			}
			
			if (!isCH){
				CHInfo info = *CHcandidates.begin();
				int power = maxPower - ((info.rssi)-(sensibility));
				levelTxPower(power);
				//trace() << "Node " << self << " Sent Data Packet"  << "\n";
				processBufferedPacket();
				setTimer(END_SLOT, slotLength);
			}
			break;
		}

		case END_SLOT:{
			//trace() << "Node " << self << " Sleept"  << "\n";
			if (!isSink && !isCH) setStateSleep();
			break;
		}

		case START_COMPETITION: {			
			
			LbcRoutingPacket *crtlPkt = new LbcRoutingPacket("Tentative Cluster Initializing Message", NETWORK_LAYER_PACKET);
			crtlPkt->setByteLength(advPacketSize);								//viene settata la dimensione del pacchetto, gi? specificata 
			crtlPkt->setLbcRoutingPacketKind(LBC_ROUTING_COMPETECH_PACKET);	//setto il tipo di EEUC packet; in LbcRoutingpacket.h
			crtlPkt->setSource(SELF_NETWORK_ADDRESS);							//setto il nodo sorgente; routingpacket.h
			crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);					//setto la destinazione; routingpacket.h
			crtlPkt->setRComp(RComp);											//setto il raggio di competenza
			crtlPkt->setResidualEnergy(CompetitionResidualEnergy);				//setto l'energia spesa
			crtlPkt->setX(xlocal);												//setto la mia x
			crtlPkt->setY(ylocal);												//setto la mia y
			toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);							//Sends a packet to MAC layer, along with the destination MAC 
			cntPktCon++;
			break;
		}	
/*
	    case FINISH_COMPETITION:{
			if (newTentativeCH){
				
				bool lessSpentEnergy = true;
				list <CHCompete>::iterator p;										//creo un iteratore per scorrere la lista dei tentativeCH nella lista
				p = CHCompetitors.begin();	
			
				while ((lessSpentEnergy == true) && (p !=CHCompetitors.end())){		//finch? non il flag rimane "true" o non arrivo alla fine della lista scorro la lista stessa
					if (CompetitionResidualEnergy >=  (*p).ResidualEnergy){				//se trovo un tentativeCh che ha pi? energia residua di me allora
						lessSpentEnergy = false;									//setto il flag a falso
					}
					p++;
				}
			
				if(lessSpentEnergy){
				trace() << "Node " << self << " is Cluster Head.";
					isCH = true;
					newTentativeCH = false;
				
				}
				break;
			}
		}
*/
		case SEND_BS:{	
		
			if (isCH){
				LbcRoutingPacket *crtlPkt = new LbcRoutingPacket("BS Re-Claster Packet", NETWORK_LAYER_PACKET);
				crtlPkt->setByteLength(advPacketSize);
				crtlPkt->setLbcRoutingPacketKind(LBC_ROUTING_BS_PACKET);
				crtlPkt->setSource(SELF_NETWORK_ADDRESS);
				bufferAggregate.push_back(*crtlPkt);
				sendToBS();

			}
			break;
		}

		case FINISH_COMPETITION:{
			if(newTentativeCH){
			trace() << "Node " << self << " ArraySaizCH " << CHCompetitors.size();	
			CHCompetitors.sort(lbcComEn);
  					CHCompete info = *CHCompetitors.begin();
					stringstream buffer;
					buffer << info.src;
					string dst = buffer.str();
					trace() << "Node " << info.src << " ResidualEnergy " << info.ResidualEnergy;
  					if(CompetitionResidualEnergy >= info.ResidualEnergy){
					trace() << "Node " << self << " ResidualEnergy " << CompetitionResidualEnergy << " is Cluster Head.";
					isCH = true;			
				}
			//	setTimer(FINISH_COMPETITION, 2);
			}
			break;
		}	

		case BS_BROADCAST:{
				LbcRoutingPacket *crtlPkt = new LbcRoutingPacket("BS BROADCAST Packet", NETWORK_LAYER_PACKET);
				crtlPkt->setByteLength(advPacketSize);
				crtlPkt->setLbcRoutingPacketKind(LBC_ROUTING_BROADCAST_BS_PACKET);
				crtlPkt->setSource(SELF_NETWORK_ADDRESS);
				crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
				toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
				cntPktCon++;
			
			break;
		}

		case ADJACENT_CH_ADVERTISEMENT:{
			if (isCH){
				
				double ResidualEnergy = energy->getRemainingEnergy();
				
				LbcRoutingPacket *crtlPkt = new LbcRoutingPacket("Adjacent Cluster Head Advertisement", NETWORK_LAYER_PACKET);

				crtlPkt->setByteLength(advPacketSize);									//viene settata la dimensione del pacchetto, gi? specificata nel .ned file
				crtlPkt->setLbcRoutingPacketKind(LBC_ROUTING_ADJACENTCH_PACKET);		//setto il tipo di EEUC packet; in LbcRoutingpacket.h
				crtlPkt->setSource(SELF_NETWORK_ADDRESS);							//setto il nodo sorgente; routingpacket.h
				crtlPkt->setResidualEnergy(ResidualEnergy);									//setto l'energia spesa
				crtlPkt->setBSDistance(BSDistance);									//setto la mia distanza dalla BS
				crtlPkt->setX(xlocal);												//setto la mia x
				crtlPkt->setY(ylocal);												//setto la mia y
				crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);					//setto la destinazione; routingpacket.h

				toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
				cntPktCon++;
				
				//FINO A QUI TUTTO CORRETTO 28-11-13 ORE 16.30
			}			
			break;
		}
	}
}

void LbcRouting::sendAggregate(){
	if(bufferAggregate.size()!=0){
		

		if ((BSDistance < TD_Max) ||  (CHNeighbors.size() == 0)){	


			double bitsLength = bufferAggregate.size() * dataPacketSize * 1000;
			double energyBit = (aggrConsumption / pow(10,9)) * bitsLength;
			powerDrawn(energyBit);
			LbcRoutingPacket *aggrPacket = new LbcRoutingPacket("ClusterHead Aggredated Packet", NETWORK_LAYER_PACKET);
			aggrPacket->setByteLength(dataPacketSize+4);
			aggrPacket->setLbcRoutingPacketKind(LBC_ROUTING_DATA_PACKET);
			aggrPacket->setSource(SELF_NETWORK_ADDRESS);
			aggrPacket->setDestination(SINK_NETWORK_ADDRESS);

			ApplicationPacket *newPacket = new ApplicationPacket("App generic packet", APPLICATION_PACKET);
			newPacket->setData(0);
			newPacket->getAppNetInfoExchange().destination = string("0");
			newPacket->getAppNetInfoExchange().source = selfAddress;
			newPacket->getAppNetInfoExchange().timestamp = simTime();
			newPacket->setApplicationID(applicationID.c_str());
			encapsulatePacket(aggrPacket, newPacket);

			bufferPacket(aggrPacket);
			bufferAggregate.clear();
		}else{
			if (CHNeighbors.size()>1){

				CHNeighbors.sort(cmoBSDis);	

				CHAdjacent neighbor_1 = CHNeighbors.back();
				CHNeighbors.pop_back();
				CHAdjacent neighbor_2 = CHNeighbors.back();
				CHNeighbors.push_back(neighbor_1);

				if (neighbor_1.ResidualEnergy >= neighbor_2.ResidualEnergy){
					nextRelay = neighbor_1;
				}else{
					nextRelay = neighbor_2;
				}

				//nextRelay = CHNeighbors.back();
				
			}else{
				nextRelay = CHNeighbors.back();
			}

			stringstream buffer;
			buffer << nextRelay.src;
			string dst = buffer.str();

			LbcRoutingPacket *aggrPacket = new LbcRoutingPacket("ClusterHead Aggredated Packet", NETWORK_LAYER_PACKET);
			aggrPacket->setByteLength(dataPacketSize+4);
			aggrPacket->setLbcRoutingPacketKind(LBC_ROUTING_AGGREGATEDADJACENT_PACKET);
			aggrPacket->setSource(SELF_NETWORK_ADDRESS);
			aggrPacket->setDestination(dst.c_str());

			toMacLayer(aggrPacket, BROADCAST_MAC_ADDRESS);
			cntPktCon++;
			bufferAggregate.clear();			
		}
	}
}


void LbcRouting::sendToBS(){
	if(bufferAggregate.size()!=0){
		

		if ((BSDistance < TD_Max) ||  (CHNeighbors.size() == 0)){	

			double bitsLength = bufferAggregate.size() * dataPacketSize * 1000;
			double energyBit = (aggrConsumption / pow(10,9)) * bitsLength;
			powerDrawn(energyBit);
			LbcRoutingPacket *aggrPacket = new LbcRoutingPacket("ClusterHead Aggredated Packet", NETWORK_LAYER_PACKET);
			aggrPacket->setByteLength(dataPacketSize+4);
			aggrPacket->setLbcRoutingPacketKind(LBC_ROUTING_BS_PACKET);
			aggrPacket->setSource(SELF_NETWORK_ADDRESS);
			aggrPacket->setDestination(SINK_NETWORK_ADDRESS);

			ApplicationPacket *newPacket = new ApplicationPacket("App generic packet", APPLICATION_PACKET);
			newPacket->setData(0);
			newPacket->getAppNetInfoExchange().destination = string("0");
			newPacket->getAppNetInfoExchange().source = selfAddress;
			newPacket->getAppNetInfoExchange().timestamp = simTime();
			newPacket->setApplicationID(applicationID.c_str());
			encapsulatePacket(aggrPacket, newPacket);

			bufferPacket(aggrPacket);
			bufferAggregate.clear();
		}else{
			if (CHNeighbors.size()>1){

				CHNeighbors.sort(cmoBSDis);	

				CHAdjacent neighbor_1 = CHNeighbors.back();
				CHNeighbors.pop_back();
				CHAdjacent neighbor_2 = CHNeighbors.back();
				CHNeighbors.push_back(neighbor_1);

				if (neighbor_1.ResidualEnergy >= neighbor_2.ResidualEnergy){
					nextRelay = neighbor_1;
				}else{
					nextRelay = neighbor_2;
				}

				//nextRelay = CHNeighbors.back();
				
			}else{
				nextRelay = CHNeighbors.back();
			}

			stringstream buffer;
			buffer << nextRelay.src;
			string dst = buffer.str();

			LbcRoutingPacket *aggrPacket = new LbcRoutingPacket("ClusterHead Aggredated Packet", NETWORK_LAYER_PACKET);
			aggrPacket->setByteLength(dataPacketSize+4);
			aggrPacket->setLbcRoutingPacketKind(LBC_ROUTING_AGGREGATED_BS_PACKET);
			aggrPacket->setSource(SELF_NETWORK_ADDRESS);
			aggrPacket->setDestination(dst.c_str());

			toMacLayer(aggrPacket, BROADCAST_MAC_ADDRESS);
			cntPktCon++;
			bufferAggregate.clear();			
		}
	}
}

void LbcRouting::processBufferedPacket(){
	while (!tempTXBuffer.empty())
	{
		cPacket *pkt = tempTXBuffer.front();	
		LbcRoutingPacket *netPacket = dynamic_cast <LbcRoutingPacket*>(pkt);
		CHInfo info = *CHcandidates.begin();
		stringstream buffer;
		buffer << info.src;
		string dst = buffer.str();
		netPacket->setDestination(dst.c_str());
		bufferPacket(netPacket); 
		tempTXBuffer.pop();
	}

	while (!TXBuffer.empty()) {
		toMacLayer(TXBuffer.front(), BROADCAST_MAC_ADDRESS);
		TXBuffer.pop();
		cntPktCon++;
	}	
}

void LbcRouting::setStateRx(){
	send(createRadioCommand(SET_STATE, RX), "toMacModule");	
}

void LbcRouting::setPowerLevel(double powerLevel){
	send(createRadioCommand(SET_TX_OUTPUT, powerLevel), "toMacModule");
}

void LbcRouting::setStateSleep(){
	send(createRadioCommand(SET_STATE, SLEEP), "toMacModule");
}

void LbcRouting::BsBroadcast(){
		trace() << "Node " << self << " moh " ;	
				LbcRoutingPacket *BsCrtlPkt = new LbcRoutingPacket("BS BROADCAST Packet", NETWORK_LAYER_PACKET);
				BsCrtlPkt->setByteLength(advPacketSize);
				BsCrtlPkt->setLbcRoutingPacketKind(LBC_ROUTING_BROADCAST_BS_PACKET);
				BsCrtlPkt->setSource(SELF_NETWORK_ADDRESS);
				BsCrtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
				toMacLayer(BsCrtlPkt, BROADCAST_MAC_ADDRESS);
				cntPktCon++;
			
}

void LbcRouting::levelTxPower(int linkBudget){
	vector<int>::iterator constIterator;
	for (constIterator = powers.begin();
		constIterator != powers.end();
	        constIterator++ ) {
		if(*constIterator > (linkBudget))
		{
			setPowerLevel(*constIterator);
			break;
		}
	}
}

void LbcRouting::readXMLparams(){
	cXMLElement *rootelement = par("powersConfig").xmlValue();
	if (!rootelement) endSimulation();
	cXMLElement* data = rootelement->getFirstChildWithTag("maxPower");
	maxPower = atoi(data->getNodeValue());
	data = rootelement->getFirstChildWithTag("sensibility");
	sensibility = atoi(data->getNodeValue());
	data = rootelement->getFirstChildWithTag("aggrConsumption");
	aggrConsumption = atoi(data->getNodeValue());
	cXMLElementList sources = rootelement->getChildrenByTagName("power");
	for (int s = 0; s < sources.size(); s++)
		powers.push_back(atoi(sources[s]->getNodeValue()));
	if (powers.size() < 1) endSimulation();
	sort(powers.begin(), powers.end());
}

bool lbcCmpRssi(CHInfo a, CHInfo b){
	return (a.rssi > b.rssi);
}
bool cmoBSDis(CHAdjacent a, CHAdjacent b){
	return (a.BSDistance > b.BSDistance);
}
bool lbcComEn(CHCompete a, CHCompete b){
	//if (a.cost == b.cost)
		//return a.residualEnergy > b.residualEnergy;
	return (a.ResidualEnergy > b.ResidualEnergy);
}
