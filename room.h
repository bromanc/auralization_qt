#ifndef ROOM_H
#define ROOM_H

#include <point.h>
#include <planelayer.h>
#include <sourcelayer.h>
#include <receiverlayer.h>
#include <reflector.h>

class Room
{
private:
    int numPlanes, numSources, numReceivers, numReflectors;
    double horViewerAngle, verViewerAngle, obsDistance, focus, grigSpace, gridElements;
    bool grid;
    Point c;
    PlaneLayer *planeLayers;
    SourceLayer *sourceLayers;
    ReceiverLayer *receiverLayers;
    Reflector *reflectors;
public:
    Room();
    ~Room();
    void clear();
    void init();
    void newPlaneLayer(int n);
    void newSourceLayer(int n);
    void newReceiverLayer(int n);
    void newReflector(int n);
    void deletePlaneLayer(int planeLayer);
    void deleteSourceLayer(int sourceLayer);
    void deleteReceiverLayer(int receiverLayer);
    void deleteReflector(int reflector);
};

#endif // ROOM_H
