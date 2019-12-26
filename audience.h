#ifndef AUDIENCE_H
#define AUDIENCE_H

#include <definitions.h>
#include <point.h>
#include <QColor>
#include <triangle.h>
#include <QVector3D>
#include <math.h>

class Audience
{
private:
    char name[MaxNChar + 1];
    double radius, rotation, grid;
    Point target;
    QColor color;
    Point points[MaxNPoints];
    Triangle triangles[MaxNPoints - 2];
    Point centralPoint;
    QVector3D base0, base1, base2;
    bool on;
    int numPoints, numTriangles;
public:
    Audience();
    ~Audience();
    void calculateBase();
    void clear();
};

#endif // AUDIENCE_H
