#include "planelayer.h"

PlaneLayer::PlaneLayer() {}

PlaneLayer::~PlaneLayer() {}

void PlaneLayer::newPlanes(int n){

    Plane *tempPlane = new Plane[this->numPlanes + n];

    for (int i = 0; i < this->numPlanes; i++) {
        tempPlane[i] = this->plane[i];
    }

    for (int j = this->numPlanes; j < this->numPlanes + n ; j++) {
        Plane aux = tempPlane[j];
        aux.clear();
    }

    if(this->numPlanes > 0){
        delete [] this->plane;
        this->plane = nullptr;
    }

    this->plane = tempPlane;
    this->numPlanes += n;

}

void PlaneLayer::deletePlanes(int nSelectedPlanes, int *selectedPlane){
    bool deleted;
    int i, j, k = 0;

    if(this->numPlanes > 0 && nSelectedPlanes > 0){
        Plane *tempPlane = new Plane[this->numPlanes - nSelectedPlanes];

        for (i = 0; i < this->numPlanes; i++) {
            deleted = false;

            for(j = 0; j < nSelectedPlanes; j++){
                if(i == selectedPlane[j]){
                    deleted = true;
                }
            }

            if(!deleted){
                tempPlane[k] = this->plane[i];
                k++;
            }

        }

        delete[] this->plane;
        this->plane = tempPlane;
        this->numPlanes -= nSelectedPlanes;

    }

}

void PlaneLayer::clear(){

    for (int i = 0; i < MaxNChar + 1; i++) {
        this->Name[i] = NULL;
    }

    if(this->numPlanes > 0){
        delete[] this->plane;
        this->plane = nullptr;
    }

    this->numPlanes = 0;
    this->idMaterial = None;

}

void PlaneLayer::init(){

    for (int i = 0; i < MaxNChar; i++) {
        this->Name[i] = NULL;
    }

    this->Name[0]='P';
    this->Name[1]='.';
    this->Name[2]=' ';
    this->Name[3]='L';
    this->Name[4]='a';
    this->Name[5]='y';
    this->Name[6]='e';
    this->Name[7]='r';
    this->Name[8]=' ';
    this->Name[9]='#';

    if(this->numPlanes > 0){
        delete[] this->plane;
        this->plane = nullptr;
    }else{
        this->plane = nullptr;
    }

    this->numPlanes = 0;
    this->idMaterial = None;

}

