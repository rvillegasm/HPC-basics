#include "transcode.hpp"

#include <string>
#include <mpi.h>
#include <cstdlib>

char *transcode(std::string &secuence, const int rank, const int nRanks) {
    
    const int stepsPerProcess = double(secuence.length()) / double(nRanks);
    const int iStart = int( stepsPerProcess * rank );
    const int iEnd = int( stepsPerProcess * (rank + 1));
    
    #pragma omp parallel for
    for (int i = iStart; i < iEnd; i++) {
        if (secuence[i] == 'T') {
            secuence[i] = 'U';
        }
    }

    char *rna = NULL;

    if (rank == 0) {
        rna = (char *) malloc(sizeof(char) * secuence.length());
    }

    MPI_Gather(secuence.c_str() + iStart, iEnd - iStart, MPI_CHAR, rna, stepsPerProcess, MPI_CHAR, 0, MPI_COMM_WORLD);

    return rna;
}
