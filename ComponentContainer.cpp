//
// Created by nava on 11/05/23.
//

#include "ComponentContainer.h"

void ComponentContainer::add(BaseComponent *cmp) {
    components.push_back(cmp);
}

void ComponentContainer::tick() {
    for(auto component : components)
    {
        component->ReceiveClockPulse();
    }
}