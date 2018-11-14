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

#include "BaseNode.h"
class baseNode;

class Input {
    protected: 
        std::string userInput;
        std::vector<std::string> parsedStrings;
        baseNode* head; // pointer to top of executable tree
		bool exit; // true if exit
    public:
		Input();
        ~Input();
        void callExit();
		bool checkExit(); // returns true if needs to exit
        void runInput();
        void parseInput();
        void parseExecutableTree(); // instantiates baseExec e object w/ argList
        //void parseArguments();
        std::string returnUser();
        std::string returnHost();
};


#endif



