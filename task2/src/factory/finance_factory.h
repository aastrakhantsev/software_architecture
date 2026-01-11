#pragma once
#include <memory>
#include "../domain/bank_account.h"
#include "../domain/category.h"
#include "../domain/operation.h"

class FinanceFactory {
public:
    static std::shared_ptr<BankAccount> create_bank_account(int id, const std::string& name, double balance) {
        return std::make_shared<BankAccount>(id, name, balance);
    }

    static std::shared_ptr<Category> create_category(int id, const std::string& name, CategoryType type) {
        return std::make_shared<Category>(id, name, type);
    }

    static std::shared_ptr<Operation> create_operation(
        int id, int bank_id, int category_id, OperationType type,
        double amount, const std::string& description, const std::string& date)
    {
        return std::make_shared<Operation>(id, bank_id, category_id, type, amount, description, date);
    }
    
};
