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
#include <queue>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Process : public cSimpleModule
{
private:
    int processId_;
    //Distribuzione di T
    double meanInterArrivalDistribution;

    //Segnale per le statistiche
    simsignal_t writeRequestResponseTimeSignal_;

    // Distribuzioni di B
    double meanWriteSizeForExponential;
    bool uniformWriteSizeDistribution;


    std::queue<simtime_t> sentRequests_; // Coda per tenere traccia dei tempi di invio



  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendWriteRequest();
    virtual void finish() override;
};

#endif
