#include "audience.h"

Audience::Audience() {}

Audience::~Audience() {}

void Audience::calculateBase(){

    QVector3D tempBase0, tempBase1, tempBase2, unitaryVector;
    double angle = (M_PI * rotation)/180;

    unitaryVector.setX(0.0f);
    unitaryVector.setY(0.0f);
    unitaryVector.setZ(0.0f);

    tempBase0 = this->target.vectorCreation(this->centralPoint);
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

void Audience::clear(){

    this->name[0] = 'A';
    this->name[1] = 'u';
    this->name[2] = 'd';
    this->name[3] = 'i';
    this->name[4] = 'e';
    this->name[5] = 'n';
    this->name[6] = 'c';
    this->name[7] = 'e';
    this->name[8] = ' ';
    this->name[9] = '#';
    this->name[10] = NULL;

    this->radius = 0.15;
    this->target.matchValue(0.0f);
    this->rotation = 0;
    this->grid = 200;
    this->color.setRgb(0, 0, 0);
    this->on = true;
    this->numPoints = 0;

    for (int i = 0; i < MaxNPoints; i++) {
        this->points[i].matchValue(0.0f);
    }

    this->numTriangles = 0;

    for (int j = 0; j < MaxNPoints - 2; j++) {
        this->triangles[j] = Triangle();
    }

    this->centralPoint.matchValue(0.0f);
    this->base0 = QVector3D ();
    this->base1 = QVector3D ();
    this->base2 = QVector3D ();

}
