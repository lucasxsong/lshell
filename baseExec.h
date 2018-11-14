#ifndef ___BASEEXEC_H___
#define ___BASEEXEC_H___

#include <vector>
#include "arg.h"

/*****
// This is the base class for the executable objects that will be 
// instantiated by different user input.
*****/
class arg;

class baseExec {
    protected:
        baseExec() { }

        std::vector<arg*> a;
    public:
        virtual void execute() = 0;

};

/*****
// This opens up the options so that different executable objects can be created
// and executed with respect to connectors
*****/

//*** DERIVED CLASSES ***//

class echo : public baseExec {
    protected:
        echo() {};
        echo(std::string input);
    public: 
        void execute();
};

#endif