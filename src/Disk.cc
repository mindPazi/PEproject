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

#include "Disk.h"

Define_Module(Disk);

void Disk::initialize()
{
    writeSpeed = par("writeSpeed").doubleValue(); // MB/s
    seekTime = par("seekTime").doubleValue() / 1000.0; // Convertito in secondi
    interChunkDelay = par("interChunkDelay").doubleValue() / 1000.0; // Convertito in secondi

    busy = false;
    totalBusyTime = 0.0;
    lastBusyStart = 0.0;

    maxQueueLength = 0;
    totalQueueLengthTime = 0.0; // tempo in cui la coda è piena
    lastQueueLengthChange = simTime();

    // Inizializza mappa dei file
}

void Disk::handleMessage(cMessage *msg)
{
    if (dynamic_cast<WriteRequest*>(msg)) {
        WriteRequest *writeReq = check_and_cast<WriteRequest*>(msg);

        // Aggiornamento delle metriche della coda
        double timeSinceLastChange = (simTime() - lastQueueLengthChange).dbl(); //resituisce un double facendo .dbl();
        totalQueueLengthTime += writeQueue.size() * timeSinceLastChange;
        lastQueueLengthChange = simTime(); //istante dell'ultimo cambiamento nella coda

        if (!busy) {
            // Il disco è libero, inizia immediatamente la scrittura
            busy = true;
            lastBusyStart = simTime();

            // Calcolo del tempo di scrittura
            double writeTime = writeReq->getChunkSize() / writeSpeed; // secondi
            writeTime += seekTime; // aggiungi il tempo di ricerca

            // Programma il completamento della scrittura
            scheduleAt(simTime() + writeTime, writeReq);
        }
        else {
            // Disco occupato, aggiungi alla coda
            writeQueue.push(writeReq);
            // Aggiorna la lunghezza massima della coda
            if (writeQueue.size() > maxQueueLength) {
                maxQueueLength = writeQueue.size();
            }
        }

        // Aggiorna le metriche della coda
    }
    else {
        // Completamento della scrittura
        WriteRequest *writeReq = check_and_cast<WriteRequest*>(msg);

        // Aggiorna il tempo totale di occupazione del disco
        totalBusyTime += (simTime() - lastBusyStart).dbl();

        // Aggiorna le informazioni del file
        int fileId = writeReq->getFileId();
        if (fileInfos.find(fileId) == fileInfos.end()) {
            FileInfo finfo;
            finfo.processId = writeReq->getProcessId();
            finfo.fileId = fileId;
            finfo.startTime = writeReq->getStartTime();
            finfo.endTime = simTime();
            fileInfos[fileId] = finfo;
        }
        else {
            fileInfos[fileId].endTime = simTime();
        }

        // Verifica se ci sono altre richieste nella coda
        if (!writeQueue.empty()) {
            WriteRequest *nextReq = writeQueue.front();
            writeQueue.pop();

            // Aggiorna le metriche della coda
            double timeSinceLastChange = (simTime() - lastQueueLengthChange).dbl();
            totalQueueLengthTime += (writeQueue.size() +1) * timeSinceLastChange; // Prima di dequeue
            lastQueueLengthChange = simTime();

            // Inizia la scrittura del prossimo file
            double writeTime = nextReq->getChunkSize() / writeSpeed; // secondi
            writeTime += seekTime; // aggiungi il tempo di ricerca

            // Programma il completamento della scrittura
            scheduleAt(simTime() + writeTime, nextReq);
            // Aggiorna il tempo di inizio occupazione
                        lastBusyStart = simTime();
                    }
                    else {
                        // Disco libero
                        busy = false;
                    }

                    // Elimina il messaggio
                    delete msg;
                }
            }

            void Disk::finish()
            {
                // Calcolo delle metriche
                double diskUtilization = (totalBusyTime / par("simulationDuration").doubleValue()) * 100.0;
                double averageQueueLength = totalQueueLengthTime / par("simulationDuration").doubleValue();

                // Stampa delle metriche
                EV << "Disk Utilization: " << diskUtilization << " %\n";
                EV << "Max Queue Length: " << maxQueueLength << "\n";
                EV << "Average Queue Length: " << averageQueueLength << "\n";

                // Ulteriori metriche possono essere calcolate e stampate
            }
