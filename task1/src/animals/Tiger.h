#pragma once
#include "animals/Predator.h"

class Tiger : public Predator {
public:
    Tiger(int inventory_number)
        : Predator("Tiger", 10, inventory_number) {}
};
