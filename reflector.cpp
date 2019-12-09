#include "reflector.h"

Reflector::Reflector() {}

Reflector::~Reflector() {}

void Reflector::clear(){

    this->source = 0;
    this->plane = 0;

    for (int i = 0;i < MaxNPoints; i++) {
        this->reflectedPoints[i].matchValue(0.0f);
    }

}
