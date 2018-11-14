#ifndef ___BASEEXEC_H___
#define ___BASEEXEC_H___

#include <vector>
#include "Arg.h"

class Arg;

/*****
// This is the base class for the nodes that make up the "execution" tree.
*****/
class baseNode {
    protected:
        baseNode();
    public:
        virtual void execute() = 0; 
};

/*****
// This is the base class for the connector nodes (2 CHILD NODES).
*****/
class Connector : public baseNode {
    protected:
        Connector();
        baseNode* leftChild;
        baseNode* rightChild;
    public:
        virtual void execute() = 0;
};

//*** DERIVED "CONNECTOR" CLASSES ***//

class And : public Connector {
    protected: 
        And();
        baseNode* leftChild;
        baseNode* rightChild;
    public: 
        void execute();
};

class Or : public Connector {
    protected: 
        Or();
        baseNode* leftChild;
        baseNode* rightChild;
    public: 
        void execute();
};

class SemiColon : public Connector {
    protected: 
        SemiColon();
        baseNode* leftChild;
        baseNode* rightChild;
    public: 
        void execute();
};

/*****
// This is the base class for the executable objects that will be 
// instantiated by different user input. (LEAF NODE/ONE CHILD NODES)
*****/
class baseExec : public baseNode {
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

//*** DERIVED "BASEEXEC" CLASSES ***//

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
