//
// Generated file, do not edit! Created by opp_msgc 4.5 from src/node/communication/routing/sHeedRouting/SHeedRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "SHeedRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("SHeedRoutingPacket_Type");
    if (!e) enums.getInstance()->add(e = new cEnum("SHeedRoutingPacket_Type"));
    e->insert(SHEED_ROUTING_ADV_PACKET, "SHEED_ROUTING_ADV_PACKET");
    e->insert(SHEED_ROUTING_JOIN_PACKET, "SHEED_ROUTING_JOIN_PACKET");
    e->insert(SHEED_ROUTING_TDMA_PACKET, "SHEED_ROUTING_TDMA_PACKET");
    e->insert(SHEED_ROUTING_DATA_PACKET, "SHEED_ROUTING_DATA_PACKET");
    e->insert(SHEED_ROUTING_NIDV_PACKET, "SHEED_ROUTING_NIDV_PACKET");
    e->insert(SHEED_ROUTING_RADV_PACKET, "SHEED_ROUTING_RADV_PACKET");
);

NDInf::NDInf()
{
    src = 0;
    eng = 0;
}

void doPacking(cCommBuffer *b, NDInf& a)
{
    doPacking(b,a.src);
    doPacking(b,a.eng);
}

void doUnpacking(cCommBuffer *b, NDInf& a)
{
    doUnpacking(b,a.src);
    doUnpacking(b,a.eng);
}

class NDInfDescriptor : public cClassDescriptor
{
  public:
    NDInfDescriptor();
    virtual ~NDInfDescriptor();

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

Register_ClassDescriptor(NDInfDescriptor);

NDInfDescriptor::NDInfDescriptor() : cClassDescriptor("NDInf", "")
{
}

NDInfDescriptor::~NDInfDescriptor()
{
}

bool NDInfDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NDInf *>(obj)!=NULL;
}

const char *NDInfDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NDInfDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int NDInfDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *NDInfDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "src",
        "eng",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int NDInfDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='e' && strcmp(fieldName, "eng")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NDInfDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *NDInfDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int NDInfDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NDInf *pp = (NDInf *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NDInfDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NDInf *pp = (NDInf *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->src);
        case 1: return double2string(pp->eng);
        default: return "";
    }
}

bool NDInfDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NDInf *pp = (NDInf *)object; (void)pp;
    switch (field) {
        case 0: pp->src = string2long(value); return true;
        case 1: pp->eng = string2double(value); return true;
        default: return false;
    }
}

const char *NDInfDescriptor::getFieldStructName(void *object, int field) const
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

void *NDInfDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NDInf *pp = (NDInf *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SHeedRoutingPacket);

SHeedRoutingPacket::SHeedRoutingPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->SHeedRoutingPacketKind_var = 0;
    this->cost_var = 0;
    this->eng_var = 0;
    this->status_var = 0;
    clusterMembers_arraysize = 0;
    this->clusterMembers_var = 0;
}

SHeedRoutingPacket::SHeedRoutingPacket(const SHeedRoutingPacket& other) : ::RoutingPacket(other)
{
    clusterMembers_arraysize = 0;
    this->clusterMembers_var = 0;
    copy(other);
}

SHeedRoutingPacket::~SHeedRoutingPacket()
{
    delete [] clusterMembers_var;
}

SHeedRoutingPacket& SHeedRoutingPacket::operator=(const SHeedRoutingPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void SHeedRoutingPacket::copy(const SHeedRoutingPacket& other)
{
    this->SHeedRoutingPacketKind_var = other.SHeedRoutingPacketKind_var;
    this->cost_var = other.cost_var;
    this->eng_var = other.eng_var;
    this->status_var = other.status_var;
    delete [] this->clusterMembers_var;
    this->clusterMembers_var = (other.clusterMembers_arraysize==0) ? NULL : new NDInf[other.clusterMembers_arraysize];
    clusterMembers_arraysize = other.clusterMembers_arraysize;
    for (unsigned int i=0; i<clusterMembers_arraysize; i++)
        this->clusterMembers_var[i] = other.clusterMembers_var[i];
}

void SHeedRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->SHeedRoutingPacketKind_var);
    doPacking(b,this->cost_var);
    doPacking(b,this->eng_var);
    doPacking(b,this->status_var);
    b->pack(clusterMembers_arraysize);
    doPacking(b,this->clusterMembers_var,clusterMembers_arraysize);
}

void SHeedRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->SHeedRoutingPacketKind_var);
    doUnpacking(b,this->cost_var);
    doUnpacking(b,this->eng_var);
    doUnpacking(b,this->status_var);
    delete [] this->clusterMembers_var;
    b->unpack(clusterMembers_arraysize);
    if (clusterMembers_arraysize==0) {
        this->clusterMembers_var = 0;
    } else {
        this->clusterMembers_var = new NDInf[clusterMembers_arraysize];
        doUnpacking(b,this->clusterMembers_var,clusterMembers_arraysize);
    }
}

int SHeedRoutingPacket::getSHeedRoutingPacketKind() const
{
    return SHeedRoutingPacketKind_var;
}

void SHeedRoutingPacket::setSHeedRoutingPacketKind(int SHeedRoutingPacketKind)
{
    this->SHeedRoutingPacketKind_var = SHeedRoutingPacketKind;
}

int SHeedRoutingPacket::getCost() const
{
    return cost_var;
}

void SHeedRoutingPacket::setCost(int cost)
{
    this->cost_var = cost;
}

double SHeedRoutingPacket::getEng() const
{
    return eng_var;
}

void SHeedRoutingPacket::setEng(double eng)
{
    this->eng_var = eng;
}

bool SHeedRoutingPacket::getStatus() const
{
    return status_var;
}

void SHeedRoutingPacket::setStatus(bool status)
{
    this->status_var = status;
}

void SHeedRoutingPacket::setClusterMembersArraySize(unsigned int size)
{
    NDInf *clusterMembers_var2 = (size==0) ? NULL : new NDInf[size];
    unsigned int sz = clusterMembers_arraysize < size ? clusterMembers_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        clusterMembers_var2[i] = this->clusterMembers_var[i];
    clusterMembers_arraysize = size;
    delete [] this->clusterMembers_var;
    this->clusterMembers_var = clusterMembers_var2;
}

unsigned int SHeedRoutingPacket::getClusterMembersArraySize() const
{
    return clusterMembers_arraysize;
}

NDInf& SHeedRoutingPacket::getClusterMembers(unsigned int k)
{
    if (k>=clusterMembers_arraysize) throw cRuntimeError("Array of size %d indexed by %d", clusterMembers_arraysize, k);
    return clusterMembers_var[k];
}

void SHeedRoutingPacket::setClusterMembers(unsigned int k, const NDInf& clusterMembers)
{
    if (k>=clusterMembers_arraysize) throw cRuntimeError("Array of size %d indexed by %d", clusterMembers_arraysize, k);
    this->clusterMembers_var[k] = clusterMembers;
}

class SHeedRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    SHeedRoutingPacketDescriptor();
    virtual ~SHeedRoutingPacketDescriptor();

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

Register_ClassDescriptor(SHeedRoutingPacketDescriptor);

SHeedRoutingPacketDescriptor::SHeedRoutingPacketDescriptor() : cClassDescriptor("SHeedRoutingPacket", "RoutingPacket")
{
}

SHeedRoutingPacketDescriptor::~SHeedRoutingPacketDescriptor()
{
}

bool SHeedRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SHeedRoutingPacket *>(obj)!=NULL;
}

const char *SHeedRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SHeedRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int SHeedRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *SHeedRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "SHeedRoutingPacketKind",
        "cost",
        "eng",
        "status",
        "clusterMembers",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int SHeedRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SHeedRoutingPacketKind")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cost")==0) return base+1;
    if (fieldName[0]=='e' && strcmp(fieldName, "eng")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "clusterMembers")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SHeedRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "bool",
        "NDInf",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *SHeedRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "SHeedRoutingPacket_Type";
            return NULL;
        default: return NULL;
    }
}

int SHeedRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SHeedRoutingPacket *pp = (SHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 4: return pp->getClusterMembersArraySize();
        default: return 0;
    }
}

std::string SHeedRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SHeedRoutingPacket *pp = (SHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSHeedRoutingPacketKind());
        case 1: return long2string(pp->getCost());
        case 2: return double2string(pp->getEng());
        case 3: return bool2string(pp->getStatus());
        case 4: {std::stringstream out; out << pp->getClusterMembers(i); return out.str();}
        default: return "";
    }
}

bool SHeedRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SHeedRoutingPacket *pp = (SHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSHeedRoutingPacketKind(string2long(value)); return true;
        case 1: pp->setCost(string2long(value)); return true;
        case 2: pp->setEng(string2double(value)); return true;
        case 3: pp->setStatus(string2bool(value)); return true;
        default: return false;
    }
}

const char *SHeedRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(NDInf));
        default: return NULL;
    };
}

void *SHeedRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SHeedRoutingPacket *pp = (SHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getClusterMembers(i)); break;
        default: return NULL;
    }
}


