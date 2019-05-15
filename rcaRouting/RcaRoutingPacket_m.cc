//
// Generated file, do not edit! Created by opp_msgc 4.5 from src/node/communication/routing/rcaRouting/RcaRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "RcaRoutingPacket_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("RcaRoutingPacket_Type");
    if (!e) enums.getInstance()->add(e = new cEnum("RcaRoutingPacket_Type"));
    e->insert(RCA_ROUTING_ADV_PACKET, "RCA_ROUTING_ADV_PACKET");
    e->insert(RCA_ROUTING_JOIN_PACKET, "RCA_ROUTING_JOIN_PACKET");
    e->insert(RCA_ROUTING_TDMA_PACKET, "RCA_ROUTING_TDMA_PACKET");
    e->insert(RCA_ROUTING_DATA_PACKET, "RCA_ROUTING_DATA_PACKET");
    e->insert(RCA_ROUTING_COMPETECH_PACKET, "RCA_ROUTING_COMPETECH_PACKET");
    e->insert(RCA_ROUTING_FINALHEAD_PACKET, "RCA_ROUTING_FINALHEAD_PACKET");
    e->insert(RCA_ROUTING_QUITELECTION_PACKET, "RCA_ROUTING_QUITELECTION_PACKET");
    e->insert(RCA_ROUTING_ADJACENTCH_PACKET, "RCA_ROUTING_ADJACENTCH_PACKET");
    e->insert(RCA_ROUTING_AGGREGATEDADJACENT_PACKET, "RCA_ROUTING_AGGREGATEDADJACENT_PACKET");
    e->insert(RCA_ROUTING_ROTAT_TDMA_PACKET, "RCA_ROUTING_ROTAT_TDMA_PACKET");
    e->insert(RCA_ROUTING_BS_PACKET, "RCA_ROUTING_BS_PACKET");
    e->insert(RCA_ROUTING_BROADCAST_BS_PACKET, "RCA_ROUTING_BROADCAST_BS_PACKET");
    e->insert(RCA_ROUTING_AGGREGATED_BS_PACKET, "RCA_ROUTING_AGGREGATED_BS_PACKET");
    e->insert(RCA_ROUTING_HELLO_PACKET, "RCA_ROUTING_HELLO_PACKET");
);

Register_Class(RcaRoutingPacket);

RcaRoutingPacket::RcaRoutingPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->RcaRoutingPacketKind_var = 0;
    schedule_arraysize = 0;
    this->schedule_var = 0;
    this->x_var = 0;
    this->y_var = 0;
    this->Tn_var = 0;
    this->RComp_var = 0;
    this->ResidualEnergy_var = 0;
    this->BSDistance_var = 0;
    this->Wght_var = 0;
}

RcaRoutingPacket::RcaRoutingPacket(const RcaRoutingPacket& other) : ::RoutingPacket(other)
{
    schedule_arraysize = 0;
    this->schedule_var = 0;
    copy(other);
}

RcaRoutingPacket::~RcaRoutingPacket()
{
    delete [] schedule_var;
}

RcaRoutingPacket& RcaRoutingPacket::operator=(const RcaRoutingPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void RcaRoutingPacket::copy(const RcaRoutingPacket& other)
{
    this->RcaRoutingPacketKind_var = other.RcaRoutingPacketKind_var;
    delete [] this->schedule_var;
    this->schedule_var = (other.schedule_arraysize==0) ? NULL : new int[other.schedule_arraysize];
    schedule_arraysize = other.schedule_arraysize;
    for (unsigned int i=0; i<schedule_arraysize; i++)
        this->schedule_var[i] = other.schedule_var[i];
    this->x_var = other.x_var;
    this->y_var = other.y_var;
    this->Tn_var = other.Tn_var;
    this->RComp_var = other.RComp_var;
    this->ResidualEnergy_var = other.ResidualEnergy_var;
    this->BSDistance_var = other.BSDistance_var;
    this->Wght_var = other.Wght_var;
}

void RcaRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->RcaRoutingPacketKind_var);
    b->pack(schedule_arraysize);
    doPacking(b,this->schedule_var,schedule_arraysize);
    doPacking(b,this->x_var);
    doPacking(b,this->y_var);
    doPacking(b,this->Tn_var);
    doPacking(b,this->RComp_var);
    doPacking(b,this->ResidualEnergy_var);
    doPacking(b,this->BSDistance_var);
    doPacking(b,this->Wght_var);
}

void RcaRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->RcaRoutingPacketKind_var);
    delete [] this->schedule_var;
    b->unpack(schedule_arraysize);
    if (schedule_arraysize==0) {
        this->schedule_var = 0;
    } else {
        this->schedule_var = new int[schedule_arraysize];
        doUnpacking(b,this->schedule_var,schedule_arraysize);
    }
    doUnpacking(b,this->x_var);
    doUnpacking(b,this->y_var);
    doUnpacking(b,this->Tn_var);
    doUnpacking(b,this->RComp_var);
    doUnpacking(b,this->ResidualEnergy_var);
    doUnpacking(b,this->BSDistance_var);
    doUnpacking(b,this->Wght_var);
}

int RcaRoutingPacket::getRcaRoutingPacketKind() const
{
    return RcaRoutingPacketKind_var;
}

void RcaRoutingPacket::setRcaRoutingPacketKind(int RcaRoutingPacketKind)
{
    this->RcaRoutingPacketKind_var = RcaRoutingPacketKind;
}

void RcaRoutingPacket::setScheduleArraySize(unsigned int size)
{
    int *schedule_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = schedule_arraysize < size ? schedule_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        schedule_var2[i] = this->schedule_var[i];
    for (unsigned int i=sz; i<size; i++)
        schedule_var2[i] = 0;
    schedule_arraysize = size;
    delete [] this->schedule_var;
    this->schedule_var = schedule_var2;
}

unsigned int RcaRoutingPacket::getScheduleArraySize() const
{
    return schedule_arraysize;
}

int RcaRoutingPacket::getSchedule(unsigned int k) const
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    return schedule_var[k];
}

void RcaRoutingPacket::setSchedule(unsigned int k, int schedule)
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    this->schedule_var[k] = schedule;
}

double RcaRoutingPacket::getX() const
{
    return x_var;
}

void RcaRoutingPacket::setX(double x)
{
    this->x_var = x;
}

double RcaRoutingPacket::getY() const
{
    return y_var;
}

void RcaRoutingPacket::setY(double y)
{
    this->y_var = y;
}

double RcaRoutingPacket::getTn() const
{
    return Tn_var;
}

void RcaRoutingPacket::setTn(double Tn)
{
    this->Tn_var = Tn;
}

double RcaRoutingPacket::getRComp() const
{
    return RComp_var;
}

void RcaRoutingPacket::setRComp(double RComp)
{
    this->RComp_var = RComp;
}

double RcaRoutingPacket::getResidualEnergy() const
{
    return ResidualEnergy_var;
}

void RcaRoutingPacket::setResidualEnergy(double ResidualEnergy)
{
    this->ResidualEnergy_var = ResidualEnergy;
}

double RcaRoutingPacket::getBSDistance() const
{
    return BSDistance_var;
}

void RcaRoutingPacket::setBSDistance(double BSDistance)
{
    this->BSDistance_var = BSDistance;
}

double RcaRoutingPacket::getWght() const
{
    return Wght_var;
}

void RcaRoutingPacket::setWght(double Wght)
{
    this->Wght_var = Wght;
}

class RcaRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    RcaRoutingPacketDescriptor();
    virtual ~RcaRoutingPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(RcaRoutingPacketDescriptor);

RcaRoutingPacketDescriptor::RcaRoutingPacketDescriptor() : cClassDescriptor("RcaRoutingPacket", "RoutingPacket")
{
}

RcaRoutingPacketDescriptor::~RcaRoutingPacketDescriptor()
{
}

bool RcaRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RcaRoutingPacket *>(obj)!=NULL;
}

const char *RcaRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RcaRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount(object) : 9;
}

unsigned int RcaRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *RcaRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "RcaRoutingPacketKind",
        "schedule",
        "x",
        "y",
        "Tn",
        "RComp",
        "ResidualEnergy",
        "BSDistance",
        "Wght",
    };
    return (field>=0 && field<9) ? fieldNames[field] : NULL;
}

int RcaRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RcaRoutingPacketKind")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "schedule")==0) return base+1;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+2;
    if (fieldName[0]=='y' && strcmp(fieldName, "y")==0) return base+3;
    if (fieldName[0]=='T' && strcmp(fieldName, "Tn")==0) return base+4;
    if (fieldName[0]=='R' && strcmp(fieldName, "RComp")==0) return base+5;
    if (fieldName[0]=='R' && strcmp(fieldName, "ResidualEnergy")==0) return base+6;
    if (fieldName[0]=='B' && strcmp(fieldName, "BSDistance")==0) return base+7;
    if (fieldName[0]=='W' && strcmp(fieldName, "Wght")==0) return base+8;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RcaRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : NULL;
}

const char *RcaRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "RcaRoutingPacket_Type";
            return NULL;
        default: return NULL;
    }
}

int RcaRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RcaRoutingPacket *pp = (RcaRoutingPacket *)object; (void)pp;
    switch (field) {
        case 1: return pp->getScheduleArraySize();
        default: return 0;
    }
}

std::string RcaRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RcaRoutingPacket *pp = (RcaRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRcaRoutingPacketKind());
        case 1: return long2string(pp->getSchedule(i));
        case 2: return double2string(pp->getX());
        case 3: return double2string(pp->getY());
        case 4: return double2string(pp->getTn());
        case 5: return double2string(pp->getRComp());
        case 6: return double2string(pp->getResidualEnergy());
        case 7: return double2string(pp->getBSDistance());
        case 8: return double2string(pp->getWght());
        default: return "";
    }
}

bool RcaRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RcaRoutingPacket *pp = (RcaRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRcaRoutingPacketKind(string2long(value)); return true;
        case 1: pp->setSchedule(i,string2long(value)); return true;
        case 2: pp->setX(string2double(value)); return true;
        case 3: pp->setY(string2double(value)); return true;
        case 4: pp->setTn(string2double(value)); return true;
        case 5: pp->setRComp(string2double(value)); return true;
        case 6: pp->setResidualEnergy(string2double(value)); return true;
        case 7: pp->setBSDistance(string2double(value)); return true;
        case 8: pp->setWght(string2double(value)); return true;
        default: return false;
    }
}

const char *RcaRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *RcaRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RcaRoutingPacket *pp = (RcaRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


