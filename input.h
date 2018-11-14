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
        std::vector<std::vector<std::string> > parsedExec; // this vector holds the parsed string w/o spaces
        std::vector<std::string> parsedStrings; // these two vectors are just to help in storing 
        std::vector<std::string> connectors;    // the data to create the executable tree
        baseNode* head; // pointer to top of executable tree
		bool exit; // true if exit
    public:
		Input();
        ~Input();
        Input(std::string userString);
        void clearInput();
        std::vector<std::string> returnStrings();
        std::vector<std::string> returnConnectors();
        void callExit();
		bool checkExit(); // returns true if needs to exit
        void runInput();
        void parseInput();
        std::vector<std::string> parseSpaces(std::string withSpaces); // helper function to remove spaces from withSpaces input
        void parseConnectors();
        void makeExecutableTree(); // instantiates baseExec e object w/ argList
        //void parseArguments();
        std::string returnUser();
        std::string returnHost();
};


#endif



