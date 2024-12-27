//
// Generated file, do not edit! Created by opp_msgtool 6.1 from WriteRequest.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "WriteRequest_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(WriteRequest)

WriteRequest::WriteRequest(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

WriteRequest::WriteRequest(const WriteRequest& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WriteRequest::~WriteRequest()
{
    delete [] this->arrayField1;
}

WriteRequest& WriteRequest::operator=(const WriteRequest& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WriteRequest::copy(const WriteRequest& other)
{
    this->someField = other.someField;
    this->anotherField = other.anotherField;
    delete [] this->arrayField1;
    this->arrayField1 = (other.arrayField1_arraysize==0) ? nullptr : new double[other.arrayField1_arraysize];
    arrayField1_arraysize = other.arrayField1_arraysize;
    for (size_t i = 0; i < arrayField1_arraysize; i++) {
        this->arrayField1[i] = other.arrayField1[i];
    }
    for (size_t i = 0; i < 10; i++) {
        this->arrayField2[i] = other.arrayField2[i];
    }
}

void WriteRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->someField);
    doParsimPacking(b,this->anotherField);
    b->pack(arrayField1_arraysize);
    doParsimArrayPacking(b,this->arrayField1,arrayField1_arraysize);
    doParsimArrayPacking(b,this->arrayField2,10);
}

void WriteRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->someField);
    doParsimUnpacking(b,this->anotherField);
    delete [] this->arrayField1;
    b->unpack(arrayField1_arraysize);
    if (arrayField1_arraysize == 0) {
        this->arrayField1 = nullptr;
    } else {
        this->arrayField1 = new double[arrayField1_arraysize];
        doParsimArrayUnpacking(b,this->arrayField1,arrayField1_arraysize);
    }
    doParsimArrayUnpacking(b,this->arrayField2,10);
}

int WriteRequest::getSomeField() const
{
    return this->someField;
}

void WriteRequest::setSomeField(int someField)
{
    this->someField = someField;
}

const char * WriteRequest::getAnotherField() const
{
    return this->anotherField.c_str();
}

void WriteRequest::setAnotherField(const char * anotherField)
{
    this->anotherField = anotherField;
}

size_t WriteRequest::getArrayField1ArraySize() const
{
    return arrayField1_arraysize;
}

double WriteRequest::getArrayField1(size_t k) const
{
    if (k >= arrayField1_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)arrayField1_arraysize, (unsigned long)k);
    return this->arrayField1[k];
}

void WriteRequest::setArrayField1ArraySize(size_t newSize)
{
    double *arrayField12 = (newSize==0) ? nullptr : new double[newSize];
    size_t minSize = arrayField1_arraysize < newSize ? arrayField1_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        arrayField12[i] = this->arrayField1[i];
    for (size_t i = minSize; i < newSize; i++)
        arrayField12[i] = 0;
    delete [] this->arrayField1;
    this->arrayField1 = arrayField12;
    arrayField1_arraysize = newSize;
}

void WriteRequest::setArrayField1(size_t k, double arrayField1)
{
    if (k >= arrayField1_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)arrayField1_arraysize, (unsigned long)k);
    this->arrayField1[k] = arrayField1;
}

void WriteRequest::insertArrayField1(size_t k, double arrayField1)
{
    if (k > arrayField1_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)arrayField1_arraysize, (unsigned long)k);
    size_t newSize = arrayField1_arraysize + 1;
    double *arrayField12 = new double[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        arrayField12[i] = this->arrayField1[i];
    arrayField12[k] = arrayField1;
    for (i = k + 1; i < newSize; i++)
        arrayField12[i] = this->arrayField1[i-1];
    delete [] this->arrayField1;
    this->arrayField1 = arrayField12;
    arrayField1_arraysize = newSize;
}

void WriteRequest::appendArrayField1(double arrayField1)
{
    insertArrayField1(arrayField1_arraysize, arrayField1);
}

void WriteRequest::eraseArrayField1(size_t k)
{
    if (k >= arrayField1_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)arrayField1_arraysize, (unsigned long)k);
    size_t newSize = arrayField1_arraysize - 1;
    double *arrayField12 = (newSize == 0) ? nullptr : new double[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        arrayField12[i] = this->arrayField1[i];
    for (i = k; i < newSize; i++)
        arrayField12[i] = this->arrayField1[i+1];
    delete [] this->arrayField1;
    this->arrayField1 = arrayField12;
    arrayField1_arraysize = newSize;
}

size_t WriteRequest::getArrayField2ArraySize() const
{
    return 10;
}

double WriteRequest::getArrayField2(size_t k) const
{
    if (k >= 10) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)10, (unsigned long)k);
    return this->arrayField2[k];
}

void WriteRequest::setArrayField2(size_t k, double arrayField2)
{
    if (k >= 10) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)10, (unsigned long)k);
    this->arrayField2[k] = arrayField2;
}

class WriteRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_someField,
        FIELD_anotherField,
        FIELD_arrayField1,
        FIELD_arrayField2,
    };
  public:
    WriteRequestDescriptor();
    virtual ~WriteRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(WriteRequestDescriptor)

WriteRequestDescriptor::WriteRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(WriteRequest)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

WriteRequestDescriptor::~WriteRequestDescriptor()
{
    delete[] propertyNames;
}

bool WriteRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WriteRequest *>(obj)!=nullptr;
}

const char **WriteRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *WriteRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int WriteRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int WriteRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_someField
        FD_ISEDITABLE,    // FIELD_anotherField
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_arrayField1
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_arrayField2
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *WriteRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "someField",
        "anotherField",
        "arrayField1",
        "arrayField2",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int WriteRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "someField") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "anotherField") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "arrayField1") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "arrayField2") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *WriteRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_someField
        "string",    // FIELD_anotherField
        "double",    // FIELD_arrayField1
        "double",    // FIELD_arrayField2
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **WriteRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WriteRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WriteRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    WriteRequest *pp = omnetpp::fromAnyPtr<WriteRequest>(object); (void)pp;
    switch (field) {
        case FIELD_arrayField1: return pp->getArrayField1ArraySize();
        case FIELD_arrayField2: return 10;
        default: return 0;
    }
}

void WriteRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    WriteRequest *pp = omnetpp::fromAnyPtr<WriteRequest>(object); (void)pp;
    switch (field) {
        case FIELD_arrayField1: pp->setArrayField1ArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'WriteRequest'", field);
    }
}

const char *WriteRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    WriteRequest *pp = omnetpp::fromAnyPtr<WriteRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WriteRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    WriteRequest *pp = omnetpp::fromAnyPtr<WriteRequest>(object); (void)pp;
    switch (field) {
        case FIELD_someField: return long2string(pp->getSomeField());
        case FIELD_anotherField: return oppstring2string(pp->getAnotherField());
        case FIELD_arrayField1: return double2string(pp->getArrayField1(i));
        case FIELD_arrayField2: return double2string(pp->getArrayField2(i));
        default: return "";
    }
}

void WriteRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    WriteRequest *pp = omnetpp::fromAnyPtr<WriteRequest>(object); (void)pp;
    switch (field) {
        case FIELD_someField: pp->setSomeField(string2long(value)); break;
        case FIELD_anotherField: pp->setAnotherField((value)); break;
        case FIELD_arrayField1: pp->setArrayField1(i,string2double(value)); break;
        case FIELD_arrayField2: pp->setArrayField2(i,string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WriteRequest'", field);
    }
}

omnetpp::cValue WriteRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    WriteRequest *pp = omnetpp::fromAnyPtr<WriteRequest>(object); (void)pp;
    switch (field) {
        case FIELD_someField: return pp->getSomeField();
        case FIELD_anotherField: return pp->getAnotherField();
        case FIELD_arrayField1: return pp->getArrayField1(i);
        case FIELD_arrayField2: return pp->getArrayField2(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'WriteRequest' as cValue -- field index out of range?", field);
    }
}

void WriteRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    WriteRequest *pp = omnetpp::fromAnyPtr<WriteRequest>(object); (void)pp;
    switch (field) {
        case FIELD_someField: pp->setSomeField(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_anotherField: pp->setAnotherField(value.stringValue()); break;
        case FIELD_arrayField1: pp->setArrayField1(i,value.doubleValue()); break;
        case FIELD_arrayField2: pp->setArrayField2(i,value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WriteRequest'", field);
    }
}

const char *WriteRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr WriteRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    WriteRequest *pp = omnetpp::fromAnyPtr<WriteRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void WriteRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    WriteRequest *pp = omnetpp::fromAnyPtr<WriteRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WriteRequest'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

