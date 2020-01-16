#include "material.h"

Material::Material() {}

Material::~Material() {}

void Material::clear() {
    this->serial = None;

    for (int i = 0; i < MaxNChar * 6; i++) {
        this->name[i] = NULL;
    }

    for (int j = 0; j < NumberBands2; j++) {
        this->absorption[j] = None;
        this->scaterring[j] = None;
    }

    this->materialCriteria1 = None;
    this->materialCriteria2 = None;
    this->surfaceSuitability1 = None;
    this->surfaceSuitability2 = None;
    this->characterAbsorption1 = None;
    this->characterAbsorption2 = None;
    this->color.setRgb(0, 0, 1);

}
