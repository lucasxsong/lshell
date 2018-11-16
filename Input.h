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
        std::vector<std::string> connectors;
        baseNode* head; // pointer to top of executable tree
		bool exit; // true if exit
    public:
		Input();
        ~Input();
        Input(std::string userString);
        std::vector<std::string> returnStrings();
        std::vector<std::string> returnConnectors();
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



