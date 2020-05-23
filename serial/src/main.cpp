#include "transcode.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <omp.h>
// #include <mpi.h>

void badUsage() {
    std::cerr << "Usage: transcoder <valid DNA secuence>" << std::endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        badUsage();
    }

    std::ifstream secuence(argv[1]);

    std::string dna;
    std::getline(secuence, dna);

    double ts = omp_get_wtime();
    transcode(dna);
    double tf = omp_get_wtime();

    std::cout << "Time in Seconds: " << tf - ts << std::endl;
    
    std::ofstream outputFile;
    outputFile.open("outputDna.txt");
    outputFile << dna;
    outputFile.close();

    return 0;
}
