#include <iostream>
#include <mpi.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) 
{
    int processId, totalProcesses;
    long long int totalTosses, localTosses, circleCount = 0;
    long long int globalCircleCount = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);
    MPI_Comm_size(MPI_COMM_WORLD, &totalProcesses);

    if (processId == 0)
    {
        cout << "Ingrese el número total de lanzamientos: ";
        cin >> totalTosses;
    }

    MPI_Bcast(&totalTosses, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);

    localTosses = totalTosses / totalProcesses;

    srand(static_cast<unsigned>(time(0)) + processId);

    for (long long int toss = 0; toss < localTosses; ++toss) 
    {
        double xCoord = (static_cast<double>(rand()) / RAND_MAX) * 2.0 - 1.0;
        double yCoord = (static_cast<double>(rand()) / RAND_MAX) * 2.0 - 1.0;
        double distanceSq = xCoord * xCoord + yCoord * yCoord;

        if (distanceSq <= 1.0) 
        {
            ++circleCount;
        }
    }

    MPI_Reduce(&circleCount, &globalCircleCount, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (processId == 0) 
    {
        double piEstimate = 4.0 * static_cast<double>(globalCircleCount) / static_cast<double>(totalTosses);
        cout << "Estimación de pi: " << piEstimate << endl;
    }

    MPI_Finalize();
    return 0;
}
