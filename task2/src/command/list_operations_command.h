#pragma once
#include "command.h"
#include "../facade/operation_facade.h"
#include "../facade/category_facade.h"
#include "../facade/bank_account_facade.h"
#include <iostream>

class ListOperationsCommand : public Command {
private:
    OperationFacade& operation_facade;
    CategoryFacade& category_facade;
    BankAccountFacade& bank_facade;

public:
    ListOperationsCommand(OperationFacade& o, CategoryFacade& c, BankAccountFacade& b)
        : operation_facade(o), category_facade(c), bank_facade(b) {}

    void execute() override {
        auto operations = operation_facade.get_all_operations();
        if (operations.empty()) {
            std::cout << "No operations available.\n";
            return;
        }

        std::cout << "Operations list:\n";
        for (auto& op : operations) {
            auto cat = category_facade.get_category(op->get_category_id());
            auto acc = bank_facade.get_account(op->get_bank_account_id());

            std::cout << "ID: " << op->get_id()
                      << " | Account: " << (acc ? acc->get_name() : "Unknown")
                      << " | Category: " << (cat ? cat->get_name() : "Unknown")
                      << " | Type: " << (op->get_type() == OperationType::Income ? "Income" : "Expense")
                      << " | Amount: " << op->get_amount()
                      << " | Description: " << op->get_description()
                      << "\n";
        }
    }
};
