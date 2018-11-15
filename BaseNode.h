#ifndef ___BASEEXEC_H___
#define ___BASEEXEC_H___

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "Arg.h"

class Arg;

/*****
// This is the base class for the nodes that make up the "execution" tree.
*****/
class baseNode {
    public:
        baseNode() {}
        ~baseNode() {}
        virtual void execute() {
            return;
        }
        virtual void setLeft(baseNode* leftChild) {
            return;
        }
        virtual void setRight(baseNode* rightChild) {
            return;
        }
        virtual baseNode* getRight() {
            baseNode* b = new baseNode();
            return b;
        }
};

/*****
// This is the base class for the connector nodes (2 CHILD NODES).
*****/
class Connector : public baseNode {
    protected:
        baseNode* leftChild;
        baseNode* rightChild;
    public:
        Connector() {}
        void setLeft(baseNode* leftChild) {
            this->leftChild = leftChild;
            return;
        }
        void setRight(baseNode* rightChild) {
            this->rightChild = rightChild;
            return;
        }
        baseNode* getRight() {
            return rightChild;
        }
};

//*** DERIVED "CONNECTOR" CLASSES ***//

class And : public Connector {
    public: 
        And() {
	        leftChild = NULL;
	        rightChild = NULL;
	    }
        void execute() {
            leftChild->execute();
            rightChild->execute();
            return;
        }
};

class Or : public Connector {
    public: 
        Or() {
	        leftChild = NULL;
	        rightChild = NULL;
	    }
        void execute() {
            leftChild->execute();
            rightChild->execute();
            return;
        }
};

class SemiColon : public Connector {
    public: 
        SemiColon() {
	        leftChild = NULL;
	        rightChild = NULL;
	    }
        void execute() {
	        leftChild->execute();
	        rightChild->execute();
            return;
	    }
};

/*****
// This is the base class for the executable objects that will be 
// instantiated by different user input. (LEAF NODE/ONE CHILD NODES)
*****/
class baseExec : public baseNode {
    protected:
        std::string comment;
        std::vector<std::string> a;
        std::string input;
    public:
        // Function for adding arguments to vector a with a string passed in
        void addArg(std::vector<std::string> arg) {
            a = arg;
            return;
        }
        baseExec() { }
};

/*****
// This opens up the options so that different executable objects can be created
// and executed with respect to connectors
*****/

//*** DERIVED "BASEEXEC" CLASSES ***//

// tag: string variable to be returned back to user
class echo : public baseExec {
    protected:
        char* fileName;
    public: 
        echo() {}
        echo(std::string input) {
            this->input = input;
        }
        void addArg(std::vector<std::string> arg) {
            a = arg;
        }

        //prints arguments on newline 
        void execute() {
                for (int i = 0; i < a.size(); ++i) {
                    std::cout << a.at(i) << " ";
                }
                std::cout << std::endl;
                return;
        }
        
};

// tag: -a just to print all files (hidden too)
class ls : public baseExec {
    protected:

    public:
        ls() {}
	    ls(std::string input) {
            this->input = input;
        }

	    void execute() {
            return;
        } //print files in directory
};

// tag: filename/directory name
class cd : public baseExec {
    protected:
        std::string input;
        std::vector<std::string> a;
    public:
        cd() {}
	    cd(std::string input) {
            this->input = input;
        }

        void execute() {
            return;
        } //change directory based on argument passed in

};

// tag: directory name
class mkdir : public baseExec {
    protected:
        std::string input;
        std::vector<std::string> a;
    public:
        mkdir() {}
	    mkdir(std::string input) {
            this->input = input;
        }

        void execute() {
            return;
        }    
};

// created when user input does not match a function
class error : public baseExec { 
    protected:
        std::string input;
        std::vector<std::string> a;
    public:
        error() {}
	    error(std::string input) {
            this->input = input;
        }

        void execute() {
            std::cout << "error" << std::endl;
            return;
        }
        
};
#endif
