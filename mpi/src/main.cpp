#include "transcode.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <omp.h>
#include <mpi.h>

void badUsage() {
    std::cerr << "Usage: transcoder <valid DNA secuence>" << std::endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        badUsage();
    }

    MPI_Init(&argc, &argv);
    int rank, nRanks;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nRanks);

    std::ifstream secuence(argv[1]);

    std::string dna;
    std::getline(secuence, dna);

    MPI_Barrier(MPI_COMM_WORLD);

    double ts, tf;

    if (rank == 0) ts = omp_get_wtime();
    char *rna = transcode(dna, rank, nRanks);
    if (rank == 0) tf = omp_get_wtime();
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    if (rank == 0) {
        std::cout << "Time in Seconds: " << tf - ts << std::endl;
	rna[dna.length()] = '\0';
        std::ofstream outputFile;
        outputFile.open("outputDna.txt");
        outputFile << rna << std::endl;
        outputFile.close();
    }

    free(rna);
    MPI_Finalize();

    return 0;
}
