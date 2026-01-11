#pragma once
#include "../domain/operation.h"
#include "../facade/bank_account_facade.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

class OperationFacade {
private:
    std::vector<std::shared_ptr<Operation>> operations;
    BankAccountFacade& bank_facade;
    int next_id = 1;

public:
    OperationFacade(BankAccountFacade& b) : bank_facade(b) {}

    std::shared_ptr<Operation> add_operation(int bank_id, int category_id,
                                             OperationType type, double amount,
                                             const std::string& description,
                                             const std::string& date)
    {
        auto account = bank_facade.get_account(bank_id);
        if (!account) throw std::runtime_error("Bank account not found");

        if (type == OperationType::Expense && amount > account->get_balance())
            throw std::runtime_error("Insufficient funds");

        if (type == OperationType::Income) account->deposit(amount);
        else account->withdraw(amount);

        auto op = std::make_shared<Operation>(next_id++, bank_id, category_id, type, amount, description, date);
        operations.push_back(op);
        return op;
    }

    std::shared_ptr<Operation> get_operation(int id) {
        auto it = std::find_if(operations.begin(), operations.end(),
                               [id](auto& op){ return op->get_id() == id; });
        return (it != operations.end()) ? *it : nullptr;
    }

    std::vector<std::shared_ptr<Operation>>& get_all_operations() { return operations; }

    bool delete_operation(int id) {
        auto op = get_operation(id);
        if (!op) return false;
        auto account = bank_facade.get_account(op->get_bank_account_id());
        if (op->get_type() == OperationType::Income) account->withdraw(op->get_amount());
        else account->deposit(op->get_amount());

        auto it = std::remove_if(operations.begin(), operations.end(),
                                 [id](auto& o){ return o->get_id() == id; });
        operations.erase(it, operations.end());
        return true;
    }

    bool edit_operation(int id, double new_amount, const std::string& new_description) {
        auto op = get_operation(id);
        if (!op) return false;

        auto account = bank_facade.get_account(op->get_bank_account_id());
        if (op->get_type() == OperationType::Income) account->withdraw(op->get_amount());
        else account->deposit(op->get_amount());

        if (op->get_type() == OperationType::Expense && new_amount > account->get_balance()) {
            if (op->get_type() == OperationType::Income) account->deposit(op->get_amount());
            else account->withdraw(op->get_amount());
            return false;
        }

        op->set_amount(new_amount);
        op->set_description(new_description);

        if (op->get_type() == OperationType::Income) account->deposit(new_amount);
        else account->withdraw(new_amount);

        return true;
    }
};
