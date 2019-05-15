//
// Generated file, do not edit! Created by opp_msgc 4.5 from src/node/communication/routing/mHeedRouting/MHeedRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "MHeedRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("MHeedRoutingPacket_Type");
    if (!e) enums.getInstance()->add(e = new cEnum("MHeedRoutingPacket_Type"));
    e->insert(MHEED_ROUTING_ADV_PACKET, "MHEED_ROUTING_ADV_PACKET");
    e->insert(MHEED_ROUTING_JOIN_PACKET, "MHEED_ROUTING_JOIN_PACKET");
    e->insert(MHEED_ROUTING_TDMA_PACKET, "MHEED_ROUTING_TDMA_PACKET");
    e->insert(MHEED_ROUTING_DATA_PACKET, "MHEED_ROUTING_DATA_PACKET");
    e->insert(MHEED_ROUTING_NIDV_PACKET, "MHEED_ROUTING_NIDV_PACKET");
);

NDInfo::NDInfo()
{
    src = 0;
    eng = 0;
}

void doPacking(cCommBuffer *b, NDInfo& a)
{
    doPacking(b,a.src);
    doPacking(b,a.eng);
}

void doUnpacking(cCommBuffer *b, NDInfo& a)
{
    doUnpacking(b,a.src);
    doUnpacking(b,a.eng);
}

class NDInfoDescriptor : public cClassDescriptor
{
  public:
    NDInfoDescriptor();
    virtual ~NDInfoDescriptor();

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

Register_ClassDescriptor(NDInfoDescriptor);

NDInfoDescriptor::NDInfoDescriptor() : cClassDescriptor("NDInfo", "")
{
}

NDInfoDescriptor::~NDInfoDescriptor()
{
}

bool NDInfoDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NDInfo *>(obj)!=NULL;
}

const char *NDInfoDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NDInfoDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int NDInfoDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NDInfoDescriptor::getFieldName(void *object, int field) const
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

int NDInfoDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='e' && strcmp(fieldName, "eng")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NDInfoDescriptor::getFieldTypeString(void *object, int field) const
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

const char *NDInfoDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NDInfoDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NDInfo *pp = (NDInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NDInfoDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NDInfo *pp = (NDInfo *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->src);
        case 1: return double2string(pp->eng);
        default: return "";
    }
}

bool NDInfoDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NDInfo *pp = (NDInfo *)object; (void)pp;
    switch (field) {
        case 0: pp->src = string2long(value); return true;
        case 1: pp->eng = string2double(value); return true;
        default: return false;
    }
}

const char *NDInfoDescriptor::getFieldStructName(void *object, int field) const
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

void *NDInfoDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NDInfo *pp = (NDInfo *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(MHeedRoutingPacket);

MHeedRoutingPacket::MHeedRoutingPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->MHeedRoutingPacketKind_var = 0;
    this->cost_var = 0;
    this->eng_var = 0;
    this->status_var = 0;
    clusterMembers_arraysize = 0;
    this->clusterMembers_var = 0;
}

MHeedRoutingPacket::MHeedRoutingPacket(const MHeedRoutingPacket& other) : ::RoutingPacket(other)
{
    clusterMembers_arraysize = 0;
    this->clusterMembers_var = 0;
    copy(other);
}

MHeedRoutingPacket::~MHeedRoutingPacket()
{
    delete [] clusterMembers_var;
}

MHeedRoutingPacket& MHeedRoutingPacket::operator=(const MHeedRoutingPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void MHeedRoutingPacket::copy(const MHeedRoutingPacket& other)
{
    this->MHeedRoutingPacketKind_var = other.MHeedRoutingPacketKind_var;
    this->cost_var = other.cost_var;
    this->eng_var = other.eng_var;
    this->status_var = other.status_var;
    delete [] this->clusterMembers_var;
    this->clusterMembers_var = (other.clusterMembers_arraysize==0) ? NULL : new NDInfo[other.clusterMembers_arraysize];
    clusterMembers_arraysize = other.clusterMembers_arraysize;
    for (unsigned int i=0; i<clusterMembers_arraysize; i++)
        this->clusterMembers_var[i] = other.clusterMembers_var[i];
}

void MHeedRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->MHeedRoutingPacketKind_var);
    doPacking(b,this->cost_var);
    doPacking(b,this->eng_var);
    doPacking(b,this->status_var);
    b->pack(clusterMembers_arraysize);
    doPacking(b,this->clusterMembers_var,clusterMembers_arraysize);
}

void MHeedRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->MHeedRoutingPacketKind_var);
    doUnpacking(b,this->cost_var);
    doUnpacking(b,this->eng_var);
    doUnpacking(b,this->status_var);
    delete [] this->clusterMembers_var;
    b->unpack(clusterMembers_arraysize);
    if (clusterMembers_arraysize==0) {
        this->clusterMembers_var = 0;
    } else {
        this->clusterMembers_var = new NDInfo[clusterMembers_arraysize];
        doUnpacking(b,this->clusterMembers_var,clusterMembers_arraysize);
    }
}

int MHeedRoutingPacket::getMHeedRoutingPacketKind() const
{
    return MHeedRoutingPacketKind_var;
}

void MHeedRoutingPacket::setMHeedRoutingPacketKind(int MHeedRoutingPacketKind)
{
    this->MHeedRoutingPacketKind_var = MHeedRoutingPacketKind;
}

int MHeedRoutingPacket::getCost() const
{
    return cost_var;
}

void MHeedRoutingPacket::setCost(int cost)
{
    this->cost_var = cost;
}

double MHeedRoutingPacket::getEng() const
{
    return eng_var;
}

void MHeedRoutingPacket::setEng(double eng)
{
    this->eng_var = eng;
}

bool MHeedRoutingPacket::getStatus() const
{
    return status_var;
}

void MHeedRoutingPacket::setStatus(bool status)
{
    this->status_var = status;
}

void MHeedRoutingPacket::setClusterMembersArraySize(unsigned int size)
{
    NDInfo *clusterMembers_var2 = (size==0) ? NULL : new NDInfo[size];
    unsigned int sz = clusterMembers_arraysize < size ? clusterMembers_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        clusterMembers_var2[i] = this->clusterMembers_var[i];
    clusterMembers_arraysize = size;
    delete [] this->clusterMembers_var;
    this->clusterMembers_var = clusterMembers_var2;
}

unsigned int MHeedRoutingPacket::getClusterMembersArraySize() const
{
    return clusterMembers_arraysize;
}

NDInfo& MHeedRoutingPacket::getClusterMembers(unsigned int k)
{
    if (k>=clusterMembers_arraysize) throw cRuntimeError("Array of size %d indexed by %d", clusterMembers_arraysize, k);
    return clusterMembers_var[k];
}

void MHeedRoutingPacket::setClusterMembers(unsigned int k, const NDInfo& clusterMembers)
{
    if (k>=clusterMembers_arraysize) throw cRuntimeError("Array of size %d indexed by %d", clusterMembers_arraysize, k);
    this->clusterMembers_var[k] = clusterMembers;
}

class MHeedRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    MHeedRoutingPacketDescriptor();
    virtual ~MHeedRoutingPacketDescriptor();

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

Register_ClassDescriptor(MHeedRoutingPacketDescriptor);

MHeedRoutingPacketDescriptor::MHeedRoutingPacketDescriptor() : cClassDescriptor("MHeedRoutingPacket", "RoutingPacket")
{
}

MHeedRoutingPacketDescriptor::~MHeedRoutingPacketDescriptor()
{
}

bool MHeedRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<MHeedRoutingPacket *>(obj)!=NULL;
}

const char *MHeedRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int MHeedRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int MHeedRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *MHeedRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "MHeedRoutingPacketKind",
        "cost",
        "eng",
        "status",
        "clusterMembers",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int MHeedRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='M' && strcmp(fieldName, "MHeedRoutingPacketKind")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cost")==0) return base+1;
    if (fieldName[0]=='e' && strcmp(fieldName, "eng")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "clusterMembers")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *MHeedRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "NDInfo",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *MHeedRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "MHeedRoutingPacket_Type";
            return NULL;
        default: return NULL;
    }
}

int MHeedRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    MHeedRoutingPacket *pp = (MHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 4: return pp->getClusterMembersArraySize();
        default: return 0;
    }
}

std::string MHeedRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    MHeedRoutingPacket *pp = (MHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMHeedRoutingPacketKind());
        case 1: return long2string(pp->getCost());
        case 2: return double2string(pp->getEng());
        case 3: return bool2string(pp->getStatus());
        case 4: {std::stringstream out; out << pp->getClusterMembers(i); return out.str();}
        default: return "";
    }
}

bool MHeedRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    MHeedRoutingPacket *pp = (MHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setMHeedRoutingPacketKind(string2long(value)); return true;
        case 1: pp->setCost(string2long(value)); return true;
        case 2: pp->setEng(string2double(value)); return true;
        case 3: pp->setStatus(string2bool(value)); return true;
        default: return false;
    }
}

const char *MHeedRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(NDInfo));
        default: return NULL;
    };
}

void *MHeedRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    MHeedRoutingPacket *pp = (MHeedRoutingPacket *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getClusterMembers(i)); break;
        default: return NULL;
    }
}


