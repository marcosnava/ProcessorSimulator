//
// Created by nava on 11/05/23.
//

#ifndef PROCESSORSIMULATOR_ANOTHERCOMPONENT_H
#define PROCESSORSIMULATOR_ANOTHERCOMPONENT_H


#include "BaseComponent.h"

class AnotherComponent: public BaseComponent {
public:
    AnotherComponent() = default;
    void ReceiveClockPulse() override;
};


#endif //PROCESSORSIMULATOR_ANOTHERCOMPONENT_H
