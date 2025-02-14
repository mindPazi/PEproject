//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __HARDDISKWRITEOPERATIONS_DISK_H_
#define __HARDDISKWRITEOPERATIONS_DISK_H_

#include <omnetpp.h>
#include <queue>
#include "CompletingAWrite_m.h"
#include "WriteRequest_m.h"
#include "WriteCompleted_m.h"

using namespace omnetpp;

class Disk: public cSimpleModule {
private:
    double writeSpeed_; // MB/s (W)
    double seekTime_; // Millisecondi (S)
    double interChunkDelay_; // Millisecondi (L)
    int maxChunkSize_; // K

    bool busy_;
    std::queue<WriteRequest*> writeQueue; // coda delle richieste di scrittura

    // Metriche
    double totalBusyTime_;
    simtime_t lastBusyStart_;
    simsignal_t writeFileTimeSignal_;
    simsignal_t writeChunkTimeSignal_;
    simsignal_t queueLengthSignal_;
    simsignal_t queueLengthTimeSignal_;
    double totalQueueLengthTime_;
    simsignal_t busyPercentageSignal_;
    simtime_t lastQueueLengthChange_;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    int getChunkSize(int bytesRemainingToWrite);
    void writeAndSchedule(WriteRequest *nextReq);
    bool itsADifferentFile();
    void sendWriteCompleted(int processId, double writeTime);
};

#endif
