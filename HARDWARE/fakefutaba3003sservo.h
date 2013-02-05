#ifndef FAKEFUTABA3003SSERVO_H
#define FAKEFUTABA3003SSERVO_H

#include "basic_servo.h"

class FakeFutaba3003sServo : public Basic_Servo
{
public:
    FakeFutaba3003sServo();

protected:
    virtual Component build();
};

#endif // FAKEFUTABA3003SSERVO_H
