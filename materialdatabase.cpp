#include "materialdatabase.h"

MaterialDataBase::MaterialDataBase() {}

MaterialDataBase::~MaterialDataBase() {}

void MaterialDataBase::init(){
    this->numMaterials = 0;
    this->materials = nullptr;
}

void MaterialDataBase::newMaterial(int n){

    Material *tempMaterial = new Material[this->numMaterials + n] ();

    for (int i = 0; i < this->numMaterials; i++) {
        tempMaterial[i] = this->materials[i];
    }

    for (int i = this->numMaterials; i < (this->numMaterials + n); i++) {
        tempMaterial[i].clear();
    }

    if(this->numMaterials > 0)
        delete [] this->materials;

    this->materials = tempMaterial;
    this->numMaterials += n;

}

void MaterialDataBase::deleteMaterial(int m){

    if(this->numMaterials > 0 && m > -1){
        Material *tempMaterial = new Material[this->numMaterials - 1] ();
        int aux = 0;

        for (int i = 0; i < this->numMaterials; i++) {
            if(i != m){
                tempMaterial[aux] = this->materials[i];
                aux++;
            }
        }

        delete [] this->materials;
        this->materials = tempMaterial;
        this->numMaterials--;
    }

}

void MaterialDataBase::clear(){
    if(this->numMaterials > 0)
        delete [] this->materials;

    this->materials = nullptr;
    this->numMaterials = 0;
}
