#include "receiver.h"

Receiver::Receiver() {}

Receiver::~Receiver() {}

void Receiver::clear(){

    this->Name[0] = 'M';
    this->Name[1] = 'i';
    this->Name[2] = 'c';
    this->Name[3] = 'r';
    this->Name[4] = 'o';
    this->Name[5] = 'p';
    this->Name[6] = 'h';
    this->Name[7] = 'o';
    this->Name[8] = 'n';
    this->Name[9] = 'e';
    this->Name[10] = ' ';
    this->Name[11] = '#';
    this->Name[12] = NULL;

    this->radius = 0.15;
    this->position.matchValue(0.0f);
    this->target.matchValue(0.0f);
    this->rotation = 0;
    this->visualRadius = 0.3;
    this->color.setRed(0);
    this->color.setBlue(0);
    this->color.setGreen(1);
    this->on = true;

    this->base0 = QVector3D();
    this->base1 = QVector3D();
    this->base2 = QVector3D();

}

void Receiver::calculateBase(){

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
