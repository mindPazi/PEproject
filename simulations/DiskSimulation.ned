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

// DiskSimulation.ned
package harddiskwriteoperations.simulations;

//import omnetpp.common.queue.Queue;

import harddiskwriteoperations.Process;

import harddiskwriteoperations.Disk;

network DiskSimulation
{
    parameters:
        int N; // Numero di processi

    submodules:
        // Creazione di N processi
        process[N]: Process {
            parameters:
                processId = index;
        }

        // Modulo Disk
        disk: Disk {
            @display("p=441,90");
        }
    connections:
        for i=0..N-1 {
            // Connessione da ogni processo al disco per l'invio delle richieste di scrittura
            process[i].out --> disk.in++;
            // Connessione nel verso opposto per l'invio della conferma di scrittura completata 
            disk.out++ --> process[i].in;
        }

}
