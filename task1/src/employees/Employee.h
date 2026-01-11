#pragma once
#include <string>
#include "interfaces/IInventory.h"

class Employee : public IInventory {
private:
    std::string name;
    std::string position;
    int inventory_number;

public:
    Employee(const std::string& name,
             const std::string& position,
             int inventory_number)
        : name(name),
          position(position),
          inventory_number(inventory_number) {}

    int get_inventory_number() const override {
        return inventory_number;
    }

    std::string get_name() const {
        return name;
    }

    std::string get_position() const {
        return position;
    }
};
