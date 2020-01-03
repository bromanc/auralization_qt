#ifndef MATERIALDATABASE_H
#define MATERIALDATABASE_H

#include "material.h"

class MaterialDataBase
{
private:
    int numMaterials;
    Material *materials;
public:
    MaterialDataBase();
    ~MaterialDataBase();
    void newMaterial(int n);
    void deleteMaterial(int m);
    void clear();
    void init();
};

#endif // MATERIALDATABASE_H
