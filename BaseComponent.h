//
// Created by nava on 11/05/23.
//

#ifndef PROCESSORSIMULATOR_BASECOMPONENT_H
#define PROCESSORSIMULATOR_BASECOMPONENT_H
#include <iostream>
using namespace std;
class BaseComponent {
public:
    BaseComponent() = default;

    virtual void ReceiveClockPulse() {
        cout << "Tick do pai" << endl;
    };
private:

};


#endif //PROCESSORSIMULATOR_BASECOMPONENT_H
