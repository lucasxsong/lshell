#ifndef ___BASEEXEC_H___
#define ___BASEEXEC_H___
#include "Input.h"

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "Arg.h"

class Arg;
extern bool exitBool;

/*****
// This is the base class for the nodes that make up the "execution" tree.
*****/
class baseNode {
    protected:
        baseNode* leftChild;
        baseNode* rightChild;
    public:
        baseNode() {
            leftChild = NULL;
            rightChild = NULL;
        }
        ~baseNode() {}
        virtual bool execute() { // returns true if function calls, false if not
            return true;
        }
        virtual void setLeft(baseNode* leftChild) {
            return;
        }
        virtual void setRight(baseNode* rightChild) {
            return;
        }
        virtual baseNode* getRight() {
            return rightChild;
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
        bool execute() {
            if (leftChild->execute()) {
                return rightChild->execute();
            }
            return false;
        }
};

class Or : public Connector {
    public: 
        Or() {
	        leftChild = NULL;
	        rightChild = NULL;
	    }
        bool execute() {
            if (!leftChild->execute()) {
                return rightChild->execute();
            }
            return true;
        }
};

class SemiColon : public Connector {
    public: 
        SemiColon() {
	        leftChild = NULL;
	        rightChild = NULL;
	    }
        bool execute() {
	        leftChild->execute();
            rightChild->execute();
            return true;
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
    public:
        // Function for adding arguments to vector a with a string passed in
        void addArg(std::vector<std::string> arg) {
            for (int i = 0; i < arg.size(); ++i) {
                a.push_back(arg.at(i));
            }
            return;
        }
        virtual bool execute() {
            pid_t pid;
            
            if ((pid = fork()) < 0) {
                perror("ERROR: forking child process failed");
                return false;
            }
            return true;
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
        std::string userInput;
    public: 
        echo() {}
        void addUserInput(std::string userInput) {
            this->userInput = userInput;
        }

        //prints arguments on newline 
        bool execute() {
                for (int i = 1; i < a.size(); i++) {
                    std::cout << a.at(i) << " ";
                }

                std::cout << std::endl;
                return true;
        }
        
};

// tag: -a just to print all files (hidden too)
class ls : public baseExec {
    protected:

    public:
        ls() {}

	    bool execute() {
            return true; //if commands executed
        } //print files in directory
};

// tag: filename/directory name
class cd : public baseExec {
    protected:
        
    public:
        cd() {}

        bool execute() {
            return true;
        } //change directory based on argument passed in

};

// tag: directory name
class mkdir : public baseExec {
    protected:

    public:
        mkdir() {}

        bool execute() {
            return true;
        }    
};

// created when user input does not match a function
class error : public baseExec { 
    protected:
       
    public:
        error() {}

        bool execute() {
            std::cout << "Rshell: " << a.at(0) << ": command not found"  << std::endl;
            return false;
        }
        
};

class exitCall : public baseExec {
    protected:

    public: 
        exitCall() {}
        bool execute() {
            exitBool = true;
            return true;
        }
};
#endif
