#pragma once
#include "animals/Animal.h"

class IHealthChecker {
public:
    virtual bool check_health(const Animal& animal) const = 0;
    virtual ~IHealthChecker() = default;
};
