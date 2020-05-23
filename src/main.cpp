#include "transcode.hpp"

#include <iostream>
#include <string>
#include <fstream>
// #include <mpi.h>

void badUsage() {
    std::cerr << "Usage: transcoder <valid DNA secuence>" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        badUsage();
    }

    std::ifstream secuence(argv[1]);

    std::string dna;
    std::getline(secuence, dna);

    transcode(dna);
    std::cout << dna << std::endl;

    return EXIT_SUCCESS;
}