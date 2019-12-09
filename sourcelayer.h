#ifndef SOURCELAYER_H
#define SOURCELAYER_H

#include <definitions.h>
#include <QColor>
#include <source.h>

class SourceLayer
{
private:
    char Name[MaxNChar + 1];
    int numSources;
    Source *sources;
    QColor color;
    int idSourceType;
public:
    SourceLayer();
    ~SourceLayer();
    void newSource(int n);
    void deleteSources(int nSelectedSources, int selectedSources[MaxNSelectedSources]);
    void clear();
    void init();
};

#endif // SOURCELAYER_H
