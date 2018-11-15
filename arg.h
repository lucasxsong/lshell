#ifndef ___ARG_H____
#define ___ARG_H____

#include <vector>

/*****
// This is the base class for arguments. Flags, text, and comments should 
// inherit from this class 
*****/

class Arg {
    protected:
    	
    public:
        Arg() {}
        virtual void execute() = 0;
};

/*****
// This opens up the options so that tags/text/comments can be queued up
// to be executed by evalCmd
*****/

//*** Derived Classes ***//

class fileName : public Arg { // class for filename string
    protected:
        
    public:
};

class a : public Arg { // class for tag -a 
    protected:
    
    public: 
    
};

#endif 
