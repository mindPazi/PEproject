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

void Process::initialize()
{
    // inizializzazione dei parametri
    processId_ = par("processId").intValue;
    meanInterArrivalDistribution = par("meanInterArrivalDist").doubleValue();
    uniformWriteSizesDistribution= par("uniformWriteSizes").boolValue();

    waitingForResponse = false;

    writeRequestResponseTimeSignal_ = registerSignal("writeRequestResponseTime");


    scheduleAt(simTime() + exponential(meanInterArrivalDist), new cMessage("sendNextRequest"));
}

void Process::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
    // Se non stiamo aspettando una risposta, invia una nuova richiesta
        if (!waitingForResponse) {
            sendWriteRequest();
            }
        delete msg;
    }else {
        // Ricezione di una risposta
        EV << "Process " << processId << " received a response.\n";

        emit(writeRequestResponseTimeSignal_, (simTime() - lastTimeSent_));
        waitingForResponse = false;
        // Pianifica la prossima richiesta
        scheduleAt(simTime() + exponential(meanInterArrivalDist), new cMessage("SendNextRequest"));
        delete msg;
   }
}

void sendWriteRequest() {
       // Crea un messaggio WriteRequest
       WriteRequest *request = new WriteRequest("WriteRequest");

       // Calcola bytesToWrite in base alla distribuzione
       int bytesToWrite;
       if (uniformWriteSizesDistribution) {
           bytesToWrite = par("writeSizeForUniform");
       } else {
           bytesToWrite = int(exponential(meanWriteSizesForExponential));
       }

       // Assegna i valori al messaggio
       request->setBytesToWrite(bytesToWrite);
       request->setFileName(("fileA").c_str());
       request->setProcessId(processId);

       // Salva il tempo di invio
       lastTimeSent_ = simTime();

       // Invia il messaggio
       send(request, "out");
       EV << "Process " << processId << " sent a WriteRequest with bytesToWrite=" << bytesToWrite
          << ", fileName=" << request->getFileName() << "\n";

       waitingForResponse = true;
   }


void Process::finish()
{
    // Raccolta statistiche se necessario
}

