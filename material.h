#ifndef MATERIAL_H
#define MATERIAL_H

#include <definitions.h>
#include <QColor>

class Material
{
private:
    int serial;
    int characterAbsorption1, characterAbsorption2;
    int materialCriteria1, materialCriteria2;
    int surfaceSuitability1, surfaceSuitability2;
    char name[MaxNChar * 6], reference[MaxNChar * 2];
    double absorption[NumberBands2], scaterring[NumberBands2];
    QColor color;
public:
    Material();
    ~Material();
    void clear();
};

#endif // MATERIAL_H
