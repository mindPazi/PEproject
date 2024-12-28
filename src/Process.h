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

#ifndef __HARDDISKWRITEOPERATIONS_PROCESS_H_
#define __HARDDISKWRITEOPERATIONS_PROCESS_H_

#include <omnetpp.h>
#include "WriteRequest_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Process : public cSimpleModule
{
private:
    int processId_;
    simtime_t lastTimeSent_;

    //Distribuzione di T
    double meanInterArrivalDistribution;


    simsignal_t writeRequestResponseTimeSignal_;

    double meanWriteSizeForExponential;
    // Distribuzioni di B
    bool uniformWriteSizeDistribution;


    bool waitingForResponse;


  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendWriteRequest();
    virtual void finish() override;
};

#endif
