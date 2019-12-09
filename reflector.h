#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <definitions.h>
#include <point.h>

class Reflector
{
private:
    int source, plane;
    Point reflectedPoints[MaxNPoints];
public:
    Reflector();
    ~Reflector();
    void clear();
};

#endif // REFLECTOR_H
