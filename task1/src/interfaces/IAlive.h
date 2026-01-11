#pragma once

class IAlive {
public:
    virtual int get_food_per_day() const = 0;
    virtual ~IAlive() = default;
};
