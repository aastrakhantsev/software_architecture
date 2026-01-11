#pragma once
#include <string>
#include "interfaces/IAlive.h"
#include "interfaces/IInventory.h"

class Animal : public IAlive, public IInventory {
protected:
    std::string name;
    int food_per_day;
    int inventory_number;

public:
    Animal(const std::string& name, int food, int number)
        : name(name),
          food_per_day(food),
          inventory_number(number) {}

    int get_food_per_day() const override {
        return food_per_day;
    }

    int get_inventory_number() const override {
        return inventory_number;
    }

    std::string get_name() const {
        return name;
    }

    virtual ~Animal() = default;
};
