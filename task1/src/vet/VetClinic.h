#pragma once
#include <cstdlib>
#include "vet/IHealthChecker.h"

class VetClinic : public IHealthChecker {
public:
    bool check_health(const Animal& animal) const override {
        return external_system_decision(animal);
    }

private:
    // can be replaced with real request to clinic
    bool external_system_decision(const Animal& animal) const {
        return animal.get_food_per_day() < 12;
    }
};
    