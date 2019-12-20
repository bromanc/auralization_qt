#ifndef DIRECTIVITY_H
#define DIRECTIVITY_H

#include <definitions.h>
#include <stddef.h>

class Directivity
{
private:
    char name[MaxNChar + 1];
    double spectrum[NumberBands];
    double directivity[NumberBands][MaxNAngles];
public:
    Directivity();
    ~Directivity();
    void normalize();
    void clear();
};

#endif // DIRECTIVITY_H
