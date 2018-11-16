#include <iostream>
#include "Input.h"


int main() {
    Input* i = new Input();

    while (!exitBool){
        i->runInput();
        i->clearInput();
    } 
    
    std::cout << "Exiting..." << std::endl;

    return 0;
}