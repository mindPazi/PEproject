//
// Generated file, do not edit! Created by opp_msgtool 6.1 from WriteCompleted.msg.
//

#ifndef __WRITECOMPLETED_M_H
#define __WRITECOMPLETED_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0601
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class WriteCompleted;
/**
 * Class generated from <tt>WriteCompleted.msg:19</tt> by opp_msgtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * message WriteCompleted
 * {
 *     double writeTime;
 * }
 * </pre>
 */
class WriteCompleted : public ::omnetpp::cMessage
{
  protected:
    double writeTime = 0;

  private:
    void copy(const WriteCompleted& other);

  protected:
    bool operator==(const WriteCompleted&) = delete;

  public:
    WriteCompleted(const char *name=nullptr, short kind=0);
    WriteCompleted(const WriteCompleted& other);
    virtual ~WriteCompleted();
    WriteCompleted& operator=(const WriteCompleted& other);
    virtual WriteCompleted *dup() const override {return new WriteCompleted(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual double getWriteTime() const;
    virtual void setWriteTime(double writeTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const WriteCompleted& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, WriteCompleted& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline WriteCompleted *fromAnyPtr(any_ptr ptr) { return check_and_cast<WriteCompleted*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __WRITECOMPLETED_M_H

