#ifndef POINT_H
#define POINT_H

#include <QVector3D>

class Point
{
private:
    float x, y, z;
public:
    Point();
    Point(float x, float y, float z);
    ~Point();
    Point traslation(QVector3D v);
    Point addTwoCoordinates(Point p);
    QVector3D vectorCreation(Point p);
    Point scalarMultiplication(float s);
    Point scalarDivision(float s);
    void matchValue(float v);
    bool comparePoints(Point p);
    float maxValueCoordinates(void);
    float minValueCoordiantes(void);
    Point abs(void);
};

#endif // POINT_H
