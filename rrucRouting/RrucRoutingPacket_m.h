//
// Generated file, do not edit! Created by opp_msgc 4.5 from src/node/communication/routing/rrucRouting/RrucRoutingPacket.msg.
//

#ifndef _RRUCROUTINGPACKET_M_H_
#define _RRUCROUTINGPACKET_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "RoutingPacket_m.h"
// }}



/**
 * Enum generated from <tt>src/node/communication/routing/rrucRouting/RrucRoutingPacket.msg</tt> by opp_msgc.
 * <pre>
 * enum RrucRoutingPacket_Type
 * {
 * 	RRUC_ROUTING_ADV_PACKET 	= 1;		
 * 	RRUC_ROUTING_JOIN_PACKET 	= 2;		
 * 	RRUC_ROUTING_TDMA_PACKET 	= 3;		
 * 	RRUC_ROUTING_DATA_PACKET 	= 4;
 * 	RRUC_ROUTING_COMPETECH_PACKET = 5;
 * 	RRUC_ROUTING_FINALHEAD_PACKET = 6;
 * 	RRUC_ROUTING_QUITELECTION_PACKET = 7;
 * 	RRUC_ROUTING_ADJACENTCH_PACKET = 8;
 * 	RRUC_ROUTING_AGGREGATEDADJACENT_PACKET = 9;
 * 	RRUC_ROUTING_ROTAT_TDMA_PACKET = 10;
 * };
 * </pre>
 */
enum RrucRoutingPacket_Type {
    RRUC_ROUTING_ADV_PACKET = 1,
    RRUC_ROUTING_JOIN_PACKET = 2,
    RRUC_ROUTING_TDMA_PACKET = 3,
    RRUC_ROUTING_DATA_PACKET = 4,
    RRUC_ROUTING_COMPETECH_PACKET = 5,
    RRUC_ROUTING_FINALHEAD_PACKET = 6,
    RRUC_ROUTING_QUITELECTION_PACKET = 7,
    RRUC_ROUTING_ADJACENTCH_PACKET = 8,
    RRUC_ROUTING_AGGREGATEDADJACENT_PACKET = 9,
    RRUC_ROUTING_ROTAT_TDMA_PACKET = 10
};

/**
 * Class generated from <tt>src/node/communication/routing/rrucRouting/RrucRoutingPacket.msg</tt> by opp_msgc.
 * <pre>
 * packet RrucRoutingPacket extends RoutingPacket
 * {	
 * 	int RrucRoutingPacketKind enum (RrucRoutingPacket_Type);   
 * 	int schedule[];	
 * 	double x;
 * 	double y;
 * 	double RComp;
 * 	double SpentEnergy;	
 * 	double BSDistance;
 * };
 * </pre>
 */
class RrucRoutingPacket : public ::RoutingPacket
{
  protected:
    int RrucRoutingPacketKind_var;
    int *schedule_var; // array ptr
    unsigned int schedule_arraysize;
    double x_var;
    double y_var;
    double RComp_var;
    double SpentEnergy_var;
    double BSDistance_var;

  private:
    void copy(const RrucRoutingPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RrucRoutingPacket&);

  public:
    RrucRoutingPacket(const char *name=NULL, int kind=0);
    RrucRoutingPacket(const RrucRoutingPacket& other);
    virtual ~RrucRoutingPacket();
    RrucRoutingPacket& operator=(const RrucRoutingPacket& other);
    virtual RrucRoutingPacket *dup() const {return new RrucRoutingPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getRrucRoutingPacketKind() const;
    virtual void setRrucRoutingPacketKind(int RrucRoutingPacketKind);
    virtual void setScheduleArraySize(unsigned int size);
    virtual unsigned int getScheduleArraySize() const;
    virtual int getSchedule(unsigned int k) const;
    virtual void setSchedule(unsigned int k, int schedule);
    virtual double getX() const;
    virtual void setX(double x);
    virtual double getY() const;
    virtual void setY(double y);
    virtual double getRComp() const;
    virtual void setRComp(double RComp);
    virtual double getSpentEnergy() const;
    virtual void setSpentEnergy(double SpentEnergy);
    virtual double getBSDistance() const;
    virtual void setBSDistance(double BSDistance);
};

inline void doPacking(cCommBuffer *b, RrucRoutingPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, RrucRoutingPacket& obj) {obj.parsimUnpack(b);}


#endif // _RRUCROUTINGPACKET_M_H_