#ifndef ___BASEEXEC_H___
#define ___BASEEXEC_H___

#include <vector>
#include <iostream>
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
        virtual void setLeft(baseNode* leftChild) = 0;
        virtual void setRight(baseNode* rightChild) = 0;
        virtual baseNode* getRight() = 0;
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
        virtual void setLeft(baseNode* leftChild) = 0;
        virtual void setRight(baseNode* rightChild) = 0;
        virtual void execute() = 0;
        virtual baseNode* getRight() = 0;
};

//*** DERIVED "CONNECTOR" CLASSES ***//

class And : public Connector {
    protected: 
        And() {
	    leftChild = NULL;
	    rightChild = NULL;
	}
        baseNode* leftChild;
        baseNode* rightChild;
    public: 
        void setLeft(baseNode* leftChild);
        void setRight(baseNode* rightChild);
        void execute();
        baseNode* getRight();
};

class Or : public Connector {
    protected: 
        Or() {
	    leftChild = NULL;
	    rightChild = NULL;
	}
        baseNode* leftChild;
        baseNode* rightChild;
    public: 
        void setLeft(baseNode* leftChild);
        void setRight(baseNode* rightChild);
        void execute();
        baseNode* getRight();
};

class SemiColon : public Connector {
    protected: 
        SemiColon() {
	    leftChild = NULL;
	    rightChild = NULL;
	}
        baseNode* leftChild;
        baseNode* rightChild;
    public: 
        void execute() {
	    leftChild->execute();
	    rightChild->execute();
	}
        void setLeft(baseNode* leftChild);
        void setRight(baseNode* rightChild);
        baseNode* getRight();
};

/*****
// This is the base class for the executable objects that will be 
// instantiated by different user input. (LEAF NODE/ONE CHILD NODES)
*****/
class baseExec : public baseNode {
    protected:
        std::string comment;
        std::vector<Arg*> a;
    public:
        // Function for adding arguments to vector a with a string passed in
        virtual void addArg(std::vector<std::string> arg) = 0;
        baseExec() { }
        virtual void execute() = 0;

};

/*****
// This opens up the options so that different executable objects can be created
// and executed with respect to connectors
*****/

//*** DERIVED "BASEEXEC" CLASSES ***//

// tag: string variable to be returned back to user
class echo : public baseExec {
    protected:
        std::vector<Arg*> a;
    public: 
        void addArg(std::vector<std::string> arg);
        void execute(); //prints arguments on newline
        echo() {};
        echo(std::string input);
};

// tag: -a just to print all files (hidden too)
class ls : public baseExec {
    protected:
        std::vector<Arg*> a;
    public:
        void addArg(std::vector<std::string> arg);
	void execute(); //print files in directory
        ls() {};
	ls(std::string input);
};

// tag: filename/directory name
class cd : public baseExec {
    protected:
        std::vector<Arg*> a;
    public:
        void addArg(std::vector<std::string> arg);
        cd() {};
	cd(std::string input);
	void execute(); //change directory based on argument passed in
};

// tag: directory name
class mkdir : public baseExec {
    protected:
        std::vector<Arg*> a;
    public:
        void addArg(std::vector<std::string> arg);
        mkdir() {};
	mkdir(std::string input);
	void execute();
};

// created when user input does not match a function
class error : public baseExec { 
    protected:
        std::vector<Arg*> a;
    public:
        void addArg(std::vector<std::string> arg);
        error() {};
	error(std::string input);
	void execute() {
            std::cout << "error" << std::endl;
        }
};
#endif
