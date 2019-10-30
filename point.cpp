#include "point.h"
#include <math.h>

Point::Point(){}

Point::Point(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::~Point() {}

Point Point::traslation(QVector3D v){
    Point aux;
    aux.x = this->x + v.x();
    aux.y = this->y + v.y();
    aux.z = this->z + v.z();
    return aux;
}

Point Point::addTwoCoordinates(Point p){
    Point aux;
    aux.x = this->x + p.x;
    aux.y = this->y + p.y;
    aux.z = this->z + p.z;
    return aux;
}

QVector3D Point::vectorCreation(Point p){
    QVector3D vector;
    vector.setX(this->x - p.x);
    vector.setY(this->y - p.y);
    vector.setZ(this->z - p.z);
    return vector;
}

Point Point::scalarMultiplication(float s){
    Point aux;
    aux.x = this->x * s;
    aux.y = this->y * s;
    aux.z = this->z * s;
    return aux;
}

Point Point::scalarDivision(float s){
    Point aux;
    aux.x = this->x / s;
    aux.y = this->y / s;
    aux.z = this->z / s;
    return aux;
}

void Point::matchValue(float v){
    this->x = this->y = this->z = v;
}

bool Point::comparePoints(Point p){
    if(this->x == p.x && this->y == p.y && this->z == p.z){
        return true;
    }else{
        return false;
    }
}

float Point::maxValueCoordinates(){
    float max;
    if(this->x > this->y){
        max = this->x;
    }else{
        max = this->y;
    }
    if(this->z > max){
        max = this->z;
    }
    return max;
}

float Point::minValueCoordiantes(){
    float min;
    if(this->x < this->y){
        min = this->x;
    }else{
        min = this->y;
    }
    if(this->z < min){
        min = this->z;
    }
    return min;
}

Point Point::abs(){
    Point aux;
    aux.x = fabs(this->x);
    aux.y = fabs(this->y);
    aux.z = fabs(this->z);
    return aux;
}
