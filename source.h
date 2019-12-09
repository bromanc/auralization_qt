#ifndef SOURCE_H
#define SOURCE_H

#include <definitions.h>
#include <point.h>
#include <QtMath>

class Source
{
private:
    char Name[MaxNChar + 1];
    double power;
    Point position;
    Point target;
    double rotation;
    double visualRadius;
    int idDirectivity;
    bool on;
    double powerSpectrum[NumberBands];
    QVector3D base0, base1, base2;
public:
    Source();
    ~Source();
    void calculateBase(void);
    void clear(void);
};

#endif // SOURCE_H
