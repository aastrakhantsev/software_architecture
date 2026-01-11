#pragma once
#include "animals/Predator.h"

class Wolf : public Predator {
public:
    Wolf(int inventory_number)
        : Predator("Wolf", 7, inventory_number) {}
};
