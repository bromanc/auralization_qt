#include "receiverlayer.h"

ReceiverLayer::ReceiverLayer() {}

ReceiverLayer::~ReceiverLayer() {}

void ReceiverLayer::init(){

    for (int i = 0; i < MaxNChar + 1; i++) {
        this->Name[i] = NULL;
    }

    this->Name[0] = 'R';
    this->Name[1] = '.';
    this->Name[2] = ' ';
    this->Name[3] = 'L';
    this->Name[4] = 'a';
    this->Name[5] = 'y';
    this->Name[6] = 'e';
    this->Name[7] = 'r';
    this->Name[8] = ' ';
    this->Name[9] = '#';

    if(this->numReceivers > 0){
        delete [] this->receivers;
        this->receivers = nullptr;
    }else{
        this->receivers = nullptr;
    }

    this->numReceivers = 0;

}

void ReceiverLayer::clear(){

    for (int i = 0; i < MaxNChar; i++) {
        this->Name[i] = NULL;
    }

    if(this->numReceivers > 0){
        delete [] this->receivers;
        this->receivers = nullptr;
    }

    this->numReceivers = 0;

}

void ReceiverLayer::deleteReceivers(int nSelectedReceivers, int *selectedReceiver){

    bool deleted;
    int k = 0;

    if(this->numReceivers > 0 && nSelectedReceivers > 0){
        Receiver *tempSources = new Receiver[this->numReceivers - nSelectedReceivers] ();

        for (int i = 0; i < this->numReceivers; i++) {
            deleted = false;

            for(int j = 0; j < nSelectedReceivers; j++){
                if(i == selectedReceiver[j]){
                    deleted = true;
                }
            }

            if(!deleted){
                tempSources[k] = this->receivers[i];
                k++;
            }

        }

        delete [] this->receivers;
        this->receivers = tempSources;
        this->numReceivers -= nSelectedReceivers;
    }

}

void ReceiverLayer::newReceiver(int n){

    int i;
    Receiver *tempReceiver = new Receiver[this->numReceivers + n]();

    for (i = 0; i < this->numReceivers; i++) {
        tempReceiver[i] = this->receivers[i];
    }

    for(i = this->numReceivers; i < (this->numReceivers + n); i++){
        tempReceiver[i].clear();
    }

    if(this->numReceivers > 0){
        delete [] this->receivers;
        this->receivers = nullptr;
    }

    this->receivers = tempReceiver;
    this->numReceivers += n;

}
