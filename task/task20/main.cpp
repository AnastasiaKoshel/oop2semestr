#include <iostream>
#include <string>
#include "strategy.hpp"
using namespace std;

int main(void) {
    
    Unit orc("Orc");
    Unit elf("Elf");
    Unit troll("Troll");
    
    orc.setStrategy(new Fly());
    orc.moveStrategy();
    
    troll.setStrategy(new Fly());
    troll.moveStrategy();
    
    orc.setStrategy(new Walk());
    orc.moveStrategy();
    
    elf.setStrategy(new Walk());
    elf.moveStrategy();
    
    return 0;
}