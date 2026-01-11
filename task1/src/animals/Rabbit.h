#pragma once
#include "animals/Herbo.h"

class Rabbit : public Herbo {
public:
    Rabbit(int inventory_number, int kindness)
        : Herbo("Rabbit", 2, inventory_number, kindness) {}
};
