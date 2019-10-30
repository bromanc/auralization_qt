#ifndef ROOM_H
#define ROOM_H

#include <point.h>

class Room
{
private:
    int numPlanes, numSources, numReceivers, numReflectors;
    double horViewerAngle, verViewerAngle, obsDistance, focus, grigSpace, gridElements;
    bool grid;
    Point c;
public:
    Room();

};

#endif // ROOM_H
