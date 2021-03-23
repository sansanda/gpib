#ifndef PARALLELPORT_H
#define PARALLELPORT_H

#include "./gpib/parallelCommunications/communicationPort.h"

class ParallelPort: public CommunicationsPort
{
    Q_OBJECT
public:
    ParallelPort():CommunicationsPort(){}
    ~ParallelPort(){}
};

#endif // PARALLELPORT_H
