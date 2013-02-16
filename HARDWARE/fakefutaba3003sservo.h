#ifndef FAKEFUTABA3003SSERVO_H
#define FAKEFUTABA3003SSERVO_H

#include "basicservo.h"

class FakeFutaba3003sServo : public BasicServo
{
public:
    FakeFutaba3003sServo();

protected:
    virtual Component build();
};

#endif // FAKEFUTABA3003SSERVO_H
