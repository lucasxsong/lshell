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
#include <fcntl.h>

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
        // The base execute function has been changed to allow for the input/output redirection to utilize the 
        // same interface as the baseNode
        virtual bool execute(int in, int out) { // returns true if function calls, false if not
            return true;
        }
        virtual void setLeft(baseNode* leftChild) {
            return;
        }
        virtual void setRight(baseNode* rightChild) {
            return;
        }
        virtual baseNode* getLeft() {
            return leftChild;
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

        virtual std::string get_cmd() {
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
            return "Connector";
        };
        virtual std::string returnCheck() {
            return "con";
        }
};

//*** DERIVED "CONNECTOR" CLASSES ***//

class And : public Connector {
    public: 
        And() {
	        leftChild = NULL;
	        rightChild = NULL;
	    }
        bool execute(int in, int out) {
            if (leftChild->execute(in, out)) {
                return rightChild->execute(in, out);
            }
            return false;
        }
        std::string returnType() {
            return "&&";
        }
        std::string returnCheck() {
            return "and";
        }
};

class Or : public Connector {
    public: 
        Or() {
	        leftChild = NULL;
	        rightChild = NULL;
	    }
        bool execute(int in, int out) {
            if (!leftChild->execute(in, out)) {
                return rightChild->execute(in, out);
            }
            return true;
        }
        std::string returnType() {
            return "||";
        }
        std::string returnCheck() {
            return "or";
        }
};

class SemiColon : public Connector {
    public: 
        SemiColon() {
	        leftChild = NULL;
	        rightChild = NULL;
	    }
        bool execute(int in, int out) {
	        leftChild->execute(in, out);
            rightChild->execute(in, out);
            return true;
	    }
        std::string returnType() {
            return ";";
        }
        std::string returnCheck() {
            return "semi";
        }
};

/*****
// ADDITIONS FOR ASSN 4
*****/

class Pipe : public Connector {
    public:
        Pipe() {
        leftChild = NULL;
        rightChild = NULL;
        }
         // These are just filler executes, need to be redone for redirection
        bool execute(int in, int out) {
            int fds[2];
            if (pipe(fds) == -1) {
                perror("pipe");
                return false;
            }
            if (!leftChild->execute(in, fds[1])) {
                return false;
            }
            close(fds[1]);

            if(!rightChild->execute(fds[0], out)) {
                return false;
            }
            close(fds[0]);
            return true;
        }
        std::string returnType() {
            return "|";
        }
        std::string returnCheck() {
            return "pipe";
        }
};

class OOverwrite : public Connector { // SYMBOL : >
    public: 
        OOverwrite() {
            rightChild = NULL;
            leftChild = NULL;
        }
        // These are just filler executes, need to be redone for redirection
        bool execute(int in, int out) {
            std::string ofile = rightChild->get_cmd();
            out = open(ofile.c_str(), O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

            return leftChild->execute(0,out);
        }
        std::string returnType () {
            return ">";
        }
        std::string returnCheck() {
            return "OOverWrite";
        }
};



class OConcatenate : public Connector { // SYMBOL : >>
    public: 
        OConcatenate() {
            rightChild = NULL;
            leftChild = NULL;
        }
        // These are just filler executes, need to be redone for redirection
        bool execute(int in, int out) {
            std::string ofile = rightChild->get_cmd();
            out = open(ofile.c_str(), O_WRONLY| O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

            return leftChild->execute(0,out);
        }
        std::string returnType() {
            return ">>";
        }
        std::string returnCheck() {
            return "OConcatenate";
        }
};

class IOverwrite : public Connector { // SYMBOL : <
    public: 
        IOverwrite() {
            rightChild = NULL;
            leftChild = NULL;
        }
        
        bool execute(int in, int out) {
            std::string file;
            file = rightChild->get_cmd();
            in = open(file.c_str(), O_RDONLY);
            return leftChild->execute(in,1);
        }
        std::string returnType() {
            return "<";
        }
        std::string returnCheck() {
            return "IOverwrite";
        }
};


/*****
// ADDITIONS FOR ASSN 4
*****/

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

        std::string get_cmd() {
            return a.at(0);
        }

        virtual bool execute(int in, int out) {
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
                
                if (dup2(in, 0) == -1) {
                    perror("dup2");
                    return false;
                }
                if (dup2(out,1) == -1) {
                    perror("dup2");
                    return false;
                }
                if (execvp(arg[0], arg.data()) == -1) {
                    perror("execvp() failed");
                    run = false;
                    //***
                    // std::cout << "Rshell: " << a.at(0) << ": command not found"  << std::endl;
                    // error* e = new baseExec();
                    // e->addArg(exec);
                    // e->execute(0, 0);
                    //***
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
            return a.at(0);
        }
        baseExec() { }

        virtual std::string returnCheck() {
            //using string comment as temporary fix for errorTest
            //mimicked error class's returnCheck()
            comment = "Rshell: ";
            comment += a.at(0);
            comment += ": command not found\n";
            return comment;
        }
};

/*****
// This opens up the options so that different executable objects can be created
// and executed with respect to connectors
*****/

//*** DERIVED "BASEEXEC" CLASSES ***//

// ***** ECHO CLASS NO LONGER NEEDED AS OF ASSN4 ******
// tag: string variable to be returned back to user
// class echo : public baseExec {
//     protected:
//         std::string userInput;
//         std::string echoReturn; //stores a string of what echo returns
//     public: 
//         echo() {}
//         void addUserInput(std::string userInput) {
//             this->userInput = userInput;
//         }

//         //prints arguments on newline 
//         bool execute(int in, int out) {
//                 for (int i = 1; i < a.size(); i++) {
//                     std::cout << a.at(i) << " ";
//                 }

//                 std::cout << std::endl;
//                 return true;
//         }
//         std::string returnType() {
//             return "echo";
//         }
//         //used for test case
//         std::string returnCheck() {
//             std::string str = "";
//             for (int i = 1; i < a.size(); i++) {
//                 str = a.at(i);
//                 echoReturn += str;
//                 echoReturn += " ";
//             }

//             return echoReturn;
//         }
        
// };

// created when user input does not match a function
class error : public baseExec { 
    protected:
       std::string errorReturn;
    public:
        error() {
            leftChild = NULL;
            rightChild = NULL;
        }

        bool execute(int in, int out) {
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
        bool execute(int in, int out) {
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
        bool execute(int in, int out) {
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

/*****
// This is the parenthesis baseClass, which inherits from the baseExec class, but also has 2 children
// ***MARKED AS RESOLVED*** 
// The function or potentially the program as a whole eventually needs a solution to switch out the
// Par node with the connector so that the execute function can properly iterate through the tree
// ***MARKED AS RESOLVED***
*****/
class Par : public baseExec {
    protected:
        std::string subString;

    public:
        Par() {
            leftChild = NULL;
            rightChild = NULL;
        }

        void setSubString(std::string s) {
            subString = s;
        }
        bool execute(int in, int out) {
            
            return true;
            // The execute function of par will look through the substring and see if there are any parenthesis, if not
            // it will just simply create the two baseExec objects based on makeExecutableTree and execute them
            // ***FIXED***
            // The execute function will not be called, the par object is simply a step in recursively calling parseInput on
            // the substring data member
            // ***FIXED***
        }
        std::string returnType() {
            return "()";
        }
        std::string returnCheck() {
            return "working";
        }
};

#endif
