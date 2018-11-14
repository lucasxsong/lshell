#include <iostream>
#include "input.h"
//#include "baseExec.h"

int main() {
    input* i;
    while (i->runShell() == true) {
        i->runInput();
    }

    return 0;
}


