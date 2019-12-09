#include "sourcelayer.h"

SourceLayer::SourceLayer(){}

SourceLayer::~SourceLayer(){}

void SourceLayer::init(){

    for (int i = 0; i < MaxNChar + 1; i++) {
        this->Name[i] = NULL;
    }

    this->Name[0] = 'S';
    this->Name[1] = '.';
    this->Name[2] = ' ';
    this->Name[3] = 'L';
    this->Name[4] = 'a';
    this->Name[5] = 'y';
    this->Name[6] = 'e';
    this->Name[7] = 'r';
    this->Name[8] = ' ';
    this->Name[9] = '#';

    if(this->numSources > 0){
        delete [] this->sources;
        this->sources = nullptr;
    }else{
        this->sources = nullptr;
    }

    this->numSources = 0;
    this->color.setRed(1);
    this->color.setBlue(0);
    this->color.setGreen(0);
    this->idSourceType = None;

}

void SourceLayer::newSource(int n){

    int i;
    Source *tempSource = new Source[this->numSources + n]();

    for (i = 0; i < this->numSources; i++) {
        tempSource[i] = this->sources[i];
    }

    for(i = this->numSources; i < (this->numSources + n); i++){
        tempSource[i].clear();
    }

    if(this->numSources > 0){
        delete [] this->sources;
        this->sources = nullptr;
    }

    this->sources = tempSource;
    this->numSources += n;

}

void SourceLayer::deleteSources(int nSelectedSources, int *selectedSources){

    bool deleted;
    int k = 0;

    if(this->numSources > 0 && nSelectedSources > 0){
        Source *tempSources = new Source[this->numSources - nSelectedSources] ();

        for (int i = 0; i < this->numSources; i++) {
            deleted = false;

            for(int j = 0; j < nSelectedSources; j++){
                if(i == selectedSources[j]){
                    deleted = true;
                }
            }

            if(!deleted){
                tempSources[k] = this->sources[i];
                k++;
            }

        }

        delete [] this->sources;
        this->sources = tempSources;
        this->numSources -= nSelectedSources;
    }

}

void SourceLayer::clear(){

    for (int i = 0; i < MaxNChar; i++) {
        this->Name[i] = NULL;
    }

    if(this->numSources > 0){
        delete [] this->sources;
        this->sources = nullptr;
    }

    this->numSources = 0;
    this->color.setRed(1);
    this->color.setBlue(0);
    this->color.setGreen(0);
    this->idSourceType = None;

}
