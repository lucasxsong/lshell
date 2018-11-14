#ifndef ___BASEEXEC_H___
#define ___BASEEXEC_H___

#include <vector>
#include "arg.h"

/*****
// This is the base class for the executable objects that will be 
// instantiated by different user input.
*****/
class Arg;

class baseExec {
    protected:
        baseExec() { }
        std::vector<Arg*> a;
    public:
        virtual void execute() = 0;

};

class echo : public: baseExec {
    protected:
        echo() {};
        echo(std::string input);
    public: 
        void execute();
};

/*****
// This opens up the options so that different executable objects can be created
// and executed with respect to connectors
*****/

//*** DERIVED CLASSES ***//

#endif