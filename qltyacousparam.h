#ifndef QLTYACOUSPARAM_H
#define QLTYACOUSPARAM_H

#include <definitions.h>

class QltyAcousParam
{
private:
    int numSources, numReceivers;
    float **T30, **EDT, **D50, **C80;
    float **TS, **G, **LF, **LFC;
    float **D80, **C50, **LG, **ST1;
public:
    QltyAcousParam();
    ~QltyAcousParam();
    bool createQlyParamMat(int sources, int receivers);
    bool deleteQltyParamMat();
};

#endif // QLTYACOUSPARAM_H
