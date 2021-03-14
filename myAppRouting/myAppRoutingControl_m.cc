//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/myAppRouting/myAppRoutingControl.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "myAppRoutingControl_m.h"

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
    cEnum *e = cEnum::find("myAppRoutingControlDef");
    if (!e) enums.getInstance()->add(e = new cEnum("myAppRoutingControlDef"));
    e->insert(MPRINGS_NOT_CONNECTED, "MPRINGS_NOT_CONNECTED");
    e->insert(MPRINGS_CONNECTED_TO_TREE, "MPRINGS_CONNECTED_TO_TREE");
    e->insert(MPRINGS_TREE_LEVEL_UPDATED, "MPRINGS_TREE_LEVEL_UPDATED");
);

Register_Class(myAppRoutingControlMessage);

myAppRoutingControlMessage::myAppRoutingControlMessage(const char *name, int kind) : ::cMessage(name,kind)
{
    this->myAppRoutingControlMessageKind_var = 0;
    this->sinkID_var = 0;
    this->level_var = 0;
}

myAppRoutingControlMessage::myAppRoutingControlMessage(const myAppRoutingControlMessage& other) : ::cMessage(other)
{
    copy(other);
}

myAppRoutingControlMessage::~myAppRoutingControlMessage()
{
}

myAppRoutingControlMessage& myAppRoutingControlMessage::operator=(const myAppRoutingControlMessage& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void myAppRoutingControlMessage::copy(const myAppRoutingControlMessage& other)
{
    this->myAppRoutingControlMessageKind_var = other.myAppRoutingControlMessageKind_var;
    this->sinkID_var = other.sinkID_var;
    this->level_var = other.level_var;
}

void myAppRoutingControlMessage::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->myAppRoutingControlMessageKind_var);
    doPacking(b,this->sinkID_var);
    doPacking(b,this->level_var);
}

void myAppRoutingControlMessage::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->myAppRoutingControlMessageKind_var);
    doUnpacking(b,this->sinkID_var);
    doUnpacking(b,this->level_var);
}

int myAppRoutingControlMessage::getMyAppRoutingControlMessageKind() const
{
    return myAppRoutingControlMessageKind_var;
}

void myAppRoutingControlMessage::setMyAppRoutingControlMessageKind(int myAppRoutingControlMessageKind)
{
    this->myAppRoutingControlMessageKind_var = myAppRoutingControlMessageKind;
}

int myAppRoutingControlMessage::getSinkID() const
{
    return sinkID_var;
}

void myAppRoutingControlMessage::setSinkID(int sinkID)
{
    this->sinkID_var = sinkID;
}

int myAppRoutingControlMessage::getLevel() const
{
    return level_var;
}

void myAppRoutingControlMessage::setLevel(int level)
{
    this->level_var = level;
}

class myAppRoutingControlMessageDescriptor : public cClassDescriptor
{
  public:
    myAppRoutingControlMessageDescriptor();
    virtual ~myAppRoutingControlMessageDescriptor();

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

Register_ClassDescriptor(myAppRoutingControlMessageDescriptor);

myAppRoutingControlMessageDescriptor::myAppRoutingControlMessageDescriptor() : cClassDescriptor("myAppRoutingControlMessage", "cMessage")
{
}

myAppRoutingControlMessageDescriptor::~myAppRoutingControlMessageDescriptor()
{
}

bool myAppRoutingControlMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<myAppRoutingControlMessage *>(obj)!=NULL;
}

const char *myAppRoutingControlMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int myAppRoutingControlMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int myAppRoutingControlMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *myAppRoutingControlMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "myAppRoutingControlMessageKind",
        "sinkID",
        "level",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int myAppRoutingControlMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myAppRoutingControlMessageKind")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sinkID")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "level")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *myAppRoutingControlMessageDescriptor::getFieldTypeString(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *myAppRoutingControlMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "myAppRoutingControlDef";
            return NULL;
        default: return NULL;
    }
}

int myAppRoutingControlMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    myAppRoutingControlMessage *pp = (myAppRoutingControlMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string myAppRoutingControlMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    myAppRoutingControlMessage *pp = (myAppRoutingControlMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMyAppRoutingControlMessageKind());
        case 1: return long2string(pp->getSinkID());
        case 2: return long2string(pp->getLevel());
        default: return "";
    }
}

bool myAppRoutingControlMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    myAppRoutingControlMessage *pp = (myAppRoutingControlMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setMyAppRoutingControlMessageKind(string2long(value)); return true;
        case 1: pp->setSinkID(string2long(value)); return true;
        case 2: pp->setLevel(string2long(value)); return true;
        default: return false;
    }
}

const char *myAppRoutingControlMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *myAppRoutingControlMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    myAppRoutingControlMessage *pp = (myAppRoutingControlMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


