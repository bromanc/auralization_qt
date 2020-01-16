#include "source.h"

Source::Source(){}

Source::~Source(){}

void Source::calculateBase(){

    QVector3D tempBase0, tempBase1, tempBase2, unitaryVector;
    double angle = this->rotation * M_PI/180;

    unitaryVector.setX(0);
    unitaryVector.setY(0);
    unitaryVector.setZ(1);

    tempBase0 = this->target.vectorCreation(this->position);
    tempBase0.normalize();

    QVector3D aux = unitaryVector.operator*=(tempBase0);

    if(aux.x() == 0 && aux.y() == 0 && aux.z() == 0){
        unitaryVector.setX(1);
    }

    unitaryVector.setY(0);
    unitaryVector.setZ(0);

    tempBase1 = QVector3D::normal(unitaryVector, tempBase0);
    tempBase2 = QVector3D::normal(tempBase0, tempBase1);

    this->base0 = tempBase0;
    this->base1 = tempBase1.operator*=(cos(angle)).operator+=(tempBase2.operator*=(sin(angle)));
    this->base2 = tempBase1.operator*=(cos(-angle)).operator+=(tempBase2.operator*=(sin(-angle)));

}

void Source::clear(){

    this->Name[0]='S';
    this->Name[1]='o';
    this->Name[2]='u';
    this->Name[3]='r';
    this->Name[4]='c';
    this->Name[5]='e';
    this->Name[6]=' ';
    this->Name[7]='#';
    this->Name[8]=NULL;

    this->power = 0.01;
    this->position = Point();
    this->target = Point();
    this->rotation = 0.0;
    this->visualRadius = 0.3;
    this->idDirectivity = None;
    this->on = true;

    for (int i = 0; i < NumberBands; i++) {
        this->powerSpectrum[i] = 1;
    }

    this->base0 = QVector3D();
    this->base1 = QVector3D();
    this->base2 = QVector3D();

}
