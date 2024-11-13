#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <mpi.h>

using namespace std;

void merge(vector<int>& left, vector<int>& right, vector<int>& result) {
    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result[k++] = left[i++];
        } else {
            result[k++] = right[j++];
        }
    }
    while (i < left.size()) {
        result[k++] = left[i++];
    }
    while (j < right.size()) {
        result[k++] = right[j++];
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank, comm_sz;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    
    int n;
    if (rank == 0) {
        cout << "Numero de elementos a ordenar (n): ";
        cin >> n;
    }
    
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    int local_n = n / comm_sz;
    vector<int> local_data(local_n);
    
    mt19937 rng(rank + 1);
    uniform_int_distribution<int> dist(1, 100);
    
    
    for (int i = 0; i < local_n; ++i) {
        local_data[i] = dist(rng);
    }

    sort(local_data.begin(), local_data.end());

    vector<int> gathered_data;
    if (rank == 0) {
        gathered_data.resize(n);
    }
    
    MPI_Gather(local_data.data(), local_n, MPI_INT, gathered_data.data(), local_n, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        vector<int> sorted_data;
        sorted_data.reserve(n);
        
        for (int i = 0; i < comm_sz; ++i) {
            vector<int> temp(gathered_data.begin() + i * local_n, gathered_data.begin() + (i + 1) * local_n);
            if (i == 0) {
                sorted_data = temp;
            } else {
                vector<int> merged_data(sorted_data.size() + temp.size());
                merge(sorted_data, temp, merged_data);
                sorted_data = merged_data;
            }
        }
        
        cout << "Dara ordenada: ";
        for (const int& num : sorted_data) {
            cout << num << " ";
        }
        cout << endl;
    }

    MPI_Finalize();
    return 0;
}
