#pragma once
#include <string>
#include "interfaces/IInventory.h"

class Thing : public IInventory {
protected:
    std::string name;
    int inventory_number;

public:
    Thing(const std::string& name, int number)
        : name(name),
          inventory_number(number) {}

    int get_inventory_number() const override {
        return inventory_number;
    }

    std::string get_name() const {
        return name;
    }

    virtual ~Thing() = default;
};
