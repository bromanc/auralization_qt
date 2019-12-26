#include "directivity.h"

Directivity::Directivity() {}

Directivity::~Directivity() {}

void Directivity::normalize(){

    double c = 0;

    for (int i = 0; i < NumberBands; i++) {
        c += (this->spectrum[i] / NumberBands);
    }

    for (int i = 0; i < NumberBands; i++) {
        this->spectrum[i] /= c;
    }

    for (int j = 0; j < MaxNAngles; j++) {
        c = 0;
        for (int i = 0; i < NumberBands; i++) {
            c += (this->directivity[i][j] / NumberBands);
        }
        for (int i  = 0; i < NumberBands; i++) {
            this->directivity[i][j] /= c;
        }
    }

}

void Directivity::clear(){

    this->name[0] = NULL;

    for (int i = 0; i < NumberBands; i++) {
        this->spectrum[i] = 1;
    }

    for (int i = 0; i < NumberBands; i++) {
        for (int j = 0; j < MaxNAngles; j++) {
            this->directivity[i][j] = 1;
        }
    }

}
