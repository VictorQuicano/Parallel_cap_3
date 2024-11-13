#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char* argv[]) 
{
    int processRank, totalProcesses;
    int localSum, globalSum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
    MPI_Comm_size(MPI_COMM_WORLD, &totalProcesses);

    localSum = processRank + 1;

    int remainingProcesses = totalProcesses;
    int stepSize = 1;

    while (remainingProcesses > 1) 
    {
        int partnerProcess;
        
        if (remainingProcesses % 2 != 0 && processRank == remainingProcesses - 1) {
            MPI_Send(&localSum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            remainingProcesses--;
            continue;
        } else if (processRank % (2 * stepSize) == 0) {
            partnerProcess = processRank + stepSize;
            if (partnerProcess < totalProcesses) 
            {
                int receivedValue;
                MPI_Recv(&receivedValue, 1, MPI_INT, partnerProcess, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                localSum += receivedValue;
            }
        } else if ((processRank % (2 * stepSize)) == stepSize) {
            partnerProcess = processRank - stepSize;
            MPI_Send(&localSum, 1, MPI_INT, partnerProcess, 0, MPI_COMM_WORLD);
            break;
        }

        stepSize *= 2;
        remainingProcesses /= 2;
    }

    if (processRank == 0 && totalProcesses % 2 != 0) 
    {
        int extraValue;
        MPI_Recv(&extraValue, 1, MPI_INT, totalProcesses - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        localSum += extraValue;
    }

    if (processRank == 0) 
    {
        globalSum = localSum;
        cout << "Suma total de todos los procesos: " << globalSum << endl;
    }

    MPI_Finalize();
    return 0;
}
