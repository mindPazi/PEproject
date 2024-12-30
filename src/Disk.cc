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

//todo: capire se registrare anche: WaitingTime, tempo di risposta = writeFileTime+WaitingTime, througput,
void Disk::initialize() {
    writeSpeed_ = par("writeSpeed").doubleValue(); // MB/s
    seekTime_ = par("seekTime").doubleValue() / 1000.0; // Convertito in secondi
    interChunkDelay_ = par("interChunkDelay").doubleValue() / 1000.0; // Convertito in secondi
    maxChunkSize_ = par("maxChunkSize"); // K bytes

    writeChunkTimeSignal_ = registerSignal("writeChunkTime");
    writeFileTimeSignal_ = registerSignal("writeFileTime");
    queueLengthSignal_ = registerSignal("queueLength");
    busyPercentageSignal_ = registerSignal("busyPercentage");

    busy_ = false;
    totalBusyTime_ = 0.0;
    lastBusyStart_ = 0.0;

    maxQueueLength_ = 0;
    totalQueueLengthTime_ = 0.0; // tempo in cui la coda è piena
    lastQueueLengthChange_ = simTime();
}

void Disk::handleMessage(cMessage *msg) {
    if (dynamic_cast<WriteRequest*>(msg)) { // arriva una write request nella coda
        WriteRequest *writeReq = check_and_cast<WriteRequest*>(msg); // todo: msg o packet?
        EV <<"total busy time"<<totalBusyTime_<<"/n";
        // tempo trascorso dell'ultima entrata o uscita di un processo dalla coda
        double timeSinceLastChange = (simTime() - lastQueueLengthChange_).dbl(); //resituisce un double facendo .dbl();
        totalQueueLengthTime_ += writeQueue.size() * timeSinceLastChange; // lunghezza della coda pesata per il tempo che ha avuto quella lunghezza
        lastQueueLengthChange_ = simTime(); //istante dell'ultimo cambiamento nella coda

        if (!busy_) { // garantisce le write request che arrivano mentre sto elaborando una richiesta vadano in coda
            // Il disco è libero, inizia immediatamente la scrittura
            busy_ = true;
            lastBusyStart_ = simTime(); //istante di inizio della scrittura
            Disk::writeAndSchedule(writeReq);
        } else {
            // Disco occupato, aggiungi alla coda
            writeQueue.push(writeReq);
            // Aggiorna la lunghezza massima della coda
            if (writeQueue.size() > maxQueueLength_)
                maxQueueLength_ = writeQueue.size();
        }

    } else if (dynamic_cast<CompletingAWrite*>(msg)) { // Completamento della scrittura
        CompletingAWrite *cwMsg = check_and_cast<CompletingAWrite*>(msg);
        int remainingBytesToWrite = cwMsg->getRemainingBytesToWrite();
        int currentIteration = cwMsg->getIteration();

        int chunkSize = Disk::getChunkSize(remainingBytesToWrite);
        cwMsg->setIteration(currentIteration + 1); // incrementa di uno;
        EV << "Disk has to write  " << remainingBytesToWrite << "\n";
        EV << "Disk is doing iteration n " << currentIteration << "\n";
        double writeTime = interChunkDelay_ + chunkSize / writeSpeed_;
        cwMsg->setRemainingBytesToWrite(remainingBytesToWrite - chunkSize); //aggiorna sottraendo i bit rimanenti al passo precedente quelli scritti ora

        if (chunkSize != 0) {
            cwMsg->appendChunkWriteTimes(writeTime);
            emit(writeChunkTimeSignal_, writeTime);
            EV << "Disk has been working for " << writeTime << "\n";
            EV << "Disk has chunk size of  " << chunkSize << "\n";
            scheduleAt(simTime() + writeTime, cwMsg);

        } else {
            cMessage *newExtraxtionTimer = new cMessage();
            for (int i = 0; i < cwMsg->getChunkWriteTimesArraySize() - 1; i++)
                writeTime += cwMsg->getChunkWriteTimes(i); // somma tutti i chunk times
            emit(writeFileTimeSignal_, writeTime);
            sendWriteCompleted(cwMsg->getProcessId(), writeTime);
            delete msg;
            EV << "Disk sent confirm and now is looking for a new message\n";
            scheduleAt(simTime() + writeTime, newExtraxtionTimer);
        }

    } else if (dynamic_cast<cMessage*>(msg)) { //estrazione di un processo dalla coda

        // Verifica se ci sono altre richieste nella coda
        if (!writeQueue.empty()) {
            WriteRequest *nextReq = writeQueue.front();
            writeQueue.pop();

            // Aggiorna le metriche della coda
            double timeSinceLastChange =
                    (simTime() - lastQueueLengthChange_).dbl();
            totalQueueLengthTime_ += (writeQueue.size() + 1)
                    * timeSinceLastChange; // Prima di dequeue
            lastQueueLengthChange_ = simTime();

            // Aggiorna il tempo di inizio occupazione
            lastBusyStart_ = simTime();

            // scrive e schedula la prossima richiesta
            Disk::writeAndSchedule(nextReq);

        } else {
            // Disco libero
            busy_ = false;
            totalBusyTime_ += (simTime() - lastBusyStart_).dbl();
        }

        // Elimina il messaggio
        delete msg;
    } else
        EV << "Incorrect message type." << "\n";
}

// calcola quanti bytes deve scrivere il processo
int Disk::getChunkSize(int bytesRemainingToWrite) {
    if (bytesRemainingToWrite <= maxChunkSize_)
        return bytesRemainingToWrite;
    else
        return maxChunkSize_;
}

void Disk::writeAndSchedule(WriteRequest *nextReq) {
    double writeTime;
    //todo: creare la funzione itsADifferentFile
    if (itsADifferentFile()) //calcola con una certa probabilità che il file sia diverso da quello della scrittura precedente
        // aggiunge il seek time
        writeTime = seekTime_;
    else
        // aggiunge inter chunk delay
        writeTime = interChunkDelay_;

    //estraggo la dim del file
    int fileSize = nextReq->getBytesToWrite();
    if (fileSize > maxChunkSize_) {
        //devo completare la scrittura in più step
        CompletingAWrite *cwMsg = new CompletingAWrite(); // lo inizializza con i byte rimanenti da scrivere
        writeTime += maxChunkSize_ / writeSpeed_; // in secondi. Chunk_size(i)={B-iK se B<K, k altrimenti}
        cwMsg->setRemainingBytesToWrite(fileSize - maxChunkSize_);
        cwMsg->appendChunkWriteTimes(writeTime);
        cwMsg->setIteration(1);
        cwMsg->setProcessId(nextReq->getProcessId());
        emit(writeChunkTimeSignal_, writeTime);
        EV << "Disk iteration " << cwMsg->getIteration() << "\n";
        EV << "Disk has left " << cwMsg->getRemainingBytesToWrite() << "\n";
        scheduleAt(simTime() + writeTime, cwMsg); // Programma il completamento della scrittura
    } else {
        writeTime += fileSize / writeSpeed_;
        emit(writeFileTimeSignal_, writeTime);
        sendWriteCompleted(nextReq->getProcessId(), writeTime); //invia il messaggio di scrittura completata
        scheduleAt(simTime() + writeTime, new cMessage()); // gestisce l'estrazione di un processo dalla coda
    }
}

bool Disk::itsADifferentFile() {
    // ritorna con prob del 10% che il file sia lo stesso del precedente
    if (par("itsADifferentFileGenerator").doubleValue() <= 0.1)
        return true;
    return false;
}

void Disk::sendWriteCompleted(int processId, double writeTime) {
// Ottenere il modulo target usando il nome
    std::string targetPath = "DiskSimulation.process["
            + std::to_string(processId) + "]";
    cModule *targetModule = getModuleByPath(targetPath.c_str());

    WriteCompleted *writeCompleted = new WriteCompleted();
    writeCompleted->setWriteTime(writeTime);

    if (targetModule != nullptr) {
        // Invia il messaggio alla porta di input del processo target
        send(writeCompleted, "out", targetModule->getIndex());
    }
}

void Disk::finish() {
    // Calcolo delle metriche
    double simDuration = par("simulationDuration").doubleValue();
    if (totalBusyTime_ == 0) // se totalBusyTime==0 vuoldire che il disco non è mai stato libero e la statistica non è stata aggiornata
    {
        totalBusyTime_ = simDuration;
        EV <<"total busy time"<<totalBusyTime_;
    }
    double diskUtilization = (totalBusyTime_ / simDuration) * 100.0; // *100 per esprimere la percentuale
    emit(busyPercentageSignal_, diskUtilization);

    double averageQueueLength = totalQueueLengthTime_
            / par("simulationDuration").doubleValue();
    emit(queueLengthSignal_, averageQueueLength);

    //elimina le richieste in coda
    while (!writeQueue.empty()) {
        WriteRequest *msg = writeQueue.front();
        writeQueue.pop();
        delete msg;
    }
}
