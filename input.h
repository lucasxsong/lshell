#ifndef INPUT_H
#define INPUT_H

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

#include "baseExec.h"

using namespace std;

class input {
	protected:
		string preParse;
		vectro<string> preExec;
		baseExec* e;
	public:
		void callExit();
		void runInput();
		void parseInput();
		void parseArguments();
		string printUser();
		string printHost();
};

bool runShell = true;

#endif
