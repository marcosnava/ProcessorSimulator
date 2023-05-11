//
// Created by nava on 11/05/23.
//

#ifndef PROCESSORSIMULATOR_TESTINGCOMPONENT_H
#define PROCESSORSIMULATOR_TESTINGCOMPONENT_H
#include "BaseComponent.h"

class TestingComponent: public BaseComponent{
public:
    TestingComponent() = default;
    void ReceiveClockPulse() override;
};


#endif //PROCESSORSIMULATOR_TESTINGCOMPONENT_H
