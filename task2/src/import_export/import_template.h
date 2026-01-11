#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "../domain/operation.h"
#include "../facade/operation_facade.h"

class ImportTemplate {
protected:
    OperationFacade& operation_facade;

    virtual std::vector<std::shared_ptr<Operation>> parse_file(const std::string& filename) = 0;

public:
    ImportTemplate(OperationFacade& facade) : operation_facade(facade) {}

    void import(const std::string& filename) {
        // TODO
    }
};
