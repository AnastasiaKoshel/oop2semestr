#ifndef strategy_hpp
#define strategy_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class IStrategy {
public:
    virtual string move() = 0;
};

class Walk : public IStrategy {
public:
    string move();
};

class Fly : public IStrategy {
public:
    string move();
};

class GameUnit
{
protected:
    IStrategy* strategy;
public:
    virtual string moveStrategy() = 0;
    virtual void setStrategy(IStrategy*);
};

class Unit : public GameUnit {
public:
    string name;
    Unit(string name);
    string moveStrategy();
};


#endif /* strategy_hpp */