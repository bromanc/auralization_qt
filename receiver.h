#ifndef RECEIVER_H
#define RECEIVER_H

#include <definitions.h>
#include <point.h>
#include <QColor>
#include <QtMath>

class Receiver
{
private:
    char Name[MaxNChar + 1];
    double radius, rotation, visualRadius;
    Point position, target;
    QColor color;
    bool on;
    QVector3D base0, base1, base2;
public:
    Receiver();
    ~Receiver();
    void calculateBase();
    void clear();
};

#endif // RECEIVER_H
