//
// Generated file, do not edit! Created by opp_msgc 4.5 from src/node/communication/routing/rrucRouting/RrucRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "RrucRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("RrucRoutingPacket_Type");
    if (!e) enums.getInstance()->add(e = new cEnum("RrucRoutingPacket_Type"));
    e->insert(RRUC_ROUTING_ADV_PACKET, "RRUC_ROUTING_ADV_PACKET");
    e->insert(RRUC_ROUTING_JOIN_PACKET, "RRUC_ROUTING_JOIN_PACKET");
    e->insert(RRUC_ROUTING_TDMA_PACKET, "RRUC_ROUTING_TDMA_PACKET");
    e->insert(RRUC_ROUTING_DATA_PACKET, "RRUC_ROUTING_DATA_PACKET");
    e->insert(RRUC_ROUTING_COMPETECH_PACKET, "RRUC_ROUTING_COMPETECH_PACKET");
    e->insert(RRUC_ROUTING_FINALHEAD_PACKET, "RRUC_ROUTING_FINALHEAD_PACKET");
    e->insert(RRUC_ROUTING_QUITELECTION_PACKET, "RRUC_ROUTING_QUITELECTION_PACKET");
    e->insert(RRUC_ROUTING_ADJACENTCH_PACKET, "RRUC_ROUTING_ADJACENTCH_PACKET");
    e->insert(RRUC_ROUTING_AGGREGATEDADJACENT_PACKET, "RRUC_ROUTING_AGGREGATEDADJACENT_PACKET");
    e->insert(RRUC_ROUTING_ROTAT_TDMA_PACKET, "RRUC_ROUTING_ROTAT_TDMA_PACKET");
);

Register_Class(RrucRoutingPacket);

RrucRoutingPacket::RrucRoutingPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->RrucRoutingPacketKind_var = 0;
    schedule_arraysize = 0;
    this->schedule_var = 0;
    this->x_var = 0;
    this->y_var = 0;
    this->RComp_var = 0;
    this->SpentEnergy_var = 0;
    this->BSDistance_var = 0;
}

RrucRoutingPacket::RrucRoutingPacket(const RrucRoutingPacket& other) : ::RoutingPacket(other)
{
    schedule_arraysize = 0;
    this->schedule_var = 0;
    copy(other);
}

RrucRoutingPacket::~RrucRoutingPacket()
{
    delete [] schedule_var;
}

RrucRoutingPacket& RrucRoutingPacket::operator=(const RrucRoutingPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void RrucRoutingPacket::copy(const RrucRoutingPacket& other)
{
    this->RrucRoutingPacketKind_var = other.RrucRoutingPacketKind_var;
    delete [] this->schedule_var;
    this->schedule_var = (other.schedule_arraysize==0) ? NULL : new int[other.schedule_arraysize];
    schedule_arraysize = other.schedule_arraysize;
    for (unsigned int i=0; i<schedule_arraysize; i++)
        this->schedule_var[i] = other.schedule_var[i];
    this->x_var = other.x_var;
    this->y_var = other.y_var;
    this->RComp_var = other.RComp_var;
    this->SpentEnergy_var = other.SpentEnergy_var;
    this->BSDistance_var = other.BSDistance_var;
}

void RrucRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->RrucRoutingPacketKind_var);
    b->pack(schedule_arraysize);
    doPacking(b,this->schedule_var,schedule_arraysize);
    doPacking(b,this->x_var);
    doPacking(b,this->y_var);
    doPacking(b,this->RComp_var);
    doPacking(b,this->SpentEnergy_var);
    doPacking(b,this->BSDistance_var);
}

void RrucRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->RrucRoutingPacketKind_var);
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
    doUnpacking(b,this->RComp_var);
    doUnpacking(b,this->SpentEnergy_var);
    doUnpacking(b,this->BSDistance_var);
}

int RrucRoutingPacket::getRrucRoutingPacketKind() const
{
    return RrucRoutingPacketKind_var;
}

void RrucRoutingPacket::setRrucRoutingPacketKind(int RrucRoutingPacketKind)
{
    this->RrucRoutingPacketKind_var = RrucRoutingPacketKind;
}

void RrucRoutingPacket::setScheduleArraySize(unsigned int size)
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

unsigned int RrucRoutingPacket::getScheduleArraySize() const
{
    return schedule_arraysize;
}

int RrucRoutingPacket::getSchedule(unsigned int k) const
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    return schedule_var[k];
}

void RrucRoutingPacket::setSchedule(unsigned int k, int schedule)
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    this->schedule_var[k] = schedule;
}

double RrucRoutingPacket::getX() const
{
    return x_var;
}

void RrucRoutingPacket::setX(double x)
{
    this->x_var = x;
}

double RrucRoutingPacket::getY() const
{
    return y_var;
}

void RrucRoutingPacket::setY(double y)
{
    this->y_var = y;
}

double RrucRoutingPacket::getRComp() const
{
    return RComp_var;
}

void RrucRoutingPacket::setRComp(double RComp)
{
    this->RComp_var = RComp;
}

double RrucRoutingPacket::getSpentEnergy() const
{
    return SpentEnergy_var;
}

void RrucRoutingPacket::setSpentEnergy(double SpentEnergy)
{
    this->SpentEnergy_var = SpentEnergy;
}

double RrucRoutingPacket::getBSDistance() const
{
    return BSDistance_var;
}

void RrucRoutingPacket::setBSDistance(double BSDistance)
{
    this->BSDistance_var = BSDistance;
}

class RrucRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    RrucRoutingPacketDescriptor();
    virtual ~RrucRoutingPacketDescriptor();

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

Register_ClassDescriptor(RrucRoutingPacketDescriptor);

RrucRoutingPacketDescriptor::RrucRoutingPacketDescriptor() : cClassDescriptor("RrucRoutingPacket", "RoutingPacket")
{
}

RrucRoutingPacketDescriptor::~RrucRoutingPacketDescriptor()
{
}

bool RrucRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RrucRoutingPacket *>(obj)!=NULL;
}

const char *RrucRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RrucRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int RrucRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *RrucRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "RrucRoutingPacketKind",
        "schedule",
        "x",
        "y",
        "RComp",
        "SpentEnergy",
        "BSDistance",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int RrucRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RrucRoutingPacketKind")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "schedule")==0) return base+1;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+2;
    if (fieldName[0]=='y' && strcmp(fieldName, "y")==0) return base+3;
    if (fieldName[0]=='R' && strcmp(fieldName, "RComp")==0) return base+4;
    if (fieldName[0]=='S' && strcmp(fieldName, "SpentEnergy")==0) return base+5;
    if (fieldName[0]=='B' && strcmp(fieldName, "BSDistance")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RrucRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *RrucRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "RrucRoutingPacket_Type";
            return NULL;
        default: return NULL;
    }
}

int RrucRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RrucRoutingPacket *pp = (RrucRoutingPacket *)object; (void)pp;
    switch (field) {
        case 1: return pp->getScheduleArraySize();
        default: return 0;
    }
}

std::string RrucRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RrucRoutingPacket *pp = (RrucRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRrucRoutingPacketKind());
        case 1: return long2string(pp->getSchedule(i));
        case 2: return double2string(pp->getX());
        case 3: return double2string(pp->getY());
        case 4: return double2string(pp->getRComp());
        case 5: return double2string(pp->getSpentEnergy());
        case 6: return double2string(pp->getBSDistance());
        default: return "";
    }
}

bool RrucRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RrucRoutingPacket *pp = (RrucRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRrucRoutingPacketKind(string2long(value)); return true;
        case 1: pp->setSchedule(i,string2long(value)); return true;
        case 2: pp->setX(string2double(value)); return true;
        case 3: pp->setY(string2double(value)); return true;
        case 4: pp->setRComp(string2double(value)); return true;
        case 5: pp->setSpentEnergy(string2double(value)); return true;
        case 6: pp->setBSDistance(string2double(value)); return true;
        default: return false;
    }
}

const char *RrucRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *RrucRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RrucRoutingPacket *pp = (RrucRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


