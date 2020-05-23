#include "transcode.hpp"

#include <string>

void transcode(std::string &secuence) {
    #pragma omp parallel for
    for (int i = 0; i < secuence.length(); i++) {
        if (secuence[i] == 'T') {
            secuence[i] = 'U';
        }
    }
}