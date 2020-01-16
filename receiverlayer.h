#ifndef RECEIVERLAYER_H
#define RECEIVERLAYER_H

#include <receiver.h>

class ReceiverLayer
{
private:
    char Name[MaxNChar + 1];
    int numReceivers;
    Receiver *receivers;
public:
    ReceiverLayer();
    ~ReceiverLayer();
    void newReceiver(int n);
    void deleteReceivers(int nSelectedReceivers, int selectedReceiver[MaxNSelectedReceivers]);
    void clear();
    void init();
};

#endif // RECEIVERLAYER_H
