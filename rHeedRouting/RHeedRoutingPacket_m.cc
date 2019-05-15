//
// Generated file, do not edit! Created by opp_msgc 4.5 from src/node/communication/routing/rHeedRouting/RHeedRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "RHeedRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("RHeedRoutingPacket_Type");
    if (!e) enums.getInstance()->add(e = new cEnum("RHeedRoutingPacket_Type"));
    e->insert(RHEED_ROUTING_ADV_PACKET, "RHEED_ROUTING_ADV_PACKET");
    e->insert(RHEED_ROUTING_JOIN_PACKET, "RHEED_ROUTING_JOIN_PACKET");
    e->insert(RHEED_ROUTING_TDMA_PACKET, "RHEED_ROUTING_TDMA_PACKET");
    e->insert(RHEED_ROUTING_DATA_PACKET, "RHEED_ROUTING_DATA_PACKET");
    e->insert(RHEED_ROUTING_NIDV_PACKET, "RHEED_ROUTING_NIDV_PACKET");
    e->insert(RHEED_ROUTING_RADV_PACKET, "RHEED_ROUTING_RADV_PACKET");
);

Register_Class(RHeedRoutingPacket);

RHeedRoutingPacket::RHeedRoutingPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->RHeedRoutingPacketKind_var = 0;
    schedule_arraysize = 0;
    this->schedule_var = 0;
    this->cost_var = 0;
    this->status_var = 0;
}

RHeedRoutingPacket::RHeedRoutingPacket(const RHeedRoutingPacket& other) : ::RoutingPacket(other)
{
    schedule_arraysize = 0;
    this->schedule_var = 0;
    copy(other);
}

RHeedRoutingPacket::~RHeedRoutingPacket()
{
    delete [] schedule_var;
}

RHeedRoutingPacket& RHeedRoutingPacket::operator=(const RHeedRoutingPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void RHeedRoutingPacket::copy(const RHeedRoutingPacket& other)
{
    this->RHeedRoutingPacketKind_var = other.RHeedRoutingPacketKind_var;
    delete [] this->schedule_var;
    this->schedule_var = (other.schedule_arraysize==0) ? NULL : new int[other.schedule_arraysize];
    schedule_arraysize = other.schedule_arraysize;
    for (unsigned int i=0; i<schedule_arraysize; i++)
        this->schedule_var[i] = other.schedule_var[i];
    this->cost_var = other.cost_var;
    this->status_var = other.status_var;
}

void RHeedRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->RHeedRoutingPacketKind_var);
    b->pack(schedule_arraysize);
    doPacking(b,this->schedule_var,schedule_arraysize);
    doPacking(b,this->cost_var);
    doPacking(b,this->status_var);
}

void RHeedRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->RHeedRoutingPacketKind_var);
    delete [] this->schedule_var;
    b->unpack(schedule_arraysize);
    if (schedule_arraysize==0) {
        this->schedule_var = 0;
    } else {
        this->schedule_var = new int[schedule_arraysize];
        doUnpacking(b,this->schedule_var,schedule_arraysize);
    }
    doUnpacking(b,this->cost_var);
    doUnpacking(b,this->status_var);
}

int RHeedRoutingPacket::getRHeedRoutingPacketKind() const
{
    return RHeedRoutingPacketKind_var;
}

void RHeedRoutingPacket::setRHeedRoutingPacketKind(int RHeedRoutingPacketKind)
{
    this->RHeedRoutingPacketKind_var = RHeedRoutingPacketKind;
}

void RHeedRoutingPacket::setScheduleArraySize(unsigned int size)
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

unsigned int RHeedRoutingPacket::getScheduleArraySize() const
{
    return schedule_arraysize;
}

int RHeedRoutingPacket::getSchedule(unsigned int k) const
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    return schedule_var[k];
}

void RHeedRoutingPacket::setSchedule(unsigned int k, int schedule)
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    this->schedule_var[k] = schedule;
}

int RHeedRoutingPacket::getCost() const
{
    return cost_var;
}

void RHeedRoutingPacket::setCost(int cost)
{
    this->cost_var = cost;
}

bool RHeedRoutingPacket::getStatus() const
{
    return status_var;
}

void RHeedRoutingPacket::setStatus(bool status)
{
    this->status_var = status;
}

class RHeedRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    RHeedRoutingPacketDescriptor();
    virtual ~RHeedRoutingPacketDescriptor();

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

Register_ClassDescriptor(RHeedRoutingPacketDescriptor);

RHeedRoutingPacketDescriptor::RHeedRoutingPacketDescriptor() : cClassDescriptor("RHeedRoutingPacket", "RoutingPacket")
{
}

RHeedRoutingPacketDescriptor::~RHeedRoutingPacketDescriptor()
{
}

bool RHeedRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RHeedRoutingPacket *>(obj)!=NULL;
}

const char *RHeedRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RHeedRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int RHeedRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *RHeedRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "RHeedRoutingPacketKind",
        "schedule",
        "cost",
        "status",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int RHeedRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RHeedRoutingPacketKind")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "schedule")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "cost")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RHeedRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "bool",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *RHeedRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "RHeedRoutingPacket_Type";
            return NULL;
        default: return NULL;
    }
}

int RHeedRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RHeedRoutingPacket *pp = (RHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 1: return pp->getScheduleArraySize();
        default: return 0;
    }
}

std::string RHeedRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RHeedRoutingPacket *pp = (RHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRHeedRoutingPacketKind());
        case 1: return long2string(pp->getSchedule(i));
        case 2: return long2string(pp->getCost());
        case 3: return bool2string(pp->getStatus());
        default: return "";
    }
}

bool RHeedRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RHeedRoutingPacket *pp = (RHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRHeedRoutingPacketKind(string2long(value)); return true;
        case 1: pp->setSchedule(i,string2long(value)); return true;
        case 2: pp->setCost(string2long(value)); return true;
        case 3: pp->setStatus(string2bool(value)); return true;
        default: return false;
    }
}

const char *RHeedRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *RHeedRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RHeedRoutingPacket *pp = (RHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


