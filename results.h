#ifndef RESULTS_H
#define RESULTS_H

#include <definitions.h>

class Results
{
private:
    int receiver, irDiscretization;
    int stopTime[NumberBands + 1];
    float *hybridIR[NumberBands + 1];
    float *specularIR[NumberBands + 1];
    float *diffuseIR[NumberBands + 1];
    float *decayCurve[NumberBands + 1];
    int numQAP;
    float *qltyAcouParam[NumberBands + 1];
public:
    Results();
    ~Results();
    void newData();
    void clear();
    void init();
};

#endif // RESULTS_H
