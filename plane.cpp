#include "plane.h"

Plane::Plane()
{

}

Plane::~Plane() {}

void Plane::clear(){
    for(int i = 0; i < MaxNChar; i++){
        this->Name[i] = NULL;
    }

    this->Name[0]='P';
    this->Name[1]='l';
    this->Name[2]='a';
    this->Name[3]='n';
    this->Name[4]='e';
    this->Name[5]=' ';
    this->Name[6]='#';

    this->numPoints = 0;
    this->numTriangles = 0;
    this->normalVector = QVector3D();

    for (int j = 0; j < MaxNPoints; j++) {
        this->planePoints[j] = *new Point();
    }

    for (int k = 0; k < MaxNPoints - 2; k++) {
        this->planeTriangles[k] = *new Triangle();
    }

}
