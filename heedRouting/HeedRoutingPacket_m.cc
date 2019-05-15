//
// Generated file, do not edit! Created by opp_msgc 4.5 from src/node/communication/routing/heedRouting/HeedRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "HeedRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("HeedRoutingPacket_Type");
    if (!e) enums.getInstance()->add(e = new cEnum("HeedRoutingPacket_Type"));
    e->insert(HEED_ROUTING_ADV_PACKET, "HEED_ROUTING_ADV_PACKET");
    e->insert(HEED_ROUTING_JOIN_PACKET, "HEED_ROUTING_JOIN_PACKET");
    e->insert(HEED_ROUTING_TDMA_PACKET, "HEED_ROUTING_TDMA_PACKET");
    e->insert(HEED_ROUTING_DATA_PACKET, "HEED_ROUTING_DATA_PACKET");
    e->insert(HEED_NEIGHBOURS_DISCOVERY_PACKET, "HEED_NEIGHBOURS_DISCOVERY_PACKET");
);

Register_Class(HeedRoutingPacket);

HeedRoutingPacket::HeedRoutingPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->HeedRoutingPacketKind_var = 0;
    schedule_arraysize = 0;
    this->schedule_var = 0;
    this->cost_var = 0;
    this->status_var = 0;
}

HeedRoutingPacket::HeedRoutingPacket(const HeedRoutingPacket& other) : ::RoutingPacket(other)
{
    schedule_arraysize = 0;
    this->schedule_var = 0;
    copy(other);
}

HeedRoutingPacket::~HeedRoutingPacket()
{
    delete [] schedule_var;
}

HeedRoutingPacket& HeedRoutingPacket::operator=(const HeedRoutingPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void HeedRoutingPacket::copy(const HeedRoutingPacket& other)
{
    this->HeedRoutingPacketKind_var = other.HeedRoutingPacketKind_var;
    delete [] this->schedule_var;
    this->schedule_var = (other.schedule_arraysize==0) ? NULL : new int[other.schedule_arraysize];
    schedule_arraysize = other.schedule_arraysize;
    for (unsigned int i=0; i<schedule_arraysize; i++)
        this->schedule_var[i] = other.schedule_var[i];
    this->cost_var = other.cost_var;
    this->status_var = other.status_var;
}

void HeedRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->HeedRoutingPacketKind_var);
    b->pack(schedule_arraysize);
    doPacking(b,this->schedule_var,schedule_arraysize);
    doPacking(b,this->cost_var);
    doPacking(b,this->status_var);
}

void HeedRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->HeedRoutingPacketKind_var);
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

int HeedRoutingPacket::getHeedRoutingPacketKind() const
{
    return HeedRoutingPacketKind_var;
}

void HeedRoutingPacket::setHeedRoutingPacketKind(int HeedRoutingPacketKind)
{
    this->HeedRoutingPacketKind_var = HeedRoutingPacketKind;
}

void HeedRoutingPacket::setScheduleArraySize(unsigned int size)
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

unsigned int HeedRoutingPacket::getScheduleArraySize() const
{
    return schedule_arraysize;
}

int HeedRoutingPacket::getSchedule(unsigned int k) const
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    return schedule_var[k];
}

void HeedRoutingPacket::setSchedule(unsigned int k, int schedule)
{
    if (k>=schedule_arraysize) throw cRuntimeError("Array of size %d indexed by %d", schedule_arraysize, k);
    this->schedule_var[k] = schedule;
}

int HeedRoutingPacket::getCost() const
{
    return cost_var;
}

void HeedRoutingPacket::setCost(int cost)
{
    this->cost_var = cost;
}

bool HeedRoutingPacket::getStatus() const
{
    return status_var;
}

void HeedRoutingPacket::setStatus(bool status)
{
    this->status_var = status;
}

class HeedRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    HeedRoutingPacketDescriptor();
    virtual ~HeedRoutingPacketDescriptor();

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

Register_ClassDescriptor(HeedRoutingPacketDescriptor);

HeedRoutingPacketDescriptor::HeedRoutingPacketDescriptor() : cClassDescriptor("HeedRoutingPacket", "RoutingPacket")
{
}

HeedRoutingPacketDescriptor::~HeedRoutingPacketDescriptor()
{
}

bool HeedRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<HeedRoutingPacket *>(obj)!=NULL;
}

const char *HeedRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HeedRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int HeedRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *HeedRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "HeedRoutingPacketKind",
        "schedule",
        "cost",
        "status",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int HeedRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='H' && strcmp(fieldName, "HeedRoutingPacketKind")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "schedule")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "cost")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *HeedRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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

const char *HeedRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "HeedRoutingPacket_Type";
            return NULL;
        default: return NULL;
    }
}

int HeedRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HeedRoutingPacket *pp = (HeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 1: return pp->getScheduleArraySize();
        default: return 0;
    }
}

std::string HeedRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    HeedRoutingPacket *pp = (HeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeedRoutingPacketKind());
        case 1: return long2string(pp->getSchedule(i));
        case 2: return long2string(pp->getCost());
        case 3: return bool2string(pp->getStatus());
        default: return "";
    }
}

bool HeedRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HeedRoutingPacket *pp = (HeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeedRoutingPacketKind(string2long(value)); return true;
        case 1: pp->setSchedule(i,string2long(value)); return true;
        case 2: pp->setCost(string2long(value)); return true;
        case 3: pp->setStatus(string2bool(value)); return true;
        default: return false;
    }
}

const char *HeedRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *HeedRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HeedRoutingPacket *pp = (HeedRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


