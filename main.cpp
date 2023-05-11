#include <iostream>
#include <chrono>
#include <thread>
#include "TestingComponent.h"
#include "ComponentContainer.h"
#include "AnotherComponent.h"

using namespace std;

int main() {

    ComponentContainer container;

    TestingComponent t1;
    TestingComponent t2;
    AnotherComponent a1;
    AnotherComponent a2;

    container.add(&t1);
    container.add(&a1);
    container.add(&t2);
    container.add(&a2);

    for(int i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        container.tick();
        std::cout << "--------------------------------------" << endl;
    }

    std::cout << "Finished!!!" << endl;

    return 0;
}
