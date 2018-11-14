#ifndef __INPUT_H__
#define	__INPUT_H__

#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#include "BaseExec.h"
class baseExec;

class Input {
    protected: 
        std::string userInput;
        std::vector<std::string> parsedStrings;
        baseExec* e;
		bool exit; // true if exit
    public:
		Input();
        ~Input();
        void callExit();
		bool checkExit(); // returns true if needs to exit
        void runInput();
        void parseInput();
        void parseExecutable(); // instantiates baseExec e object w/ argList
        //void parseArguments();
        std::string returnUser();
        std::string returnHost();
};


#endif



