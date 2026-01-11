#pragma once
#include "inventory/Thing.h"

class Computer : public Thing {
public:
    Computer(int inventory_number)
        : Thing("Computer", inventory_number) {}
};
