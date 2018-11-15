#include <iostream>
#include "Input.h"


int main() {
    Input* i = new Input();

    while (!i->checkExit()){
        i->runInput();
        i->parseInput();
        i->callExecute();
        i->clearInput();
    } 

    return 0;
}