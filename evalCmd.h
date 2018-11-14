#ifndef ___EVALCMD_H___
#define ___EVALCMD_H___

#include <vector>
#include "BaseExec.h"
#include "Arg.h"

class baseExec;

/******
// Evalcmd is a decorator class that will combine the Exec command e
// with the Arglist a to return the series of functions that need to be executed
******/
class Evalcmd {
    protected: 
        baseNode* e; //points to specific executable object
    public: 
        Evalcmd();

        // This command evaluates the command with e and its submember a. Returns 
        // true if command successfully completed, false if missing parameters, etc
        // *****
        // I think we can remove this function and use the returned int pid value
        // from calling fork() to check whether an executable has failed.
        // Based off of fork videos I think we can follow these conditions:
        // (1) If getpid() returns a positive value, it indicates the current process
        // is the parent process.
        // (2) If getpid() returns a zero, it indicates the current process is the
        // child process and is running successfully.
        // (3) If getpid() returns a negative value, it indicates that the current
        // process has failed.
        bool EvaluateCommand();
};

#endif
