#pragma once
#include "animals/Herbo.h"

class Monkey : public Herbo {
public:
    Monkey(int inventory_number, int kindness)
        : Herbo("Monkey", 4, inventory_number, kindness) {}
};
