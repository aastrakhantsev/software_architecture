#pragma once

class IInventory {
public:
    virtual int get_inventory_number() const = 0;
    virtual ~IInventory() = default;
};
