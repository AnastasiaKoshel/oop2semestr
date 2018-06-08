#include "strategy.hpp"

string Walk::move()	{
    return "I can walk";
}

string Fly::move() {
    return "I can fly";
}

Unit::Unit(string name) {
    this->name = name;
}

string Unit::moveStrategy() {
    return name + ": " + strategy->move();
}

void GameUnit::setStrategy(IStrategy* strategy) {
    this->strategy = strategy;
}