#pragma once
#include "inventory/Thing.h"

class Table : public Thing {
public:
    Table(int inventory_number)
        : Thing("Table", inventory_number) {}
};
