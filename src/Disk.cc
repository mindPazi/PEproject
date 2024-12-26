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

//todo: gestire le statistiche
//todo: creare le classi WriteRequest e CompletingWrite
#include "Disk.h"

Define_Module(Disk);

void Disk::initialize()
{
    writeSpeed_ = par("writeSpeed").doubleValue(); // MB/s
    seekTime_ = par("seekTime").doubleValue() / 1000.0; // Convertito in secondi
    interChunkDelay_ = par("interChunkDelay").doubleValue() / 1000.0; // Convertito in secondi
    maxChunkSize_ = par("chunkSize").intValue(); // K bytes


    busy_ = false;
    totalBusyTime_ = 0.0;
    lastBusyStart_ = 0.0;

    maxQueueLength_ = 0;
    totalQueueLengthTime_ = 0.0; // tempo in cui la coda è piena
    lastQueueLengthChange_ = simTime();

    // Inizializza mappa dei file
}

void Disk::handleMessage(cMessage *msg)
{
    if (dynamic_cast<WriteRequest*>(msg)) { // arriva una write request nella coda
        WriteRequest *writeReq = check_and_cast<WriteRequest*>(msg);

        // tempo trascorso dell'ultima entrata o uscita di un processo dalla coda
        double timeSinceLastChange = (simTime() - lastQueueLengthChange_).dbl(); //resituisce un double facendo .dbl();
        totalQueueLengthTime_ += writeQueue.size() * timeSinceLastChange;
        lastQueueLengthChange_ = simTime(); //istante dell'ultimo cambiamento nella coda

        if (!busy_) {
            // Il disco è libero, inizia immediatamente la scrittura
            busy_ = true;
            lastBusyStart_ = simTime(); //istante di inizio della scrittura

            // Calcolo del tempo di scrittura
            double writeTime;
            if(itsADifferentFile()) //calcola con una certa probabilità che il file sia diverso da quello della scrittura precedente
                // aggiunge il seek time
                writeTime = seekTime_;
            else
                // aggiunge inter chunk delay
                writeTime = interChunkDelay_;

            //estraggo la dim del file
            int fileSize = writeReq->getFileSize();
            if(fileSize>maxChunkSize_){
                //devo completare la scrittura in più step
                CompletingAWrite *cwMsg = new CompletingAWrite(fileSize - maxChunkSize); // lo inizializza con i byte rimanenti da scrivere
                writeTime += maxChunkSize / writeSpeed_; // in secondi. Chunk_size(i)={B-iK se B<K, k altrimenti}
                scheduleAt(simTime() + writeTime, cwMsg); // Programma il completamento della scrittura
            }
            else{
                writeTime+= fileSize / writeSpeed_;
                scheduleAt(simTime() + writeTime, writeReq);
            }
        }
        else {
            // Disco occupato, aggiungi alla coda
            writeQueue.push(writeReq);
            // Aggiorna la lunghezza massima della coda
            if (writeQueue.size() > maxQueueLength_)
                maxQueueLength_ = writeQueue.size();
        }

    }
    else if (dynamic_cast<CompletingAWrite*>(msg)){
        // Completamento della scrittura
        CompletingAWrite *cwMsg = check_and_cast<CompletingAWrite*>(msg);

        int chunkSize = getChunkSize(cwMsg->getRemainingBytesToWrite, cwMsg->getIteration());
        double writeTime = interChunkDelay_+ chunkSize / writeSpeed_;
        cwMsg->setRemainingTimeToWrite(chunkSize); //aggiorna sottraendo i bit rimanenti al passo precedente quelli scritti ora
        if(chunkSize != 0)
            scheduleAt(simTime() + writeTime, msg);
        else{
            cMessage queuePopTimer = new cMessage();
            scheduleAt(simTime() + writeTime,queuePopTimer);
            delete msg;
        }
    }
    else{
//TODO: gestire la logica di estrazione
        // Aggiorna il tempo totale di occupazione del disco
        totalBusyTime_ += (simTime() - lastBusyStart_).dbl();

        // Verifica se ci sono altre richieste nella coda
        if (!writeQueue.empty()) {
            WriteRequest *nextReq = writeQueue.front();
            writeQueue.pop();

            // Aggiorna le metriche della coda
            double timeSinceLastChange = (simTime() - lastQueueLengthChange_).dbl();
            totalQueueLengthTime_ += (writeQueue.size() +1) * timeSinceLastChange; // Prima di dequeue
            lastQueueLengthChange_ = simTime();

            // Inizia la scrittura del prossimo file
            double writeTime = nextReq->getChunkSize() / writeSpeed_; // secondi
            writeTime += seekTime_; // aggiungi il tempo di ricerca

            // Programma il completamento della scrittura
            scheduleAt(simTime() + writeTime, nextReq);
            // Aggiorna il tempo di inizio occupazione
                        lastBusyStart_ = simTime();
                    }
                    else {
                        // Disco libero
                        busy_ = false;
                    }

                    // Elimina il messaggio
                    delete msg;
                }
            }

// calcola quanti bytes deve scrivere il processo
int Disk::getChunkSize(int bytesRemainingToWrite, int i){
    if(bytesRemainingToWrite == 0)
        return 0;
    if(bytesRemainingToWrite <= maxChunkSize_)
        return bytesRemainingToWrite - i*maxChunkSize_;
    return maxChunkSize_;
}

void Disk::finish()
{
    // Calcolo delle metriche
    double diskUtilization = (totalBusyTime_ / par("simulationDuration").doubleValue()) * 100.0;
    double averageQueueLength = totalQueueLengthTime / par("simulationDuration").doubleValue();

    // Stampa delle metriche
    EV << "Disk Utilization: " << diskUtilization << " %\n";
    EV << "Max Queue Length: " << maxQueueLength_ << "\n";
    EV << "Average Queue Length: " << averageQueueLength << "\n";

    // Ulteriori metriche possono essere calcolate e stampate
}
