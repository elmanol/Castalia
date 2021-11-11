//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/eamultipathRingsRouting/EAmultipathRingsRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "EAmultipathRingsRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("eamultipathRingsRoutingPacketDef");
    if (!e) enums.getInstance()->add(e = new cEnum("eamultipathRingsRoutingPacketDef"));
    e->insert(MPRINGS_DATA_PACKET, "MPRINGS_DATA_PACKET");
    e->insert(MPRINGS_TOPOLOGY_SETUP_PACKET, "MPRINGS_TOPOLOGY_SETUP_PACKET");
    e->insert(MPRINGS_ENERGY_PACKET, "MPRINGS_ENERGY_PACKET");
);

Register_Class(EAmultipathRingsRoutingPacket);

EAmultipathRingsRoutingPacket::EAmultipathRingsRoutingPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->eamultipathRingsRoutingPacketKind_var = 0;
    this->sinkID_var = 0;
    this->senderLevel_var = 0;
    this->energyLevel_var = 0;
    this->harvestingRate_var = 0;
    this->kidsStatus_var = 0;
    this->myX_var = 0;
    this->myY_var = 0;
}

EAmultipathRingsRoutingPacket::EAmultipathRingsRoutingPacket(const EAmultipathRingsRoutingPacket& other) : ::RoutingPacket(other)
{
    copy(other);
}

EAmultipathRingsRoutingPacket::~EAmultipathRingsRoutingPacket()
{
}

EAmultipathRingsRoutingPacket& EAmultipathRingsRoutingPacket::operator=(const EAmultipathRingsRoutingPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void EAmultipathRingsRoutingPacket::copy(const EAmultipathRingsRoutingPacket& other)
{
    this->eamultipathRingsRoutingPacketKind_var = other.eamultipathRingsRoutingPacketKind_var;
    this->sinkID_var = other.sinkID_var;
    this->senderLevel_var = other.senderLevel_var;
    this->energyLevel_var = other.energyLevel_var;
    this->harvestingRate_var = other.harvestingRate_var;
    this->kidsStatus_var = other.kidsStatus_var;
    this->myX_var = other.myX_var;
    this->myY_var = other.myY_var;
}

void EAmultipathRingsRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->eamultipathRingsRoutingPacketKind_var);
    doPacking(b,this->sinkID_var);
    doPacking(b,this->senderLevel_var);
    doPacking(b,this->energyLevel_var);
    doPacking(b,this->harvestingRate_var);
    doPacking(b,this->kidsStatus_var);
    doPacking(b,this->myX_var);
    doPacking(b,this->myY_var);
}

void EAmultipathRingsRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->eamultipathRingsRoutingPacketKind_var);
    doUnpacking(b,this->sinkID_var);
    doUnpacking(b,this->senderLevel_var);
    doUnpacking(b,this->energyLevel_var);
    doUnpacking(b,this->harvestingRate_var);
    doUnpacking(b,this->kidsStatus_var);
    doUnpacking(b,this->myX_var);
    doUnpacking(b,this->myY_var);
}

int EAmultipathRingsRoutingPacket::getEamultipathRingsRoutingPacketKind() const
{
    return eamultipathRingsRoutingPacketKind_var;
}

void EAmultipathRingsRoutingPacket::setEamultipathRingsRoutingPacketKind(int eamultipathRingsRoutingPacketKind)
{
    this->eamultipathRingsRoutingPacketKind_var = eamultipathRingsRoutingPacketKind;
}

int EAmultipathRingsRoutingPacket::getSinkID() const
{
    return sinkID_var;
}

void EAmultipathRingsRoutingPacket::setSinkID(int sinkID)
{
    this->sinkID_var = sinkID;
}

int EAmultipathRingsRoutingPacket::getSenderLevel() const
{
    return senderLevel_var;
}

void EAmultipathRingsRoutingPacket::setSenderLevel(int senderLevel)
{
    this->senderLevel_var = senderLevel;
}

float EAmultipathRingsRoutingPacket::getEnergyLevel() const
{
    return energyLevel_var;
}

void EAmultipathRingsRoutingPacket::setEnergyLevel(float energyLevel)
{
    this->energyLevel_var = energyLevel;
}

float EAmultipathRingsRoutingPacket::getHarvestingRate() const
{
    return harvestingRate_var;
}

void EAmultipathRingsRoutingPacket::setHarvestingRate(float harvestingRate)
{
    this->harvestingRate_var = harvestingRate;
}

float EAmultipathRingsRoutingPacket::getKidsStatus() const
{
    return kidsStatus_var;
}

void EAmultipathRingsRoutingPacket::setKidsStatus(float kidsStatus)
{
    this->kidsStatus_var = kidsStatus;
}

int EAmultipathRingsRoutingPacket::getMyX() const
{
    return myX_var;
}

void EAmultipathRingsRoutingPacket::setMyX(int myX)
{
    this->myX_var = myX;
}

int EAmultipathRingsRoutingPacket::getMyY() const
{
    return myY_var;
}

void EAmultipathRingsRoutingPacket::setMyY(int myY)
{
    this->myY_var = myY;
}

class EAmultipathRingsRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    EAmultipathRingsRoutingPacketDescriptor();
    virtual ~EAmultipathRingsRoutingPacketDescriptor();

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

Register_ClassDescriptor(EAmultipathRingsRoutingPacketDescriptor);

EAmultipathRingsRoutingPacketDescriptor::EAmultipathRingsRoutingPacketDescriptor() : cClassDescriptor("EAmultipathRingsRoutingPacket", "RoutingPacket")
{
}

EAmultipathRingsRoutingPacketDescriptor::~EAmultipathRingsRoutingPacketDescriptor()
{
}

bool EAmultipathRingsRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<EAmultipathRingsRoutingPacket *>(obj)!=NULL;
}

const char *EAmultipathRingsRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int EAmultipathRingsRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int EAmultipathRingsRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *EAmultipathRingsRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "eamultipathRingsRoutingPacketKind",
        "sinkID",
        "senderLevel",
        "energyLevel",
        "harvestingRate",
        "kidsStatus",
        "myX",
        "myY",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int EAmultipathRingsRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "eamultipathRingsRoutingPacketKind")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sinkID")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderLevel")==0) return base+2;
    if (fieldName[0]=='e' && strcmp(fieldName, "energyLevel")==0) return base+3;
    if (fieldName[0]=='h' && strcmp(fieldName, "harvestingRate")==0) return base+4;
    if (fieldName[0]=='k' && strcmp(fieldName, "kidsStatus")==0) return base+5;
    if (fieldName[0]=='m' && strcmp(fieldName, "myX")==0) return base+6;
    if (fieldName[0]=='m' && strcmp(fieldName, "myY")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *EAmultipathRingsRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "float",
        "float",
        "float",
        "int",
        "int",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *EAmultipathRingsRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "eamultipathRingsRoutingPacketDef";
            return NULL;
        default: return NULL;
    }
}

int EAmultipathRingsRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    EAmultipathRingsRoutingPacket *pp = (EAmultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string EAmultipathRingsRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    EAmultipathRingsRoutingPacket *pp = (EAmultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getEamultipathRingsRoutingPacketKind());
        case 1: return long2string(pp->getSinkID());
        case 2: return long2string(pp->getSenderLevel());
        case 3: return double2string(pp->getEnergyLevel());
        case 4: return double2string(pp->getHarvestingRate());
        case 5: return double2string(pp->getKidsStatus());
        case 6: return long2string(pp->getMyX());
        case 7: return long2string(pp->getMyY());
        default: return "";
    }
}

bool EAmultipathRingsRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    EAmultipathRingsRoutingPacket *pp = (EAmultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setEamultipathRingsRoutingPacketKind(string2long(value)); return true;
        case 1: pp->setSinkID(string2long(value)); return true;
        case 2: pp->setSenderLevel(string2long(value)); return true;
        case 3: pp->setEnergyLevel(string2double(value)); return true;
        case 4: pp->setHarvestingRate(string2double(value)); return true;
        case 5: pp->setKidsStatus(string2double(value)); return true;
        case 6: pp->setMyX(string2long(value)); return true;
        case 7: pp->setMyY(string2long(value)); return true;
        default: return false;
    }
}

const char *EAmultipathRingsRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *EAmultipathRingsRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    EAmultipathRingsRoutingPacket *pp = (EAmultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


