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

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Process : public cSimpleModule
{
private:
    int processId_;
    int chunkSize_;
    simsignal_t writeFileTime_;
    bool uniformInterArrivals_;
    bool uniformFileSizes_;
    std::exponential_distribution<> interArrivalDist_;
    std::mt19937 generator_;

    // Distribuzioni delle dimensioni dei file
    std::uniform_real_distribution<> uniformDist_;
    std::exponential_distribution<> exponentialDist_;
    bool useUniform_;

    // Parametri dei chunk
    std::vector<double> chunkSizes_; // K

    // Identificatore unico del file
    int fileCount_;

    // Timer per la prossima generazione di file
    cMessage *fileGenerationMsg_;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

#endif
