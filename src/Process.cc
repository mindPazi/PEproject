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
    uniformInterArrivals_ = par("uniformInterarrivals").boolValue();
    uniformFileSizes_= par("uniformFileSizes").boolValue();
    chunkSize_ = par("chunkSize");
    double firstArrival;

    if(uniformInterArrivals_)
        firstArrival = uniform(par("maxInterarrivalTime"));
    else
        firstArrival = exponential(par("maxInterarrivalTime"));

    fileGenerationMsg = new cMessage("GenerateFile");
    scheduleAt(simTime() + firstArrival, fileGenerationMsg);
}

void Process::handleMessage(cMessage *msg)
{
    if (msg == fileGenerationMsg) {
            // Generazione di un nuovo file
            fileCount++;
            double fileSize;
            if (useUniform) {
                fileSize = uniformDist(generator);
            }
            else {
                fileSize = exponentialDist(generator);
            }

            // Creazione della richiesta di scrittura
            // todo: creare un custom message WriteRequest e capire come gestirlo
            //in ogni writeReq
            WriteRequest *writeReq = new WriteRequest("WriteRequest");
            writeReq->setProcessId(processId);
            writeReq->setFileId(fileCount); //
            writeReq->setFileSize(fileSize);
            writeReq->setChunkSize(chunkSize_);
            writeReq->setStartTime(simTime());

            // Invio della richiesta al disco
            send(writeReq, "out");

            // Programmazione della prossima generazione di file
            double nextArrival = interArrivalDist(generator);
            scheduleAt(simTime() + nextArrival, fileGenerationMsg);
        }
        else {
            // Gestione di eventuali messaggi di risposta dal disco
            delete msg;
        }
}

void Process::finish()
{
    // Raccolta statistiche se necessario
}

