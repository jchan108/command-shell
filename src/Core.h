#ifndef CORE_H
#define CORE_H

class Core {
    
    protected:
    // string userinput;
    
    public:
     string userinput; 
    //constructors & destructors
    Core(){};
    ~Core(){};
    
    //pure virtual functions
    virtual void read() = 0;
    virtual void parse() = 0;
    virtual void execute() = 0;
    
};

#endif