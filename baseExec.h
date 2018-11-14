#ifndef ___BASEEXEC_H___
#define ___BASEEXEC_H___

#include <vector>
#include "Arg.h"

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
        void execute(); //prints arguments on newline
};

class ls : public baseExec {
    protected:
	ls() {};
	ls(std::string input);
    public:
	void execute(); //print files in directory
};

class cd : public baseExec {
    protected:
	cd() {};
	cd(std::string input);
    public:
	void execute(); //change directory based on argument passed in
};

class mkdir : public baseExec {
    protected:
	mkdir() {};
	mkdir(std::string input);
    public:
	void execute();
};

#endif
