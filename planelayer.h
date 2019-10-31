#ifndef PLANELAYER_H
#define PLANELAYER_H

#include <definitions.h>
#include <plane.h>

class PlaneLayer
{
private:
    char Name[MaxNChar + 1];
    int numPlanes;
    Plane *plane;
    int idMaterial;
public:
    PlaneLayer();
    ~PlaneLayer();
    void newPlanes(int n);
    void deletePlanes(int nSelectedPlanes, int selectedPlane[MaxNSelectedPlanes]);
    void clear(void);
    void init(void);
};

#endif // PLANELAYER_H
