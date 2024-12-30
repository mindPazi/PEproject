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

package harddiskwriteoperations;

//
// TODO auto-generated module
//
simple Disk
{
    parameters:
        double simulationDuration; // Durata della simulazione       
        double writeSpeed; // W velocità di scrittura del disco
        double seekTime; // S tempo per muovere la testina
        double interChunkDelay; // L tempo che intercorre tra due scrittura consecutive dello stesso file
        int maxChunkSize; // K
        volatile double itsADifferentFileGenerator = default(uniform(0,10));

        @signal[writeFileTime];
        @statistic[writeFileTimeStats](source=writeFileTime; record=stats,vector);
        
        @signal[writeChunkTime];
        @statistic[writeChunkTimeStats](source="writeChunkTime"; record=stats,vector);
        
        // num of processes in the queue
        @signal[queueLength];
        @statistic[queueLengthStats](source="queueLength"; record=stats);// è un solo valore
        
        @signal[busyPercentage];
        @statistic[busyPercentageStats](source="busyPercentage"; record=stats);

   	gates:
   		input in[];
       	output out[];
}
