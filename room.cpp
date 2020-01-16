#include "room.h"

Room::Room() {}

Room::~Room() {}

void Room::deleteReflector(int reflector){

}

void Room::deleteReceiverLayer(int receiverLayer){

    if(this->numReceivers > 0 && receiverLayer > 0){
        int j = 0;
        ReceiverLayer *tempReceiverLayer = new ReceiverLayer[this->numReceivers - 1] ();

        for (int i = 0; i < this->numReceivers; i++) {
            if(i != receiverLayer){
                tempReceiverLayer[i] = this->receiverLayers[i];
                j++;
            }
        }

        this->receiverLayers[receiverLayer].clear();

        delete[] this->receiverLayers;
        this->receiverLayers = tempReceiverLayer;

        this->numReceivers--;
    }

}

void Room::deleteSourceLayer(int sourceLayer){

    if(this->numSources > 0 && sourceLayer > 0){
        int j = 0;
        SourceLayer *tempSourceLayer = new SourceLayer[this->numSources - 1] ();

        for (int i = 0; i < this->numSources; i++) {
            if(i != sourceLayer){
                tempSourceLayer[i] = this->sourceLayers[i];
                j++;
            }
        }

        this->sourceLayers[sourceLayer].clear();

        delete[] this->sourceLayers;
        this->sourceLayers = tempSourceLayer;

        this->numSources--;
    }

}

void Room::deletePlaneLayer(int planeLayer){

    if(this->numPlanes > 0 && planeLayer > 0){
        int j = 0;
        PlaneLayer *tempPlaneLayer = new PlaneLayer[this->numPlanes - 1] ();

        for (int i = 0; i < this->numPlanes; i++) {
            if(i != planeLayer){
                tempPlaneLayer[i] = this->planeLayers[i];
                j++;
            }
        }

        this->planeLayers[planeLayer].clear();

        delete[] this->planeLayers;
        this->planeLayers = tempPlaneLayer;

        this->numPlanes--;
    }

}

void Room::newReflector(int n){

    int i;
    Reflector *tempReflectors = new Reflector[this->numReflectors + n] ();

    for (i = 0; i < this->numReflectors; i++) {
        tempReflectors[i] = this->reflectors[i];
    }

    for (i = this->numReflectors; i < (this->numReflectors + n); i++) {
        tempReflectors[i].clear();
    }

    if(this->numReflectors > 0){
        delete [] this->reflectors;
        this->reflectors = nullptr;
    }

    this->reflectors = tempReflectors;
    this->numReflectors += n;

}

void Room::newReceiverLayer(int n){

    int i;
    ReceiverLayer *tempReceiverLayers = new ReceiverLayer[this->numReceivers + n]();

    for(i = 0; i < this->numReceivers; i++){
        tempReceiverLayers[i] = this->receiverLayers[i];
    }

    for (i = this->numReceivers; i < (this->numReceivers + n); i++) {
        tempReceiverLayers[i].init();
    }

    if(this->numReceivers > 0){
        delete [] this->receiverLayers;
        this->receiverLayers = nullptr;
    }

    this->receiverLayers = tempReceiverLayers;
    this->numReceivers += n;

}

void Room::newSourceLayer(int n){

    int i;
    SourceLayer *tempSourceLayers = new SourceLayer[this->numSources + n]();

    for(i = 0; i < this->numSources; i++){
        tempSourceLayers[i] = this->sourceLayers[i];
    }

    for (i = this->numSources; i < (this->numSources + n); i++) {
        tempSourceLayers[i].init();
    }

    if(this->numSources > 0){
        delete [] this->sourceLayers;
        this->sourceLayers = nullptr;
    }

    this->sourceLayers = tempSourceLayers;
    this->numSources += n;

}

void Room::newPlaneLayer(int n){

    int i;
    PlaneLayer *tempPlaneLayers = new PlaneLayer[this->numPlanes + n]();

    for(i = 0; i < this->numPlanes; i++){
        tempPlaneLayers[i] = this->planeLayers[i];
    }

    for (i = this->numPlanes; i < (this->numPlanes + n); i++) {
        tempPlaneLayers[i].init();
    }

    if(this->numPlanes > 0){
        delete [] this->planeLayers;
        this->planeLayers = nullptr;
    }

    this->planeLayers = tempPlaneLayers;
    this->numPlanes += n;

}
