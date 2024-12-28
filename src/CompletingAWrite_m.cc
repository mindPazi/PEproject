//
// Generated file, do not edit! Created by opp_msgtool 6.1 from CompletingAWrite.msg.
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
#include "CompletingAWrite_m.h"

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

Register_Class(CompletingAWrite)

CompletingAWrite::CompletingAWrite(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

CompletingAWrite::CompletingAWrite(const CompletingAWrite& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

CompletingAWrite::~CompletingAWrite()
{
    delete [] this->chunkWriteTimes;
}

CompletingAWrite& CompletingAWrite::operator=(const CompletingAWrite& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void CompletingAWrite::copy(const CompletingAWrite& other)
{
    this->iteration = other.iteration;
    this->remainingBytesToWrite = other.remainingBytesToWrite;
    delete [] this->chunkWriteTimes;
    this->chunkWriteTimes = (other.chunkWriteTimes_arraysize==0) ? nullptr : new double[other.chunkWriteTimes_arraysize];
    chunkWriteTimes_arraysize = other.chunkWriteTimes_arraysize;
    for (size_t i = 0; i < chunkWriteTimes_arraysize; i++) {
        this->chunkWriteTimes[i] = other.chunkWriteTimes[i];
    }
}

void CompletingAWrite::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->iteration);
    doParsimPacking(b,this->remainingBytesToWrite);
    b->pack(chunkWriteTimes_arraysize);
    doParsimArrayPacking(b,this->chunkWriteTimes,chunkWriteTimes_arraysize);
}

void CompletingAWrite::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->iteration);
    doParsimUnpacking(b,this->remainingBytesToWrite);
    delete [] this->chunkWriteTimes;
    b->unpack(chunkWriteTimes_arraysize);
    if (chunkWriteTimes_arraysize == 0) {
        this->chunkWriteTimes = nullptr;
    } else {
        this->chunkWriteTimes = new double[chunkWriteTimes_arraysize];
        doParsimArrayUnpacking(b,this->chunkWriteTimes,chunkWriteTimes_arraysize);
    }
}

int CompletingAWrite::getIteration() const
{
    return this->iteration;
}

void CompletingAWrite::setIteration(int iteration)
{
    this->iteration = iteration;
}

int CompletingAWrite::getRemainingBytesToWrite() const
{
    return this->remainingBytesToWrite;
}

void CompletingAWrite::setRemainingBytesToWrite(int remainingBytesToWrite)
{
    this->remainingBytesToWrite = remainingBytesToWrite;
}

size_t CompletingAWrite::getChunkWriteTimesArraySize() const
{
    return chunkWriteTimes_arraysize;
}

double CompletingAWrite::getChunkWriteTimes(size_t k) const
{
    if (k >= chunkWriteTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)chunkWriteTimes_arraysize, (unsigned long)k);
    return this->chunkWriteTimes[k];
}

void CompletingAWrite::setChunkWriteTimesArraySize(size_t newSize)
{
    double *chunkWriteTimes2 = (newSize==0) ? nullptr : new double[newSize];
    size_t minSize = chunkWriteTimes_arraysize < newSize ? chunkWriteTimes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        chunkWriteTimes2[i] = this->chunkWriteTimes[i];
    for (size_t i = minSize; i < newSize; i++)
        chunkWriteTimes2[i] = 0;
    delete [] this->chunkWriteTimes;
    this->chunkWriteTimes = chunkWriteTimes2;
    chunkWriteTimes_arraysize = newSize;
}

void CompletingAWrite::setChunkWriteTimes(size_t k, double chunkWriteTimes)
{
    if (k >= chunkWriteTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)chunkWriteTimes_arraysize, (unsigned long)k);
    this->chunkWriteTimes[k] = chunkWriteTimes;
}

void CompletingAWrite::insertChunkWriteTimes(size_t k, double chunkWriteTimes)
{
    if (k > chunkWriteTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)chunkWriteTimes_arraysize, (unsigned long)k);
    size_t newSize = chunkWriteTimes_arraysize + 1;
    double *chunkWriteTimes2 = new double[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        chunkWriteTimes2[i] = this->chunkWriteTimes[i];
    chunkWriteTimes2[k] = chunkWriteTimes;
    for (i = k + 1; i < newSize; i++)
        chunkWriteTimes2[i] = this->chunkWriteTimes[i-1];
    delete [] this->chunkWriteTimes;
    this->chunkWriteTimes = chunkWriteTimes2;
    chunkWriteTimes_arraysize = newSize;
}

void CompletingAWrite::appendChunkWriteTimes(double chunkWriteTimes)
{
    insertChunkWriteTimes(chunkWriteTimes_arraysize, chunkWriteTimes);
}

void CompletingAWrite::eraseChunkWriteTimes(size_t k)
{
    if (k >= chunkWriteTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)chunkWriteTimes_arraysize, (unsigned long)k);
    size_t newSize = chunkWriteTimes_arraysize - 1;
    double *chunkWriteTimes2 = (newSize == 0) ? nullptr : new double[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        chunkWriteTimes2[i] = this->chunkWriteTimes[i];
    for (i = k; i < newSize; i++)
        chunkWriteTimes2[i] = this->chunkWriteTimes[i+1];
    delete [] this->chunkWriteTimes;
    this->chunkWriteTimes = chunkWriteTimes2;
    chunkWriteTimes_arraysize = newSize;
}

class CompletingAWriteDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_iteration,
        FIELD_remainingBytesToWrite,
        FIELD_chunkWriteTimes,
    };
  public:
    CompletingAWriteDescriptor();
    virtual ~CompletingAWriteDescriptor();

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

Register_ClassDescriptor(CompletingAWriteDescriptor)

CompletingAWriteDescriptor::CompletingAWriteDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(CompletingAWrite)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

CompletingAWriteDescriptor::~CompletingAWriteDescriptor()
{
    delete[] propertyNames;
}

bool CompletingAWriteDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CompletingAWrite *>(obj)!=nullptr;
}

const char **CompletingAWriteDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CompletingAWriteDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CompletingAWriteDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int CompletingAWriteDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_iteration
        FD_ISEDITABLE,    // FIELD_remainingBytesToWrite
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_chunkWriteTimes
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *CompletingAWriteDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "iteration",
        "remainingBytesToWrite",
        "chunkWriteTimes",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int CompletingAWriteDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "iteration") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "remainingBytesToWrite") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "chunkWriteTimes") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *CompletingAWriteDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_iteration
        "int",    // FIELD_remainingBytesToWrite
        "double",    // FIELD_chunkWriteTimes
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **CompletingAWriteDescriptor::getFieldPropertyNames(int field) const
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

const char *CompletingAWriteDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int CompletingAWriteDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CompletingAWrite *pp = omnetpp::fromAnyPtr<CompletingAWrite>(object); (void)pp;
    switch (field) {
        case FIELD_chunkWriteTimes: return pp->getChunkWriteTimesArraySize();
        default: return 0;
    }
}

void CompletingAWriteDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CompletingAWrite *pp = omnetpp::fromAnyPtr<CompletingAWrite>(object); (void)pp;
    switch (field) {
        case FIELD_chunkWriteTimes: pp->setChunkWriteTimesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CompletingAWrite'", field);
    }
}

const char *CompletingAWriteDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CompletingAWrite *pp = omnetpp::fromAnyPtr<CompletingAWrite>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CompletingAWriteDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CompletingAWrite *pp = omnetpp::fromAnyPtr<CompletingAWrite>(object); (void)pp;
    switch (field) {
        case FIELD_iteration: return long2string(pp->getIteration());
        case FIELD_remainingBytesToWrite: return long2string(pp->getRemainingBytesToWrite());
        case FIELD_chunkWriteTimes: return double2string(pp->getChunkWriteTimes(i));
        default: return "";
    }
}

void CompletingAWriteDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CompletingAWrite *pp = omnetpp::fromAnyPtr<CompletingAWrite>(object); (void)pp;
    switch (field) {
        case FIELD_iteration: pp->setIteration(string2long(value)); break;
        case FIELD_remainingBytesToWrite: pp->setRemainingBytesToWrite(string2long(value)); break;
        case FIELD_chunkWriteTimes: pp->setChunkWriteTimes(i,string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CompletingAWrite'", field);
    }
}

omnetpp::cValue CompletingAWriteDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CompletingAWrite *pp = omnetpp::fromAnyPtr<CompletingAWrite>(object); (void)pp;
    switch (field) {
        case FIELD_iteration: return pp->getIteration();
        case FIELD_remainingBytesToWrite: return pp->getRemainingBytesToWrite();
        case FIELD_chunkWriteTimes: return pp->getChunkWriteTimes(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CompletingAWrite' as cValue -- field index out of range?", field);
    }
}

void CompletingAWriteDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CompletingAWrite *pp = omnetpp::fromAnyPtr<CompletingAWrite>(object); (void)pp;
    switch (field) {
        case FIELD_iteration: pp->setIteration(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_remainingBytesToWrite: pp->setRemainingBytesToWrite(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_chunkWriteTimes: pp->setChunkWriteTimes(i,value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CompletingAWrite'", field);
    }
}

const char *CompletingAWriteDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CompletingAWriteDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CompletingAWrite *pp = omnetpp::fromAnyPtr<CompletingAWrite>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CompletingAWriteDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CompletingAWrite *pp = omnetpp::fromAnyPtr<CompletingAWrite>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CompletingAWrite'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

