#ifndef PLANE_H
#define PLANE_H

#include <definitions.h>
#include <point.h>
#include <triangle.h>
#include <vector.h>

class Plane
{
private:
    char Name[MaxNChar + 1];
    int numPoints;
    Point planePoints[MaxNPoints];
    int numTriangles;
    Triangle planeTriangles[MaxNPoints - 2];
    QVector3D normalVector;
public:
    Plane();
    ~Plane();
    void clear(void);
    bool isConvex(void);
};

#endif // PLANE_H
