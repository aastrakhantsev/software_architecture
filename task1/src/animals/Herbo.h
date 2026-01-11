#pragma once
#include "animals/Animal.h"

class Herbo : public Animal {
protected:
    int kindness;

public:
    Herbo(const std::string& name,
          int food,
          int number,
          int kindness)
        : Animal(name, food, number),
          kindness(kindness) {}

    bool is_kind() const {
        return kindness > 5;
    }
};
