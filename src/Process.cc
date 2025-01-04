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

#include "Process.h"

Define_Module(Process);

//todo: capire come gestire la generazione dei tempi di interarrivo e della dim dei file
//todo: nell'ini file servono 2 physical number gen, uno per file dim e l'altro per interarriv. time

void Process::initialize() {
    // inizializzazione dei parametri
    processId_ = par("processId").intValue();

    meanInterArrivalDistribution = par("meanInterArrivalDist").doubleValue();

    uniformWriteSizeDistribution = par("uniformWriteSizes").boolValue();
    meanWriteSizeForExponential =
            par("meanWriteSizeForExponential").doubleValue();

    writeRequestResponseTimeSignal_ = registerSignal(
            "writeRequestResponseTime");

    simtime_t nextDeparture = exponential(meanInterArrivalDistribution, 2);
    // usa il rng 2
    EV<<"using rng2 for departure: "<<nextDeparture<<endl;
    scheduleAt(simTime() + nextDeparture, new cMessage("sendNextRequest"));
}

void Process::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Se non stiamo aspettando una risposta, invia una nuova richiesta
        sendWriteRequest();
        // usa il rng 2
        scheduleAt(simTime() + exponential(meanInterArrivalDistribution, 2),
                new cMessage("sendNextRequest"));
        delete msg;
    } else {
        // Ricezione di una risposta
        // Controlla se ci sono richieste in attesa nella coda
        if (!sentRequests_.empty()) {
            simtime_t sentTime = sentRequests_.front();
            sentRequests_.pop();
            simtime_t responseTime = simTime() - sentTime;
            EV << "Process " << processId_ << " received a response after"
                      << responseTime << "\n";
            emit(writeRequestResponseTimeSignal_, responseTime);
        } else {
            EV
                      << "Unexpected response received with no matching request in queue.\n";
        }
        delete msg;
    }
}

void Process::sendWriteRequest() {
    // Crea un messaggio WriteRequest
    WriteRequest *request = new WriteRequest("WriteRequest");

    // Calcola bytesToWrite in base alla distribuzione
    int bytesToWrite;
    if (uniformWriteSizeDistribution) {
        // usa il rng 0
        bytesToWrite = par("writeSizeForUniform").intValue();
        EV << "bytes to write uniform using rng0: "<<bytesToWrite<<endl;
    } else {
        //usa il rng 1
        bytesToWrite = int(exponential(meanWriteSizeForExponential, 1));
        EV << "bytes to write exp using rng1: "<<bytesToWrite<<endl;

    }

    // Assegna i valori al messaggio
    request->setBytesToWrite(bytesToWrite);

    request->setFileName('A');
    request->setProcessId(processId_);

    // Salva il tempo di invio
    sentRequests_.push(simTime());

    // Invia il messaggio
    send(request, "out");
    EV << "Process " << processId_ << " sent a WriteRequest with bytesToWrite="
              << bytesToWrite << ", fileName=" << request->getFileName()
              << "\n";

}

void Process::finish() {
    // Raccolta statistiche se necessario
    while (!sentRequests_.empty()) {
        EV << "Clearing unprocessed request sent at: " << sentRequests_.front()
                  << "\n";
        sentRequests_.pop();
    }
}

