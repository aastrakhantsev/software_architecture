#pragma once
#include "animals/Animal.h"

class Predator : public Animal {
public:
    Predator(const std::string& name, int food, int number)
        : Animal(name, food, number) {}
};
