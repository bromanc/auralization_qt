#include "qltyacousparam.h"

QltyAcousParam::QltyAcousParam() {

    this->numSources = 0;
    this->numReceivers = 0;
    this->T30 = nullptr;
    this->EDT = nullptr;
    this->D50  = nullptr;
    this->D80  = nullptr;
    this->C50  = nullptr;
    this->C80  = nullptr;
    this->TS  = nullptr;
    this->G  = nullptr;
    this->LG  = nullptr;
    this->LF  = nullptr;
    this->LFC  = nullptr;
    this->ST1  = nullptr;

}

QltyAcousParam::~QltyAcousParam() {}

bool QltyAcousParam::createQlyParamMat(int sources, int receivers){

    try {
        this->numSources = sources;
        this->numReceivers = receivers;
        this->T30 = new float*[this->numReceivers];
        this->EDT = new float*[this->numReceivers];
        this->D50 = new float*[this->numReceivers];
        this->D80 = new float*[this->numReceivers];
        this->C50 = new float*[this->numReceivers];
        this->C80 = new float*[this->numReceivers];
        this->TS = new float*[this->numReceivers];
        this->G = new float*[this->numReceivers];
        this->LG = new float*[this->numReceivers];
        this->LF = new float*[this->numReceivers];
        this->LFC = new float*[this->numReceivers];
        this->ST1 = new float*[this->numReceivers];

        for (int i = 0; i < this->numReceivers; i++) {
            this->T30[i] = new float[NumberBands + 1];
            this->EDT[i] = new float[NumberBands + 1];
            this->D50[i] = new float[NumberBands + 1];
            this->D80[i] = new float[NumberBands + 1];
            this->C50[i] = new float[NumberBands + 1];
            this->C80[i] = new float[NumberBands + 1];
            this->TS[i] = new float[NumberBands + 1];
            this->G[i] = new float[NumberBands + 1];
            this->LG[i] = new float[NumberBands + 1];
            this->LF[i] = new float[NumberBands + 1];
            this->LFC[i] = new float[NumberBands + 1];
            this->ST1[i] = new float[NumberBands + 1];

            for (int j = 0; j < (NumberBands + 1); j++) {
                this->T30[i][j] = 0.0;
                this->EDT[i][j] = 0.0;
                this->D50[i][j] = 0.0;
                this->D80[i][j] = 0.0;
                this->C50[i][j] = 0.0;
                this->C80[i][j] = 0.0;
                this->G[i][j] = 0.0;
                this->LG[i][j] = 0.0;
                this->LF[i][j] = 0.0;
                this->LFC[i][j] = 0.0;
                this->ST1[i][j] = 0.0;
            }
        }
        return true;
    } catch (...) {
        return false;
    }

}

bool QltyAcousParam::deleteQltyParamMat(){

    try {
        for (int i = 0; i < this->numReceivers; i++) {
            delete [] this->T30[i];
            delete [] this->EDT[i];
            delete [] this->D50[i];
            delete [] this->D80[i];
            delete [] this->C50[i];
            delete [] this->C80[i];
            delete [] this->TS[i];
            delete [] this->G[i];
            delete [] this->LG[i];
            delete [] this->LF[i];
            delete [] this->LFC[i];
            delete [] this->ST1[i];
        }

        delete [] this->T30;
        delete [] this->EDT;
        delete [] this->D50;
        delete [] this->D80;
        delete [] this->C50;
        delete [] this->C80;
        delete [] this->TS;
        delete [] this->G;
        delete [] this->LG;
        delete [] this->LF;
        delete [] this->LFC;
        delete [] this->ST1;

        this->numSources = 0;
        this->numReceivers = 0;
        this->T30 = nullptr;
        this->EDT = nullptr;
        this->D50  = nullptr;
        this->D80  = nullptr;
        this->C50  = nullptr;
        this->C80  = nullptr;
        this->TS  = nullptr;
        this->G  = nullptr;
        this->LG  = nullptr;
        this->LF  = nullptr;
        this->LFC  = nullptr;
        this->ST1  = nullptr;

        return true;
    } catch (...) {
        return false;
    }

}
