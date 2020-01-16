#include "results.h"

Results::Results() {}

Results::~Results() {}

void Results::init(){

    this->receiver = 0;
    this->irDiscretization = 0;
    this->numQAP = 0;

    for (int i = 0; i < NumberBands + 1; i++) {
        this->hybridIR[i] = nullptr;
        this->specularIR[i] = nullptr;
        this->diffuseIR[i] = nullptr;
        this->decayCurve[i] = nullptr;
        this->stopTime[i] = 0;
        this->qltyAcouParam[i] = nullptr;
    }

}

void Results::newData(){

    this->numQAP = 12;

    for (int i = 0; i < NumberBands + 1; i++) {
        this->hybridIR[i] = new float [this->stopTime[i]];
        this->specularIR[i] = new float [this->stopTime[i]];
        this->diffuseIR[i] = new float [this->stopTime[i]];
        this->decayCurve[i] = new float [this->stopTime[i]];
        this->qltyAcouParam[i] = new float [this->stopTime[i]];
    }

    for (int i = 0; i < NumberBands + 1; i++) {
        for (int j = 0; j < this->stopTime[i]; j++) {
            this->hybridIR[i][j] = 0;
            this->specularIR[i][j] = 0;
            this->diffuseIR[i][j] = 0;
            this->decayCurve[i][j] = 0;
        }


        for (int k = 0; k < this->numQAP; k++) {
            this->qltyAcouParam[i][k] = 0;
        }
    }

}

void Results::clear(){

    this->receiver = 0;
    this->irDiscretization = 0;
    this->numQAP = 12;

    for (int i = 0; i < NumberBands + 1; i++) {
        if(this->stopTime[i] > 0){
            delete [] this->hybridIR[i];
            this->hybridIR[i] = nullptr;
            delete [] this->specularIR[i];
            this->specularIR[i] = nullptr;
            delete [] this->diffuseIR[i];
            this->diffuseIR[i] = nullptr;
            delete [] this->decayCurve[i];
            this->decayCurve[i] = nullptr;
        }
        this->stopTime[i] = 0;
    }

    for (int i = 0; i < NumberBands + 1; i++) {
        if(this->numQAP > 0){
            delete [] this->qltyAcouParam[i];
            this->qltyAcouParam[i] = nullptr;
        }
        this->numQAP = 0;
    }

}
