
package node.communication.routing.rcaRouting;

simple RcaRouting like node.communication.routing.iRouting
{
parameters:
		string applicationID = default ("throughputTest");
	bool collectTraceInfo;
	int maxNetFrameSize = default (0);
	int netDataFrameOverhead = default (14);
	int netBufferSize = default (32);		
	bool isSink = default (false);
	
	double percentage;	
	double roundLength @unit(s);	
	double slotLength;

	//routing layer packet sizes
	int advPacketSize = default (9); // Type + Source + Destination = 9 bytes
	int joinPacketSize = default (9);
	int tdmaPacketSize = default (150); // Type + Source + Destination + tdma = 150 bytes
	int dataPacketSize = default (9);

	//Parameters used to power control.
	xml powersConfig;
	
	//EEUC STUFF
	double DMax = default (250);
	double DMin = default (30);
	double C = default(0.4);
	double RZeroComp = default(30);
	double K = default(2);
	double TD_Max = default(35);

gates: 
	output toCommunicationModule;
	output toMacModule;
	input fromCommunicationModule;
	input fromMacModule;
	input fromCommModuleResourceMgr;
}

