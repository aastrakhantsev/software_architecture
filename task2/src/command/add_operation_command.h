#pragma once
#include "command.h"
#include "../facade/bank_account_facade.h"
#include "../facade/category_facade.h"
#include "../facade/operation_facade.h"
#include "../factory/finance_factory.h"
#include <iostream>

class AddOperationCommand : public Command {
private:
    BankAccountFacade& bank_facade;
    CategoryFacade& category_facade;
    OperationFacade& operation_facade;

public:
    AddOperationCommand(BankAccountFacade& b, CategoryFacade& c, OperationFacade& o)
        : bank_facade(b), category_facade(c), operation_facade(o) {}

    void execute() override {
        int bank_id, category_id;
        double amount;
        std::string description;

        std::cout << "Enter bank account ID: ";
        std::cin >> bank_id;
        auto acc = bank_facade.get_account(bank_id);
        if (!acc) { 
            std::cout << "Bank account not found!\n"; 
            return; 
        }

        std::cout << "Enter category ID: ";
        std::cin >> category_id;
        auto cat = category_facade.get_category(category_id);
        if (!cat) {
            std::cout << "Category not found!\n"; 
            return;
        }

        std::cout << "Enter amount: ";
        std::cin >> amount;
        if (amount <= 0) {
            std::cout << "Amount must be positive!\n";
            return;
        }
        std::cin.ignore();

        std::string date;
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::getline(std::cin, date);

        std::cout << "Enter description: ";
        std::getline(std::cin, description);

        OperationType type = cat->get_type() == CategoryType::Income ? OperationType::Income : OperationType::Expense;

        auto op = FinanceFactory::create_operation(
            operation_facade.get_all_operations().size() + 1,
            bank_id,
            category_id,
            type,
            amount,
            description,
            date
        );
        
        try {
            if (type == OperationType::Income)
                acc->deposit(amount);
            else
                acc->withdraw(amount);
            
            operation_facade.add_operation(op);
            
            std::cout << "Operation added successfully!\n";
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
};
