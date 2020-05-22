#include "transcode.hpp"

#include <iostream>
#include <string>

void badUsage() {
    std::cerr << "Usage: transcoder <valid DNA secuence>" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        badUsage();
    }

    std::string secuence = argv[1];
    transcode(secuence);
    std::cout << secuence << std::endl;

    return EXIT_SUCCESS;
}