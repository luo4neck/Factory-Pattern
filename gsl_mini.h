#include<iostream>
#include<gsl/gsl_multimin.h>
#include<stdlib.h>

class Sim 
{
public: 
virtual void create_simplex() {}
virtual void create_simplex2() {}
virtual void create_simplex2rand() {}

//FILE *p;
};

class simplex: public Sim
{
    public:
    simplex()
    {
    
    
    }
};

class simplex2: public Sim
{
    public:
    simplex2()
    {}
};

class simplex2rand: public Sim
{
    public:
    simplex2rand()
    {}
};

class MiniFactory
{
    Sim* create_simplex() {return new simplex(); }
    Sim* create_simplex2() {return new simplex2(); }
    Sim* create_simplex2rand() {return new simplex2rand(); }

    public:
    Sim* operator() (const short Nform)
    {
        if(Nform == 1) return create_simplex();
        else if(Nform == 2) return create_simplex2();
        else return create_simplex2rand();
    }
};
