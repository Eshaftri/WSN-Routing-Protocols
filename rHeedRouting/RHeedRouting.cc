
#include "RHeedRouting.h"

Define_Module(RHeedRouting);

void RHeedRouting::startup()
{	
	/*--- The .ned file's parameters ---*/
	percentage = par("percentage");
	roundLength = par("roundLength");
	rClustrLen = par("rClustrLen");
	isSink = par("isSink");
	slotLength = par("slotLength");
	advPacketSize = par("advPacketSize");
	joinPacketSize = par("joinPacketSize");
	tdmaPacketSize = par("tdmaPacketSize");
	dataPacketSize = par("dataPacketSize");
	applicationID = par("applicationID").stringValue(); 
	/*--- Class parameters ---*/
	Sch.clear();
	clusterMembers.clear();
	neighboursMembers.clear();
	Sfinal.clear();
	CHprob=0;
	count=0;
	CHprevious =0;
	roundNumber=0;
	probability = 0;
	isCH = false;
	endFormClus = false;
	isFinalCH = false;
	timer = uniform(0,1);
	readXMLparams();
	if(!isSink) 
		setTimer(INITIALIZE,0);
		
}

void RHeedRouting::fromApplicationLayer(cPacket *pkt, const char *destination)
{	
	if(!isSink)
	{
		string dst(destination);
		RHeedRoutingPacket *netPacket = new RHeedRoutingPacket("Heed routing data packet", NETWORK_LAYER_PACKET);
		netPacket->setRHeedRoutingPacketKind(RHEED_ROUTING_DATA_PACKET);
		netPacket->setByteLength(dataPacketSize);
		netPacket->setSource(SELF_NETWORK_ADDRESS);
		encapsulatePacket(netPacket, pkt);
		if (!isCH && endFormClus)
		{
			CHInfo info = *Sfinal.begin();
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

void RHeedRouting::fromMacLayer(cPacket *pkt, int macAddress, double rssi, double lqi){
	RHeedRoutingPacket *netPacket = dynamic_cast <RHeedRoutingPacket*>(pkt);

	if (!netPacket)
		return;

	switch (netPacket->getRHeedRoutingPacketKind()) {

		case RHEED_ROUTING_NIDV_PACKET:{
			//trace() << "Node " << self << " Received a Hello from Node " << netPacket->getSource();
            if (!isSink)
				neighboursMembers.push_back(atoi(netPacket->getSource()));
				
            break;
        }
		case RHEED_ROUTING_DATA_PACKET:{
			string dst(netPacket->getDestination());
			if (isCH && dst.compare(SELF_NETWORK_ADDRESS) == 0){
				//trace() << "Node " << self << " Aggregate Data Frame \n";
				bufferAggregate.push_back(*netPacket);	
			}else if (dst.compare(SINK_NETWORK_ADDRESS) == 0 && isSink) {
				//trace() << "Node " << self << " Processing Data Packet \n";
				toApplicationLayer(decapsulatePacket(netPacket));
			}
			break;	
		}

		case RHEED_ROUTING_ADV_PACKET:{
			if(!isSink){				  				
				trace() << "Nodem " << self << " Received a CH Message of node " << netPacket->getSource() ;	
		  		CHInfo rec;
		  		rec.src = atoi(netPacket->getSource());
				rec.cost = netPacket->getCost();
		  		rec.rssi = rssi;
		  			if(!netPacket->getStatus()){
				  		Sch.push_front(rec);	
				  		trace() << "Nodem " << self << " Received a tentative_CH Message of node " << netPacket->getSource() ;	
				  	}else{
				  		Sfinal.push_front(rec);
				  		Sch.push_front(rec);	
				  		trace() << "Nodem " << self << " Received a final_CH Message of node " << netPacket->getSource() ;	
				  	}
		    }
		 break;
		}

		case RHEED_ROUTING_RADV_PACKET:{
			if(!isSink){	
				clusterLength = netPacket->getScheduleArraySize();
				for(int i=0; i < netPacket->getScheduleArraySize(); i++) {
					if (netPacket->getSchedule(i)==atoi(SELF_NETWORK_ADDRESS)) {
						CHInfo rec;
						rec.src = atoi(netPacket->getSource());
						rec.cost = netPacket->getCost();
						rec.rssi = rssi;
						Sfinal.push_front(rec);
						endFormClus = true;
						setStateSleep();
						setTimer(START_SLOT, i*slotLength);
			        trace() << "Nodem " << self << " Received a rotate CH Message of node " << netPacket->getSource() ;	
			        break;
					}
		   		}
		 	}
		 	break;
        }
		case RHEED_ROUTING_JOIN_PACKET:{
			string dst(netPacket->getDestination());
				if(isCH && dst.compare(SELF_NETWORK_ADDRESS) == 0){
				  clusterMembers.push_back(atoi(netPacket->getSource()));
				//  trace() << "Node " << self << " is Cluster Head.";
				}
	 	    break;
		}

		case RHEED_ROUTING_TDMA_PACKET:{
			if(!isCH && !isSink){
			clusterLength = netPacket->getScheduleArraySize();
				for( int i=0; i<netPacket->getScheduleArraySize(); i++) {
					if (netPacket->getSchedule(i)==atoi(SELF_NETWORK_ADDRESS)) {
						trace() << "Node " << self << " == "<< netPacket->getSchedule(i) ;
						trace() << "Node " << self << " clusterLength "<<  netPacket->getScheduleArraySize() ;
					        setStateSleep();
							setTimer(START_SLOT, i*slotLength);
							for( int i=0; i<netPacket->getScheduleArraySize(); i++) {
								trace() << "Node " << self << " I am:The Last "<< i << " from " << netPacket->getSource();
					         clusterMembers.push_back(netPacket->getSchedule(i));
					     }
					     trace() << "Node " << self << " clusterLength2 "<<  clusterMembers.size() ;
					break;
					}			
				}
			}
    	break;
		}
	
	}
}

void RHeedRouting::timerFiredCallback(int index)
{
	timer = uniform(0,0.5);
	switch (index) {

		case INITIALIZE:{	
			setStateRx();
			setPowerLevel(maxPower);
			isCH = false;
			endFormClus = false;
			isFinalCH = false;
			count = 0;
			Sch.clear();
			Sfinal.clear();
			clusterMembers.clear();
			neighboursMembers.clear();
			if (getTimer(START_SLOT) != 0) { 
				cancelTimer(START_SLOT);
			}
			if (getTimer(START_ROT) != 0) { 
				cancelTimer(START_ROT);
			}
		    setTimer(NEB_DIS,timer);
			setTimer(REPEAT,1.5);
			setTimer(INITIALIZE, rClustrLen);
			setTimer(START_ROT,roundLength);
		break;
		}

		case NEB_DIS:{	
			neighboursDiscovery();
			break;
		}

		case REPEAT:{
			CHprob = getCHprob();
			//double ttimer = ((1/CHprob)/60);
			trace() << "Node " << self << " CHprob " << CHprob;
			//trace() << "Node " << self << " ttimer " << ttimer;
			CHprevious =0;
			do{
				randomNumber = uniform(0,1);
				if(Sch.size()!=0){
  					Sch.sort(cmpCos);
  					CHInfo info = *Sch.begin();
					stringstream buffer;
					buffer << info.src;
					string dst = buffer.str();
					trace() << "Node " << info.src << " Cost " << info.cost;
  					if(dst.compare(SELF_NETWORK_ADDRESS) == 0){
  						if(CHprob == 1){
  							isFinalCH = true;
  							setTimer(SEND_ADV, 0); //cluster_head_msg(NodeID,final_CH,cost)
  						}else{
							setTimer(SEND_ADV, 0); //cluster_head_msg(NodeID,tentative_CH,cost)
							trace() << "Node " << self << " 1tentative_CH";
							}	
  					}
  				}else{
  					if(CHprob == 1){
  						isFinalCH = true;
  						setTimer(SEND_ADV, 0); //cluster_head_msg(NodeID,final_CH,cost)
  					}else{
  						if(randomNumber <= CHprob){
  						setTimer(SEND_ADV, timer); //cluster_head_msg(NodeID,tentative_CH,cost)
  						trace() << "Node " << self << " 2tentative_CH";
  						trace() << "Node " << self << " Status " << isFinalCH ;

  						}
  					}
  				}
				CHprevious = round(CHprob);
				CHprob = CHprob * 2;
				trace() << "CHprevious " << CHprevious;
			}while(CHprevious < 1);
		/////////////////////////////////////////////////
			trace() << "neighboursCost " << neighboursMembers.size();
			trace() << "ClusterHeadCost " << Sch.size();
			trace() << "Find CH " << Sfinal.size();
			if(!isFinalCH){
				if(Sfinal.size()!=0){
					setTimer(JOIN_CH,1.0+timer);
					trace() << "Node " << self << " JOIN_CH";
				}else{
					isFinalCH = true;
					setTimer(SEND_ADV,0); //cl)uster_head_msg(NodeID,final_CH,cost)
					trace() << "Node " << self << " 1 final_CH";
					isCH = true;
					trace() << "Node " << self << " is Cluster Head.";
					setTimer(MAKE_TDMA,2.0+timer);
				}
			}else{
				isFinalCH = true;
  				setTimer(SEND_ADV,0); //cluster_head_msg(NodeID,final_CH,cost)
				setTimer(MAKE_TDMA,2.0+timer);
  				trace() << "Node " << self << " 2 final_CH";
  				isCH = true;
				trace() << "Node " << self << " is Cluster Head.";
			}
			
			break;
		}

		case SEND_ADV:{	
			if (neighboursMembers.size()!=0){
			RHeedRoutingPacket *crtlPkt = new RHeedRoutingPacket("ClusterHead Announcement Packet", NETWORK_LAYER_PACKET);
			crtlPkt->setByteLength(advPacketSize);
			crtlPkt->setRHeedRoutingPacketKind(RHEED_ROUTING_ADV_PACKET);
			crtlPkt->setSource(SELF_NETWORK_ADDRESS);
			crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
			crtlPkt->setCost(neighboursMembers.size());
			crtlPkt->setStatus(isFinalCH);
			toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
			trace() << "Node " << self << " Status" << isFinalCH ;
		  }
			break;
		}

		case SEND_RADV:{	
			RHeedRoutingPacket *crtlPkt = new RHeedRoutingPacket("Rotate CH Announcement Packet", NETWORK_LAYER_PACKET);
			crtlPkt->setByteLength(advPacketSize);
			crtlPkt->setRHeedRoutingPacketKind(RHEED_ROUTING_RADV_PACKET);
			crtlPkt->setSource(SELF_NETWORK_ADDRESS);
			crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
			clusterLength = clusterMembers.size();	
			crtlPkt->setScheduleArraySize(clusterMembers.size());	
			for(int i=0; i<clusterLength; i++) crtlPkt->setSchedule(i,clusterMembers[i]);
			toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
			setTimer(START_SLOT, clusterLength*slotLength);
				
			break;
		}

		case JOIN_CH:{
			if(Sfinal.size()!=0){	
				Sfinal.sort(cmpCos);
				RHeedRoutingPacket *crtlPkt = new RHeedRoutingPacket("ClusterMember Join Packet", NETWORK_LAYER_PACKET);
				crtlPkt->setRHeedRoutingPacketKind(RHEED_ROUTING_JOIN_PACKET);
				crtlPkt->setByteLength(joinPacketSize);	
				crtlPkt->setSource(SELF_NETWORK_ADDRESS);
				CHInfo info = *Sfinal.begin();
				stringstream buffer;
				buffer << info.src;
				string dst = buffer.str();
				crtlPkt->setDestination(dst.c_str());			
				toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
				endFormClus = true;
				trace() << "Node " << self << " Sent Join Request to CH " << dst << " With Cost " << info.cost;
			}
			break;
		}

		case MAKE_TDMA:{
			if (clusterMembers.size()!=0){
				RHeedRoutingPacket *crtlPkt = new RHeedRoutingPacket("ClusterHead TDMA Packet", NETWORK_LAYER_PACKET);
				crtlPkt->setByteLength(tdmaPacketSize);
				crtlPkt->setRHeedRoutingPacketKind(RHEED_ROUTING_TDMA_PACKET);
				crtlPkt->setSource(SELF_NETWORK_ADDRESS);
				crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
				clusterLength = clusterMembers.size();	
				crtlPkt->setScheduleArraySize(clusterMembers.size());	
				for(int i=0; i<clusterLength; i++) crtlPkt->setSchedule(i,clusterMembers[i]);
				toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
				trace() << "Node " << self << " Sent TDMA pkt";
				setTimer(START_SLOT, clusterLength*slotLength);
			}
			else setTimer(START_SLOT, slotLength);					
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
				CHInfo info = *Sfinal.begin();
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
		case START_ROT:{
			setTimer(START_ROT,roundLength);
			if (clusterMembers.size()!=0) {
				timer = uniform(0,0.5);
				setStateRx();
				setPowerLevel(maxPower);
				isCH = false;
				endFormClus = false;
				Sfinal.clear();
				if (getTimer(START_SLOT) != 0) { 
					cancelTimer(START_SLOT);
				}
				if (count == clusterMembers.size()){
					count =0;
				}
				if (clusterMembers[count]==atoi(SELF_NETWORK_ADDRESS)){
					isCH = true;
					setTimer(SEND_RADV,timer);
					trace() << "Node " << self << " CH after Rotate wit count "<< count << " and "<< clusterMembers[count];
				}
				count++ ;	
			}
			break;
		}
	}
}

void RHeedRouting::sendAggregate()
{
	if(bufferAggregate.size()!=0)
	{	
		double bitsLength = bufferAggregate.size() * dataPacketSize * 1000;
		double energyBit = (aggrConsumption / pow(10,9)) * bitsLength;
		powerDrawn(energyBit);
		RHeedRoutingPacket *aggrPacket = new RHeedRoutingPacket("ClusterHead Aggredated Packet", NETWORK_LAYER_PACKET);
		aggrPacket->setByteLength(dataPacketSize+4);
		aggrPacket->setRHeedRoutingPacketKind(RHEED_ROUTING_DATA_PACKET);
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
	}
}

void RHeedRouting::processBufferedPacket()
{
	while (!tempTXBuffer.empty())
	{
		cPacket *pkt = tempTXBuffer.front();	
		RHeedRoutingPacket *netPacket = dynamic_cast <RHeedRoutingPacket*>(pkt);
		CHInfo info = *Sfinal.begin();
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
	}	
}

void RHeedRouting::setStateRx()
{
	send(createRadioCommand(SET_STATE, RX), "toMacModule");	
}

void RHeedRouting::setPowerLevel(double powerLevel)
{
	send(createRadioCommand(SET_TX_OUTPUT, powerLevel), "toMacModule");
}

void RHeedRouting::setStateSleep()
{
	send(createRadioCommand(SET_STATE, SLEEP), "toMacModule");
}

void RHeedRouting::levelTxPower(int linkBudget)
{
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

void RHeedRouting::readXMLparams()
{
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

bool cmpCos(CHInfo a, CHInfo b){
	//if (a.cost == b.cost)
		//return a.residualEnergy > b.residualEnergy;
	return (a.cost < b.cost);
}

void RHeedRouting::neighboursDiscovery()
{
	RHeedRoutingPacket *crtlPkt = new RHeedRoutingPacket("Find Neighbours Packet", NETWORK_LAYER_PACKET);
		    crtlPkt->setByteLength(advPacketSize);
		    crtlPkt->setRHeedRoutingPacketKind(RHEED_ROUTING_NIDV_PACKET);
		    crtlPkt->setSource(SELF_NETWORK_ADDRESS);
		    crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
		    toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
		   // trace() << "Nodeo " << self << " Sent Find Neighbours Beacon";		    	
}
double RHeedRouting::getCHprob(void)
{
	ResourceManager *tmpResourceManager = check_and_cast<ResourceManager*>(getParentModule()->getParentModule()->getSubmodule("ResourceManager"));
  			double residualEnergy = tmpResourceManager->getRemainingEnergy();
  			double initialEnergy = tmpResourceManager->par("initialEnergy");
  			CHprob = percentage * (residualEnergy/initialEnergy);
  			return (CHprob);	    	
}
