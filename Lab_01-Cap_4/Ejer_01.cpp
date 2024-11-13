#include <iostream>
#include <vector>
#include <mpi.h>
#include <cmath>

using namespace std;

int DetermineBinIndex(double value, const vector<double>& binUpperLimits, double minRange) 
{
    int binIndex = 0;
    while (binIndex < binUpperLimits.size() && value >= binUpperLimits[binIndex]) 
    {
        ++binIndex;
    }
    return binIndex;
}

int main(int argc, char* argv[]) 
{
    int processID, totalProcesses;
    int totalDataCount = 20;
    double rangeMin = 0.0, rangeMax = 5.0;
    int totalBins = 5;
    
    vector<double> measurements = {1.3, 2.9, 0.4, 0.3, 1.3, 4.4, 1.7, 0.4, 3.2, 0.3, 4.9, 2.4, 3.1, 4.4, 3.9, 0.4, 4.2, 4.5, 4.9, 0.9};
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processID);
    MPI_Comm_size(MPI_COMM_WORLD, &totalProcesses);

    double binInterval = (rangeMax - rangeMin) / totalBins;
    vector<double> binUpperLimits(totalBins);
    vector<int> binCounts(totalBins, 0);

    for (int i = 0; i < totalBins; ++i) 
    {
        binUpperLimits[i] = rangeMin + binInterval * (i + 1);
    }

    int localDataCount = totalDataCount / totalProcesses;
    int extraData = totalDataCount % totalProcesses;
    if (processID < extraData) 
    {
        ++localDataCount;
    }

    vector<double> localMeasurements(localDataCount);
    vector<int> sendDataCounts(totalProcesses);
    vector<int> offsets(totalProcesses);

    int currentOffset = 0;
    for (int i = 0; i < totalProcesses; ++i) 
    {
        sendDataCounts[i] = totalDataCount / totalProcesses + (i < extraData ? 1 : 0);
        offsets[i] = currentOffset;
        currentOffset += sendDataCounts[i];
    }

    MPI_Scatterv(measurements.data(), sendDataCounts.data(), offsets.data(), MPI_DOUBLE,
                 localMeasurements.data(), localDataCount, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    vector<int> localBinCounts(totalBins, 0);
    for (double value : localMeasurements) 
    {
        int binIndex = DetermineBinIndex(value, binUpperLimits, rangeMin);
        ++localBinCounts[binIndex];
    }

    MPI_Reduce(localBinCounts.data(), binCounts.data(), totalBins, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (processID == 0) 
    {
        cout << "Histogram:\n";
        for (int i = 0; i < totalBins; ++i) 
        {
            cout << "Bin " << i << " [" << (i == 0 ? rangeMin : binUpperLimits[i - 1]) << ", " << binUpperLimits[i] << "): " << binCounts[i] << endl;
        }
    }
    MPI_Finalize();
}
