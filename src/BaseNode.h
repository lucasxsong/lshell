#ifndef ___BASEEXEC_H___
#define ___BASEEXEC_H___
#include "Input.h"

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

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
        virtual std::string returnType() {
            return "";
        }
        virtual std::string returnCheck() { //helper function for test cases
            return "";
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
        virtual std::string returnType() {
            return "";
        };
        virtual std::string returnCheck() {
            return "";
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
        std::string returnType() {
            return "&&";
        }
        std::string returnCheck() {
            return "";
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
        std::string returnType() {
            return "||";
        }
        std::string returnCheck() {
            return "";
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
        std::string returnType() {
            return ";";
        }
        std::string returnCheck() {
            return "";
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
            bool comment = false;
            int commentIndex;
            for (int i = 0; i < arg.size(); ++i) {
                if (arg.at(i).at(0) == '#') {
                    comment = true;
                    commentIndex = i;
                }
                a.push_back(arg.at(i));
            }
            // This is a hack to remove comments from the arglist. NEEDS TO BE FIXED
            if (comment) {
                a.clear();
                for (int i = 0; i < commentIndex; ++i) {
                    a.push_back(arg.at(i));
                }
            }
            return;
        }

        virtual bool execute() {
            pid_t pid = fork();
            int status;
            bool run = true;
            std::string exec = a.at(0);
            std::vector<char *> arg(a.size() + 1);
            for (std::size_t i = 0; i != a.size(); ++i) {
                arg[i] = &a[i][0];
            }
            
            if (pid < 0) {
                perror("fork() failed");
                return false;
            }

            else if (pid == 0) {
                
                if (execvp(arg[0], arg.data()) == -1) {
                    perror("execvp() failed");
                    run = false;
                    exit(1);
                }
            }
            else if (pid > 0) {
                if (waitpid(pid, &status, 0) == -1) {
                    perror("waitpid() failed");
                }
                if(WEXITSTATUS(status) != 0) {
                    run = false;
                }
            }
            return run;
        }
        virtual std::string returnType() {
            return "";
        }
        baseExec() { }

        virtual std::string returnCheck() {
            return "";
        }
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
        std::string echoReturn; //stores a string of what echo returns
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
        std::string returnType() {
            return "echo";
        }
        //used for test case
        std::string returnCheck() {
            std::string str = "";
            for (int i = 1; i < a.size(); i++) {
                str = a.at(i);
                echoReturn += str;
                echoReturn += " ";
            }

            return echoReturn;
        }
        
};

// created when user input does not match a function
class error : public baseExec { 
    protected:
       std::string errorReturn;
    public:
        error() {
            leftChild = NULL;
            rightChild = NULL;
        }

        bool execute() {
            std::cout << "Rshell: " << a.at(0) << ": command not found"  << std::endl;
            return false;
        }
        std::string returnType() {
            return "error";
        }
        std::string returnCheck() {
            errorReturn = "Rshell: ";
            errorReturn += a.at(0);
            errorReturn += ": command not found\n";
            return errorReturn;
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
        std::string returnType() {
            return "exit";
        }
        std::string returnCheck() {
            return "working";
        }
};

/*****
// Adding implementation for the test executable, for assignment 3
// This function, as per assignment 3 guidelines will return TRUE if the 
// test succeeds and false if it fails (checking file paths)
// TO DO: still need to factor in how [] can call test exec instantiation
*****/

class test : public baseExec {
    protected:
        bool dashE;
        bool dashF;
        bool dashD;
        std::string filePath;
    public: 
        test() {
            dashE = true; // checks if the file/directory exists (used by default)
            dashF = false; // checks if the file/directory exists and is a regular file
            dashD = false; // checks if the file/directory exists and is a regular file
        }
        bool execute() {
            // execute function should check if there are any flags in the arglist
            // if there are not, move on to check to see if the file path exists using stat()
            
            // first iterate through the a list and check for flags and filename
            // throw errors accordingly

            for (int i = 0; i < a.size(); ++i) {
                if (a.at(i).at(0) == '-') {
                    if (a.at(i) == "-e") {
                        dashE = true;
                    }
                    else if (a.at(i) == "-f") {
                        dashF = true;
                        dashE = false;
                    }
                    else if (a.at(i) == "-d") {
                        dashD = true;
                        dashE = false;
                    }
                    else {
                        printf ("tag not found, please use -e (check if path exists), -f (check if file exists), or -d (check if directory exists");
                        std::cout << std::endl;
                    }
                }
                else {
                    filePath = a.at(i);
                }
            }
            // use stat to see if the file paths exist and use flags accordingly (no flags is e)
        

            if (dashE) {
                struct stat buffer;
                if (stat (filePath.c_str(), &buffer) == 0) {
                    std::cout << "(True)" << std::endl;
                    return true;
                }
                else {
                    std::cout << "(False)" << std::endl;
                    return false;
                }
                
                // executes stat based on -e tag
            }
            
            else if (dashF) {
                // executes stat based on -f tag
                struct stat buffer;
                if (stat (filePath.c_str(), &buffer) == 0) {
                    if (S_ISREG(buffer.st_mode)) {
                        std::cout << "(True)" << std::endl;
                        return true;
                    }
                    else {
                        std::cout << "(False)" << std::endl;
                        return false;
                    }
                }
                else {
                    std::cout << "(False)" << std::endl;
                    return false;
                }
            }
            
            else if (dashD) {
                // executes stat based on -d tag
                struct stat buffer;
                if (stat (filePath.c_str(), &buffer) == 0) {
                    if (S_ISDIR(buffer.st_mode)) {
                        std::cout << "(True)" << std::endl;
                        return true;
                    }
                    else {
                        std::cout << "(False)" << std::endl;
                        return false;
                    }
                }
                else {
                    std::cout << "(False)" << std::endl;
                    return false;
                }
            }

            return false;    
                
        }

        std::string returnCheck() {
            return "false";
        }

};

#endif
