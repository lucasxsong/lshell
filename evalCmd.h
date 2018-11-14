#ifndef ___EVALCMD_H___
#define ___EVALCMD_H___

#include <vector>
#include "baseExec.h"

class baseExec,

/******
// Evalcmd is a decorater class that will combine the Exec command e
// with the Arglist a to return the series of functions that need to be executed
******/
class Evalcmd {
    protected: 
        baseExec* e;
    public: 
        Evalcmd();

        // This command evaluates the commond with e and its submember a. Returns 
        // true if command successfully completed, false if missing parameters, etc
        bool EvaluateCommand();
};

#endif