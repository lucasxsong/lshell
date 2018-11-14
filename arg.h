#ifndef ___ARG_H____
#define ___ARG_H____

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



#endif 