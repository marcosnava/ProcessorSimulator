//
// Created by nava on 11/05/23.
//

#ifndef PROCESSORSIMULATOR_COMPONENTCONTAINER_H
#define PROCESSORSIMULATOR_COMPONENTCONTAINER_H
#include <iostream>
#include <vector>
#include "TestingComponent.h"

using namespace std;

class ComponentContainer {
public:
    void add(BaseComponent *cmp);
    void tick();
private:
    vector<BaseComponent *> components;
};


#endif //PROCESSORSIMULATOR_COMPONENTCONTAINER_H
