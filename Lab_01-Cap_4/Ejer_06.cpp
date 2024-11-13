#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>

void read_matrix(int n, std::vector<double> &A, int rank) {
    if (rank == 0) {
        for (int i = 0; i < n * n; i++) {
            A[i] = static_cast<double>(i % n);
        }
    }
    // Broadcast de la matriz a todos los procesos
    MPI_Bcast(A.data(), n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

void distribute_vector(int n, std::vector<double> &x, std::vector<double> &local_x, int rank) {
    // Se distribuyen los componentes del vector
    if (rank < n) {
        local_x[rank] = x[rank];
    }
    // Broadcast del vector local
    MPI_Bcast(local_x.data(), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

int main(int argc, char **argv) {
    int rank, size;
    int n = 4; // Orden de la matriz (debe ser un cuadrado perfecto)
    int sqrt_comm_sz; // Raíz cuadrada del número de procesos
    std::vector<double> A(n * n);
    std::vector<double> local_A;
    std::vector<double> x(n);
    std::vector<double> local_x(n);
    std::vector<double> local_result;
    std::vector<double> result(n);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    sqrt_comm_sz = static_cast<int>(sqrt(size));
    int local_n = n / sqrt_comm_sz; // Tamaño de la submatriz local

    local_A.resize(local_n * n);
    local_result.resize(local_n, 0.0);

    if (rank == 0) {
        read_matrix(n, A, rank);
        // Inicializa el vector
        for (int i = 0; i < n; i++) {
            x[i] = static_cast<double>(i); // Inicialización de ejemplo
        }
    }

    // Asegúrate de que local_x tenga un tamaño correcto
    if (rank < n) {
        local_x.resize(n);
    }

    // Distribuir los componentes del vector
    distribute_vector(n, x, local_x, rank);

    // Distribución de submatrices
    MPI_Scatter(A.data(), local_n * n, MPI_DOUBLE, local_A.data(), local_n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Cálculo del resultado local
    for (int i = 0; i < local_n; i++) {
        for (int j = 0; j < n; j++) {
            local_result[i] += local_A[i * n + j] * local_x[j];
        }
    }

    // Reunir resultados
    MPI_Gather(local_result.data(), local_n, MPI_DOUBLE, result.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Proceso 0 imprime el resultado
    if (rank == 0) {
        std::cout << "Vector resultado:\n";
        for (int i = 0; i < n; i++) {
            std::cout << result[i] << " ";
        }
        std::cout << "\n";
    }

    // Finaliza MPI
    MPI_Finalize();
    return 0;
}
