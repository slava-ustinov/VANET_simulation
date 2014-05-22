//
// Generated file, do not edit! Created by opp_msgc 4.3 from messages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "messages_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(Control_msg);

Control_msg::Control_msg(const char *name, int kind) : cMessage(name,kind)
{
    this->CurrentXpos_var = 0;
    this->CurrentYpos_var = 0;
    this->SRVindex_var = 0;
    this->isBreaking_var = 0;
    this->isCrashed_var = 0;
    this->isCrazy_var = 0;
    this->RelocateToX_var = 0;
    this->RelocateToY_var = 0;
}

Control_msg::Control_msg(const Control_msg& other) : cMessage(other)
{
    copy(other);
}

Control_msg::~Control_msg()
{
}

Control_msg& Control_msg::operator=(const Control_msg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void Control_msg::copy(const Control_msg& other)
{
    this->CurrentXpos_var = other.CurrentXpos_var;
    this->CurrentYpos_var = other.CurrentYpos_var;
    this->SRVindex_var = other.SRVindex_var;
    this->isBreaking_var = other.isBreaking_var;
    this->isCrashed_var = other.isCrashed_var;
    this->isCrazy_var = other.isCrazy_var;
    this->RelocateToX_var = other.RelocateToX_var;
    this->RelocateToY_var = other.RelocateToY_var;
}

void Control_msg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->CurrentXpos_var);
    doPacking(b,this->CurrentYpos_var);
    doPacking(b,this->SRVindex_var);
    doPacking(b,this->isBreaking_var);
    doPacking(b,this->isCrashed_var);
    doPacking(b,this->isCrazy_var);
    doPacking(b,this->RelocateToX_var);
    doPacking(b,this->RelocateToY_var);
}

void Control_msg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->CurrentXpos_var);
    doUnpacking(b,this->CurrentYpos_var);
    doUnpacking(b,this->SRVindex_var);
    doUnpacking(b,this->isBreaking_var);
    doUnpacking(b,this->isCrashed_var);
    doUnpacking(b,this->isCrazy_var);
    doUnpacking(b,this->RelocateToX_var);
    doUnpacking(b,this->RelocateToY_var);
}

int Control_msg::getCurrentXpos() const
{
    return CurrentXpos_var;
}

void Control_msg::setCurrentXpos(int CurrentXpos)
{
    this->CurrentXpos_var = CurrentXpos;
}

int Control_msg::getCurrentYpos() const
{
    return CurrentYpos_var;
}

void Control_msg::setCurrentYpos(int CurrentYpos)
{
    this->CurrentYpos_var = CurrentYpos;
}

int Control_msg::getSRVindex() const
{
    return SRVindex_var;
}

void Control_msg::setSRVindex(int SRVindex)
{
    this->SRVindex_var = SRVindex;
}

bool Control_msg::getIsBreaking() const
{
    return isBreaking_var;
}

void Control_msg::setIsBreaking(bool isBreaking)
{
    this->isBreaking_var = isBreaking;
}

bool Control_msg::getIsCrashed() const
{
    return isCrashed_var;
}

void Control_msg::setIsCrashed(bool isCrashed)
{
    this->isCrashed_var = isCrashed;
}

bool Control_msg::getIsCrazy() const
{
    return isCrazy_var;
}

void Control_msg::setIsCrazy(bool isCrazy)
{
    this->isCrazy_var = isCrazy;
}

int Control_msg::getRelocateToX() const
{
    return RelocateToX_var;
}

void Control_msg::setRelocateToX(int RelocateToX)
{
    this->RelocateToX_var = RelocateToX;
}

int Control_msg::getRelocateToY() const
{
    return RelocateToY_var;
}

void Control_msg::setRelocateToY(int RelocateToY)
{
    this->RelocateToY_var = RelocateToY;
}

class Control_msgDescriptor : public cClassDescriptor
{
  public:
    Control_msgDescriptor();
    virtual ~Control_msgDescriptor();

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

Register_ClassDescriptor(Control_msgDescriptor);

Control_msgDescriptor::Control_msgDescriptor() : cClassDescriptor("Control_msg", "cMessage")
{
}

Control_msgDescriptor::~Control_msgDescriptor()
{
}

bool Control_msgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Control_msg *>(obj)!=NULL;
}

const char *Control_msgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Control_msgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int Control_msgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *Control_msgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "CurrentXpos",
        "CurrentYpos",
        "SRVindex",
        "isBreaking",
        "isCrashed",
        "isCrazy",
        "RelocateToX",
        "RelocateToY",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int Control_msgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CurrentXpos")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CurrentYpos")==0) return base+1;
    if (fieldName[0]=='S' && strcmp(fieldName, "SRVindex")==0) return base+2;
    if (fieldName[0]=='i' && strcmp(fieldName, "isBreaking")==0) return base+3;
    if (fieldName[0]=='i' && strcmp(fieldName, "isCrashed")==0) return base+4;
    if (fieldName[0]=='i' && strcmp(fieldName, "isCrazy")==0) return base+5;
    if (fieldName[0]=='R' && strcmp(fieldName, "RelocateToX")==0) return base+6;
    if (fieldName[0]=='R' && strcmp(fieldName, "RelocateToY")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Control_msgDescriptor::getFieldTypeString(void *object, int field) const
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
        "bool",
        "bool",
        "int",
        "int",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *Control_msgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int Control_msgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Control_msg *pp = (Control_msg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Control_msgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Control_msg *pp = (Control_msg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCurrentXpos());
        case 1: return long2string(pp->getCurrentYpos());
        case 2: return long2string(pp->getSRVindex());
        case 3: return bool2string(pp->getIsBreaking());
        case 4: return bool2string(pp->getIsCrashed());
        case 5: return bool2string(pp->getIsCrazy());
        case 6: return long2string(pp->getRelocateToX());
        case 7: return long2string(pp->getRelocateToY());
        default: return "";
    }
}

bool Control_msgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Control_msg *pp = (Control_msg *)object; (void)pp;
    switch (field) {
        case 0: pp->setCurrentXpos(string2long(value)); return true;
        case 1: pp->setCurrentYpos(string2long(value)); return true;
        case 2: pp->setSRVindex(string2long(value)); return true;
        case 3: pp->setIsBreaking(string2bool(value)); return true;
        case 4: pp->setIsCrashed(string2bool(value)); return true;
        case 5: pp->setIsCrazy(string2bool(value)); return true;
        case 6: pp->setRelocateToX(string2long(value)); return true;
        case 7: pp->setRelocateToY(string2long(value)); return true;
        default: return false;
    }
}

const char *Control_msgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<8) ? fieldStructNames[field] : NULL;
}

void *Control_msgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Control_msg *pp = (Control_msg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(WiMAX_SelfMsg);

WiMAX_SelfMsg::WiMAX_SelfMsg(const char *name, int kind) : cMessage(name,kind)
{
    this->isTimeOut_var = 0;
    this->isFLOOD_var = 0;
    this->QueueIndex_var = 0;
    this->Call_ID_var = 0;
    this->isFinishedFlooding_var = 0;
}

WiMAX_SelfMsg::WiMAX_SelfMsg(const WiMAX_SelfMsg& other) : cMessage(other)
{
    copy(other);
}

WiMAX_SelfMsg::~WiMAX_SelfMsg()
{
}

WiMAX_SelfMsg& WiMAX_SelfMsg::operator=(const WiMAX_SelfMsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void WiMAX_SelfMsg::copy(const WiMAX_SelfMsg& other)
{
    this->isTimeOut_var = other.isTimeOut_var;
    this->isFLOOD_var = other.isFLOOD_var;
    this->QueueIndex_var = other.QueueIndex_var;
    this->Call_ID_var = other.Call_ID_var;
    this->isFinishedFlooding_var = other.isFinishedFlooding_var;
}

void WiMAX_SelfMsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->isTimeOut_var);
    doPacking(b,this->isFLOOD_var);
    doPacking(b,this->QueueIndex_var);
    doPacking(b,this->Call_ID_var);
    doPacking(b,this->isFinishedFlooding_var);
}

void WiMAX_SelfMsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->isTimeOut_var);
    doUnpacking(b,this->isFLOOD_var);
    doUnpacking(b,this->QueueIndex_var);
    doUnpacking(b,this->Call_ID_var);
    doUnpacking(b,this->isFinishedFlooding_var);
}

bool WiMAX_SelfMsg::getIsTimeOut() const
{
    return isTimeOut_var;
}

void WiMAX_SelfMsg::setIsTimeOut(bool isTimeOut)
{
    this->isTimeOut_var = isTimeOut;
}

bool WiMAX_SelfMsg::getIsFLOOD() const
{
    return isFLOOD_var;
}

void WiMAX_SelfMsg::setIsFLOOD(bool isFLOOD)
{
    this->isFLOOD_var = isFLOOD;
}

int WiMAX_SelfMsg::getQueueIndex() const
{
    return QueueIndex_var;
}

void WiMAX_SelfMsg::setQueueIndex(int QueueIndex)
{
    this->QueueIndex_var = QueueIndex;
}

int WiMAX_SelfMsg::getCall_ID() const
{
    return Call_ID_var;
}

void WiMAX_SelfMsg::setCall_ID(int Call_ID)
{
    this->Call_ID_var = Call_ID;
}

bool WiMAX_SelfMsg::getIsFinishedFlooding() const
{
    return isFinishedFlooding_var;
}

void WiMAX_SelfMsg::setIsFinishedFlooding(bool isFinishedFlooding)
{
    this->isFinishedFlooding_var = isFinishedFlooding;
}

class WiMAX_SelfMsgDescriptor : public cClassDescriptor
{
  public:
    WiMAX_SelfMsgDescriptor();
    virtual ~WiMAX_SelfMsgDescriptor();

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

Register_ClassDescriptor(WiMAX_SelfMsgDescriptor);

WiMAX_SelfMsgDescriptor::WiMAX_SelfMsgDescriptor() : cClassDescriptor("WiMAX_SelfMsg", "cMessage")
{
}

WiMAX_SelfMsgDescriptor::~WiMAX_SelfMsgDescriptor()
{
}

bool WiMAX_SelfMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<WiMAX_SelfMsg *>(obj)!=NULL;
}

const char *WiMAX_SelfMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int WiMAX_SelfMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int WiMAX_SelfMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *WiMAX_SelfMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "isTimeOut",
        "isFLOOD",
        "QueueIndex",
        "Call_ID",
        "isFinishedFlooding",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int WiMAX_SelfMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isTimeOut")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isFLOOD")==0) return base+1;
    if (fieldName[0]=='Q' && strcmp(fieldName, "QueueIndex")==0) return base+2;
    if (fieldName[0]=='C' && strcmp(fieldName, "Call_ID")==0) return base+3;
    if (fieldName[0]=='i' && strcmp(fieldName, "isFinishedFlooding")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *WiMAX_SelfMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
        "int",
        "int",
        "bool",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *WiMAX_SelfMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int WiMAX_SelfMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    WiMAX_SelfMsg *pp = (WiMAX_SelfMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiMAX_SelfMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    WiMAX_SelfMsg *pp = (WiMAX_SelfMsg *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getIsTimeOut());
        case 1: return bool2string(pp->getIsFLOOD());
        case 2: return long2string(pp->getQueueIndex());
        case 3: return long2string(pp->getCall_ID());
        case 4: return bool2string(pp->getIsFinishedFlooding());
        default: return "";
    }
}

bool WiMAX_SelfMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    WiMAX_SelfMsg *pp = (WiMAX_SelfMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setIsTimeOut(string2bool(value)); return true;
        case 1: pp->setIsFLOOD(string2bool(value)); return true;
        case 2: pp->setQueueIndex(string2long(value)); return true;
        case 3: pp->setCall_ID(string2long(value)); return true;
        case 4: pp->setIsFinishedFlooding(string2bool(value)); return true;
        default: return false;
    }
}

const char *WiMAX_SelfMsgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
}

void *WiMAX_SelfMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    WiMAX_SelfMsg *pp = (WiMAX_SelfMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(InitMsg);

InitMsg::InitMsg(const char *name, int kind) : cMessage(name,kind)
{
    this->SourceName_var = 0;
    this->SrcXPos_var = 0;
    this->SrcYPos_var = 0;
}

InitMsg::InitMsg(const InitMsg& other) : cMessage(other)
{
    copy(other);
}

InitMsg::~InitMsg()
{
}

InitMsg& InitMsg::operator=(const InitMsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void InitMsg::copy(const InitMsg& other)
{
    this->SourceName_var = other.SourceName_var;
    this->SrcXPos_var = other.SrcXPos_var;
    this->SrcYPos_var = other.SrcYPos_var;
}

void InitMsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->SourceName_var);
    doPacking(b,this->SrcXPos_var);
    doPacking(b,this->SrcYPos_var);
}

void InitMsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->SourceName_var);
    doUnpacking(b,this->SrcXPos_var);
    doUnpacking(b,this->SrcYPos_var);
}

const char * InitMsg::getSourceName() const
{
    return SourceName_var.c_str();
}

void InitMsg::setSourceName(const char * SourceName)
{
    this->SourceName_var = SourceName;
}

int InitMsg::getSrcXPos() const
{
    return SrcXPos_var;
}

void InitMsg::setSrcXPos(int SrcXPos)
{
    this->SrcXPos_var = SrcXPos;
}

int InitMsg::getSrcYPos() const
{
    return SrcYPos_var;
}

void InitMsg::setSrcYPos(int SrcYPos)
{
    this->SrcYPos_var = SrcYPos;
}

class InitMsgDescriptor : public cClassDescriptor
{
  public:
    InitMsgDescriptor();
    virtual ~InitMsgDescriptor();

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

Register_ClassDescriptor(InitMsgDescriptor);

InitMsgDescriptor::InitMsgDescriptor() : cClassDescriptor("InitMsg", "cMessage")
{
}

InitMsgDescriptor::~InitMsgDescriptor()
{
}

bool InitMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<InitMsg *>(obj)!=NULL;
}

const char *InitMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int InitMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int InitMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *InitMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "SourceName",
        "SrcXPos",
        "SrcYPos",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int InitMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SourceName")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SrcXPos")==0) return base+1;
    if (fieldName[0]=='S' && strcmp(fieldName, "SrcYPos")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *InitMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *InitMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int InitMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    InitMsg *pp = (InitMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string InitMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    InitMsg *pp = (InitMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getSourceName());
        case 1: return long2string(pp->getSrcXPos());
        case 2: return long2string(pp->getSrcYPos());
        default: return "";
    }
}

bool InitMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    InitMsg *pp = (InitMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setSourceName((value)); return true;
        case 1: pp->setSrcXPos(string2long(value)); return true;
        case 2: pp->setSrcYPos(string2long(value)); return true;
        default: return false;
    }
}

const char *InitMsgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *InitMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    InitMsg *pp = (InitMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SIP);

SIP::SIP(const char *name, int kind) : cPacket(name,kind)
{
    this->command_var = 0;
    this->src_var = 0;
    this->dst_var = 0;
    this->HandlingSRVindex_var = 0;
    this->Xpos_var = 0;
    this->Ypos_var = 0;
    this->Call_ID_var = 0;
}

SIP::SIP(const SIP& other) : cPacket(other)
{
    copy(other);
}

SIP::~SIP()
{
}

SIP& SIP::operator=(const SIP& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void SIP::copy(const SIP& other)
{
    this->command_var = other.command_var;
    this->src_var = other.src_var;
    this->dst_var = other.dst_var;
    this->HandlingSRVindex_var = other.HandlingSRVindex_var;
    this->Xpos_var = other.Xpos_var;
    this->Ypos_var = other.Ypos_var;
    this->Call_ID_var = other.Call_ID_var;
}

void SIP::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->command_var);
    doPacking(b,this->src_var);
    doPacking(b,this->dst_var);
    doPacking(b,this->HandlingSRVindex_var);
    doPacking(b,this->Xpos_var);
    doPacking(b,this->Ypos_var);
    doPacking(b,this->Call_ID_var);
}

void SIP::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->command_var);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dst_var);
    doUnpacking(b,this->HandlingSRVindex_var);
    doUnpacking(b,this->Xpos_var);
    doUnpacking(b,this->Ypos_var);
    doUnpacking(b,this->Call_ID_var);
}

const char * SIP::getCommand() const
{
    return command_var.c_str();
}

void SIP::setCommand(const char * command)
{
    this->command_var = command;
}

const char * SIP::getSrc() const
{
    return src_var.c_str();
}

void SIP::setSrc(const char * src)
{
    this->src_var = src;
}

const char * SIP::getDst() const
{
    return dst_var.c_str();
}

void SIP::setDst(const char * dst)
{
    this->dst_var = dst;
}

int SIP::getHandlingSRVindex() const
{
    return HandlingSRVindex_var;
}

void SIP::setHandlingSRVindex(int HandlingSRVindex)
{
    this->HandlingSRVindex_var = HandlingSRVindex;
}

int SIP::getXpos() const
{
    return Xpos_var;
}

void SIP::setXpos(int Xpos)
{
    this->Xpos_var = Xpos;
}

int SIP::getYpos() const
{
    return Ypos_var;
}

void SIP::setYpos(int Ypos)
{
    this->Ypos_var = Ypos;
}

int SIP::getCall_ID() const
{
    return Call_ID_var;
}

void SIP::setCall_ID(int Call_ID)
{
    this->Call_ID_var = Call_ID;
}

class SIPDescriptor : public cClassDescriptor
{
  public:
    SIPDescriptor();
    virtual ~SIPDescriptor();

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

Register_ClassDescriptor(SIPDescriptor);

SIPDescriptor::SIPDescriptor() : cClassDescriptor("SIP", "cPacket")
{
}

SIPDescriptor::~SIPDescriptor()
{
}

bool SIPDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SIP *>(obj)!=NULL;
}

const char *SIPDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SIPDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int SIPDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *SIPDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "command",
        "src",
        "dst",
        "HandlingSRVindex",
        "Xpos",
        "Ypos",
        "Call_ID",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int SIPDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "command")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+2;
    if (fieldName[0]=='H' && strcmp(fieldName, "HandlingSRVindex")==0) return base+3;
    if (fieldName[0]=='X' && strcmp(fieldName, "Xpos")==0) return base+4;
    if (fieldName[0]=='Y' && strcmp(fieldName, "Ypos")==0) return base+5;
    if (fieldName[0]=='C' && strcmp(fieldName, "Call_ID")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SIPDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "string",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *SIPDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SIPDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SIP *pp = (SIP *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SIPDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SIP *pp = (SIP *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getCommand());
        case 1: return oppstring2string(pp->getSrc());
        case 2: return oppstring2string(pp->getDst());
        case 3: return long2string(pp->getHandlingSRVindex());
        case 4: return long2string(pp->getXpos());
        case 5: return long2string(pp->getYpos());
        case 6: return long2string(pp->getCall_ID());
        default: return "";
    }
}

bool SIPDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SIP *pp = (SIP *)object; (void)pp;
    switch (field) {
        case 0: pp->setCommand((value)); return true;
        case 1: pp->setSrc((value)); return true;
        case 2: pp->setDst((value)); return true;
        case 3: pp->setHandlingSRVindex(string2long(value)); return true;
        case 4: pp->setXpos(string2long(value)); return true;
        case 5: pp->setYpos(string2long(value)); return true;
        case 6: pp->setCall_ID(string2long(value)); return true;
        default: return false;
    }
}

const char *SIPDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<7) ? fieldStructNames[field] : NULL;
}

void *SIPDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SIP *pp = (SIP *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SIP_Self_msg);

SIP_Self_msg::SIP_Self_msg(const char *name, int kind) : cPacket(name,kind)
{
    this->isTimeForHello_var = 0;
    this->isTimeToRelocate_var = 0;
}

SIP_Self_msg::SIP_Self_msg(const SIP_Self_msg& other) : cPacket(other)
{
    copy(other);
}

SIP_Self_msg::~SIP_Self_msg()
{
}

SIP_Self_msg& SIP_Self_msg::operator=(const SIP_Self_msg& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void SIP_Self_msg::copy(const SIP_Self_msg& other)
{
    this->isTimeForHello_var = other.isTimeForHello_var;
    this->isTimeToRelocate_var = other.isTimeToRelocate_var;
}

void SIP_Self_msg::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->isTimeForHello_var);
    doPacking(b,this->isTimeToRelocate_var);
}

void SIP_Self_msg::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->isTimeForHello_var);
    doUnpacking(b,this->isTimeToRelocate_var);
}

bool SIP_Self_msg::getIsTimeForHello() const
{
    return isTimeForHello_var;
}

void SIP_Self_msg::setIsTimeForHello(bool isTimeForHello)
{
    this->isTimeForHello_var = isTimeForHello;
}

bool SIP_Self_msg::getIsTimeToRelocate() const
{
    return isTimeToRelocate_var;
}

void SIP_Self_msg::setIsTimeToRelocate(bool isTimeToRelocate)
{
    this->isTimeToRelocate_var = isTimeToRelocate;
}

class SIP_Self_msgDescriptor : public cClassDescriptor
{
  public:
    SIP_Self_msgDescriptor();
    virtual ~SIP_Self_msgDescriptor();

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

Register_ClassDescriptor(SIP_Self_msgDescriptor);

SIP_Self_msgDescriptor::SIP_Self_msgDescriptor() : cClassDescriptor("SIP_Self_msg", "cPacket")
{
}

SIP_Self_msgDescriptor::~SIP_Self_msgDescriptor()
{
}

bool SIP_Self_msgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SIP_Self_msg *>(obj)!=NULL;
}

const char *SIP_Self_msgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SIP_Self_msgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int SIP_Self_msgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *SIP_Self_msgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "isTimeForHello",
        "isTimeToRelocate",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int SIP_Self_msgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isTimeForHello")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isTimeToRelocate")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SIP_Self_msgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *SIP_Self_msgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SIP_Self_msgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SIP_Self_msg *pp = (SIP_Self_msg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SIP_Self_msgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SIP_Self_msg *pp = (SIP_Self_msg *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getIsTimeForHello());
        case 1: return bool2string(pp->getIsTimeToRelocate());
        default: return "";
    }
}

bool SIP_Self_msgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SIP_Self_msg *pp = (SIP_Self_msg *)object; (void)pp;
    switch (field) {
        case 0: pp->setIsTimeForHello(string2bool(value)); return true;
        case 1: pp->setIsTimeToRelocate(string2bool(value)); return true;
        default: return false;
    }
}

const char *SIP_Self_msgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *SIP_Self_msgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SIP_Self_msg *pp = (SIP_Self_msg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Wimax_Frame);

Wimax_Frame::Wimax_Frame(const char *name, int kind) : cPacket(name,kind)
{
    this->isFLOOD_var = 0;
    this->isCorrupted_var = 0;
    this->isACK_var = 0;
    this->Call_ID_var = 0;
    this->Xpos_var = 0;
    this->Ypos_var = 0;
    this->src_var = 0;
    this->dst_var = 0;
}

Wimax_Frame::Wimax_Frame(const Wimax_Frame& other) : cPacket(other)
{
    copy(other);
}

Wimax_Frame::~Wimax_Frame()
{
}

Wimax_Frame& Wimax_Frame::operator=(const Wimax_Frame& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Wimax_Frame::copy(const Wimax_Frame& other)
{
    this->isFLOOD_var = other.isFLOOD_var;
    this->isCorrupted_var = other.isCorrupted_var;
    this->isACK_var = other.isACK_var;
    this->Call_ID_var = other.Call_ID_var;
    this->Xpos_var = other.Xpos_var;
    this->Ypos_var = other.Ypos_var;
    this->src_var = other.src_var;
    this->dst_var = other.dst_var;
}

void Wimax_Frame::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->isFLOOD_var);
    doPacking(b,this->isCorrupted_var);
    doPacking(b,this->isACK_var);
    doPacking(b,this->Call_ID_var);
    doPacking(b,this->Xpos_var);
    doPacking(b,this->Ypos_var);
    doPacking(b,this->src_var);
    doPacking(b,this->dst_var);
}

void Wimax_Frame::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->isFLOOD_var);
    doUnpacking(b,this->isCorrupted_var);
    doUnpacking(b,this->isACK_var);
    doUnpacking(b,this->Call_ID_var);
    doUnpacking(b,this->Xpos_var);
    doUnpacking(b,this->Ypos_var);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dst_var);
}

bool Wimax_Frame::getIsFLOOD() const
{
    return isFLOOD_var;
}

void Wimax_Frame::setIsFLOOD(bool isFLOOD)
{
    this->isFLOOD_var = isFLOOD;
}

bool Wimax_Frame::getIsCorrupted() const
{
    return isCorrupted_var;
}

void Wimax_Frame::setIsCorrupted(bool isCorrupted)
{
    this->isCorrupted_var = isCorrupted;
}

bool Wimax_Frame::getIsACK() const
{
    return isACK_var;
}

void Wimax_Frame::setIsACK(bool isACK)
{
    this->isACK_var = isACK;
}

int Wimax_Frame::getCall_ID() const
{
    return Call_ID_var;
}

void Wimax_Frame::setCall_ID(int Call_ID)
{
    this->Call_ID_var = Call_ID;
}

int Wimax_Frame::getXpos() const
{
    return Xpos_var;
}

void Wimax_Frame::setXpos(int Xpos)
{
    this->Xpos_var = Xpos;
}

int Wimax_Frame::getYpos() const
{
    return Ypos_var;
}

void Wimax_Frame::setYpos(int Ypos)
{
    this->Ypos_var = Ypos;
}

const char * Wimax_Frame::getSrc() const
{
    return src_var.c_str();
}

void Wimax_Frame::setSrc(const char * src)
{
    this->src_var = src;
}

const char * Wimax_Frame::getDst() const
{
    return dst_var.c_str();
}

void Wimax_Frame::setDst(const char * dst)
{
    this->dst_var = dst;
}

class Wimax_FrameDescriptor : public cClassDescriptor
{
  public:
    Wimax_FrameDescriptor();
    virtual ~Wimax_FrameDescriptor();

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

Register_ClassDescriptor(Wimax_FrameDescriptor);

Wimax_FrameDescriptor::Wimax_FrameDescriptor() : cClassDescriptor("Wimax_Frame", "cPacket")
{
}

Wimax_FrameDescriptor::~Wimax_FrameDescriptor()
{
}

bool Wimax_FrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Wimax_Frame *>(obj)!=NULL;
}

const char *Wimax_FrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Wimax_FrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int Wimax_FrameDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *Wimax_FrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "isFLOOD",
        "isCorrupted",
        "isACK",
        "Call_ID",
        "Xpos",
        "Ypos",
        "src",
        "dst",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int Wimax_FrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isFLOOD")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isCorrupted")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "isACK")==0) return base+2;
    if (fieldName[0]=='C' && strcmp(fieldName, "Call_ID")==0) return base+3;
    if (fieldName[0]=='X' && strcmp(fieldName, "Xpos")==0) return base+4;
    if (fieldName[0]=='Y' && strcmp(fieldName, "Ypos")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Wimax_FrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
        "bool",
        "int",
        "int",
        "int",
        "string",
        "string",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *Wimax_FrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int Wimax_FrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Wimax_Frame *pp = (Wimax_Frame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Wimax_FrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Wimax_Frame *pp = (Wimax_Frame *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getIsFLOOD());
        case 1: return bool2string(pp->getIsCorrupted());
        case 2: return bool2string(pp->getIsACK());
        case 3: return long2string(pp->getCall_ID());
        case 4: return long2string(pp->getXpos());
        case 5: return long2string(pp->getYpos());
        case 6: return oppstring2string(pp->getSrc());
        case 7: return oppstring2string(pp->getDst());
        default: return "";
    }
}

bool Wimax_FrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Wimax_Frame *pp = (Wimax_Frame *)object; (void)pp;
    switch (field) {
        case 0: pp->setIsFLOOD(string2bool(value)); return true;
        case 1: pp->setIsCorrupted(string2bool(value)); return true;
        case 2: pp->setIsACK(string2bool(value)); return true;
        case 3: pp->setCall_ID(string2long(value)); return true;
        case 4: pp->setXpos(string2long(value)); return true;
        case 5: pp->setYpos(string2long(value)); return true;
        case 6: pp->setSrc((value)); return true;
        case 7: pp->setDst((value)); return true;
        default: return false;
    }
}

const char *Wimax_FrameDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<8) ? fieldStructNames[field] : NULL;
}

void *Wimax_FrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Wimax_Frame *pp = (Wimax_Frame *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Eth_Frame);

Eth_Frame::Eth_Frame(const char *name, int kind) : cPacket(name,kind)
{
    this->command_var = 0;
    this->Call_ID_var = 0;
    this->Xpos_var = 0;
    this->Ypos_var = 0;
    this->src_var = 0;
    this->dst_var = 0;
}

Eth_Frame::Eth_Frame(const Eth_Frame& other) : cPacket(other)
{
    copy(other);
}

Eth_Frame::~Eth_Frame()
{
}

Eth_Frame& Eth_Frame::operator=(const Eth_Frame& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Eth_Frame::copy(const Eth_Frame& other)
{
    this->command_var = other.command_var;
    this->Call_ID_var = other.Call_ID_var;
    this->Xpos_var = other.Xpos_var;
    this->Ypos_var = other.Ypos_var;
    this->src_var = other.src_var;
    this->dst_var = other.dst_var;
}

void Eth_Frame::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->command_var);
    doPacking(b,this->Call_ID_var);
    doPacking(b,this->Xpos_var);
    doPacking(b,this->Ypos_var);
    doPacking(b,this->src_var);
    doPacking(b,this->dst_var);
}

void Eth_Frame::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->command_var);
    doUnpacking(b,this->Call_ID_var);
    doUnpacking(b,this->Xpos_var);
    doUnpacking(b,this->Ypos_var);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dst_var);
}

const char * Eth_Frame::getCommand() const
{
    return command_var.c_str();
}

void Eth_Frame::setCommand(const char * command)
{
    this->command_var = command;
}

int Eth_Frame::getCall_ID() const
{
    return Call_ID_var;
}

void Eth_Frame::setCall_ID(int Call_ID)
{
    this->Call_ID_var = Call_ID;
}

int Eth_Frame::getXpos() const
{
    return Xpos_var;
}

void Eth_Frame::setXpos(int Xpos)
{
    this->Xpos_var = Xpos;
}

int Eth_Frame::getYpos() const
{
    return Ypos_var;
}

void Eth_Frame::setYpos(int Ypos)
{
    this->Ypos_var = Ypos;
}

const char * Eth_Frame::getSrc() const
{
    return src_var.c_str();
}

void Eth_Frame::setSrc(const char * src)
{
    this->src_var = src;
}

const char * Eth_Frame::getDst() const
{
    return dst_var.c_str();
}

void Eth_Frame::setDst(const char * dst)
{
    this->dst_var = dst;
}

class Eth_FrameDescriptor : public cClassDescriptor
{
  public:
    Eth_FrameDescriptor();
    virtual ~Eth_FrameDescriptor();

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

Register_ClassDescriptor(Eth_FrameDescriptor);

Eth_FrameDescriptor::Eth_FrameDescriptor() : cClassDescriptor("Eth_Frame", "cPacket")
{
}

Eth_FrameDescriptor::~Eth_FrameDescriptor()
{
}

bool Eth_FrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Eth_Frame *>(obj)!=NULL;
}

const char *Eth_FrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Eth_FrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int Eth_FrameDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *Eth_FrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "command",
        "Call_ID",
        "Xpos",
        "Ypos",
        "src",
        "dst",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int Eth_FrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "command")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "Call_ID")==0) return base+1;
    if (fieldName[0]=='X' && strcmp(fieldName, "Xpos")==0) return base+2;
    if (fieldName[0]=='Y' && strcmp(fieldName, "Ypos")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Eth_FrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "int",
        "int",
        "int",
        "string",
        "string",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *Eth_FrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int Eth_FrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Eth_Frame *pp = (Eth_Frame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Eth_FrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Eth_Frame *pp = (Eth_Frame *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getCommand());
        case 1: return long2string(pp->getCall_ID());
        case 2: return long2string(pp->getXpos());
        case 3: return long2string(pp->getYpos());
        case 4: return oppstring2string(pp->getSrc());
        case 5: return oppstring2string(pp->getDst());
        default: return "";
    }
}

bool Eth_FrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Eth_Frame *pp = (Eth_Frame *)object; (void)pp;
    switch (field) {
        case 0: pp->setCommand((value)); return true;
        case 1: pp->setCall_ID(string2long(value)); return true;
        case 2: pp->setXpos(string2long(value)); return true;
        case 3: pp->setYpos(string2long(value)); return true;
        case 4: pp->setSrc((value)); return true;
        case 5: pp->setDst((value)); return true;
        default: return false;
    }
}

const char *Eth_FrameDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<6) ? fieldStructNames[field] : NULL;
}

void *Eth_FrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Eth_Frame *pp = (Eth_Frame *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UDP_IP_Packet);

UDP_IP_Packet::UDP_IP_Packet(const char *name, int kind) : cPacket(name,kind)
{
    this->command_var = 0;
    this->src_var = 0;
    this->dst_var = 0;
    this->Call_ID_var = 0;
    this->Xpos_var = 0;
    this->Ypos_var = 0;
    this->HandlingSRVindex_var = 0;
}

UDP_IP_Packet::UDP_IP_Packet(const UDP_IP_Packet& other) : cPacket(other)
{
    copy(other);
}

UDP_IP_Packet::~UDP_IP_Packet()
{
}

UDP_IP_Packet& UDP_IP_Packet::operator=(const UDP_IP_Packet& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void UDP_IP_Packet::copy(const UDP_IP_Packet& other)
{
    this->command_var = other.command_var;
    this->src_var = other.src_var;
    this->dst_var = other.dst_var;
    this->Call_ID_var = other.Call_ID_var;
    this->Xpos_var = other.Xpos_var;
    this->Ypos_var = other.Ypos_var;
    this->HandlingSRVindex_var = other.HandlingSRVindex_var;
}

void UDP_IP_Packet::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->command_var);
    doPacking(b,this->src_var);
    doPacking(b,this->dst_var);
    doPacking(b,this->Call_ID_var);
    doPacking(b,this->Xpos_var);
    doPacking(b,this->Ypos_var);
    doPacking(b,this->HandlingSRVindex_var);
}

void UDP_IP_Packet::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->command_var);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dst_var);
    doUnpacking(b,this->Call_ID_var);
    doUnpacking(b,this->Xpos_var);
    doUnpacking(b,this->Ypos_var);
    doUnpacking(b,this->HandlingSRVindex_var);
}

const char * UDP_IP_Packet::getCommand() const
{
    return command_var.c_str();
}

void UDP_IP_Packet::setCommand(const char * command)
{
    this->command_var = command;
}

const char * UDP_IP_Packet::getSrc() const
{
    return src_var.c_str();
}

void UDP_IP_Packet::setSrc(const char * src)
{
    this->src_var = src;
}

const char * UDP_IP_Packet::getDst() const
{
    return dst_var.c_str();
}

void UDP_IP_Packet::setDst(const char * dst)
{
    this->dst_var = dst;
}

int UDP_IP_Packet::getCall_ID() const
{
    return Call_ID_var;
}

void UDP_IP_Packet::setCall_ID(int Call_ID)
{
    this->Call_ID_var = Call_ID;
}

int UDP_IP_Packet::getXpos() const
{
    return Xpos_var;
}

void UDP_IP_Packet::setXpos(int Xpos)
{
    this->Xpos_var = Xpos;
}

int UDP_IP_Packet::getYpos() const
{
    return Ypos_var;
}

void UDP_IP_Packet::setYpos(int Ypos)
{
    this->Ypos_var = Ypos;
}

int UDP_IP_Packet::getHandlingSRVindex() const
{
    return HandlingSRVindex_var;
}

void UDP_IP_Packet::setHandlingSRVindex(int HandlingSRVindex)
{
    this->HandlingSRVindex_var = HandlingSRVindex;
}

class UDP_IP_PacketDescriptor : public cClassDescriptor
{
  public:
    UDP_IP_PacketDescriptor();
    virtual ~UDP_IP_PacketDescriptor();

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

Register_ClassDescriptor(UDP_IP_PacketDescriptor);

UDP_IP_PacketDescriptor::UDP_IP_PacketDescriptor() : cClassDescriptor("UDP_IP_Packet", "cPacket")
{
}

UDP_IP_PacketDescriptor::~UDP_IP_PacketDescriptor()
{
}

bool UDP_IP_PacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<UDP_IP_Packet *>(obj)!=NULL;
}

const char *UDP_IP_PacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UDP_IP_PacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int UDP_IP_PacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *UDP_IP_PacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "command",
        "src",
        "dst",
        "Call_ID",
        "Xpos",
        "Ypos",
        "HandlingSRVindex",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int UDP_IP_PacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "command")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+2;
    if (fieldName[0]=='C' && strcmp(fieldName, "Call_ID")==0) return base+3;
    if (fieldName[0]=='X' && strcmp(fieldName, "Xpos")==0) return base+4;
    if (fieldName[0]=='Y' && strcmp(fieldName, "Ypos")==0) return base+5;
    if (fieldName[0]=='H' && strcmp(fieldName, "HandlingSRVindex")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *UDP_IP_PacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "string",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *UDP_IP_PacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int UDP_IP_PacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UDP_IP_Packet *pp = (UDP_IP_Packet *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string UDP_IP_PacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    UDP_IP_Packet *pp = (UDP_IP_Packet *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getCommand());
        case 1: return oppstring2string(pp->getSrc());
        case 2: return oppstring2string(pp->getDst());
        case 3: return long2string(pp->getCall_ID());
        case 4: return long2string(pp->getXpos());
        case 5: return long2string(pp->getYpos());
        case 6: return long2string(pp->getHandlingSRVindex());
        default: return "";
    }
}

bool UDP_IP_PacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UDP_IP_Packet *pp = (UDP_IP_Packet *)object; (void)pp;
    switch (field) {
        case 0: pp->setCommand((value)); return true;
        case 1: pp->setSrc((value)); return true;
        case 2: pp->setDst((value)); return true;
        case 3: pp->setCall_ID(string2long(value)); return true;
        case 4: pp->setXpos(string2long(value)); return true;
        case 5: pp->setYpos(string2long(value)); return true;
        case 6: pp->setHandlingSRVindex(string2long(value)); return true;
        default: return false;
    }
}

const char *UDP_IP_PacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<7) ? fieldStructNames[field] : NULL;
}

void *UDP_IP_PacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UDP_IP_Packet *pp = (UDP_IP_Packet *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


