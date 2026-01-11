#pragma once
#include "../domain/bank_account.h"
#include <vector>
#include <memory>
#include <algorithm>

class BankAccountFacade {
private:
    std::vector<std::shared_ptr<BankAccount>> accounts;
    int next_id = 1;

public:
    std::shared_ptr<BankAccount> create_account(const std::string& name, double initial_balance = 0) {
        auto account = std::make_shared<BankAccount>(next_id++, name, initial_balance);
        accounts.push_back(account);
        return account;
    }

    std::shared_ptr<BankAccount> get_account(int id) {
        auto it = std::find_if(accounts.begin(), accounts.end(),
                               [id](auto& acc){ return acc->get_id() == id; });
        return (it != accounts.end()) ? *it : nullptr;
    }

    std::vector<std::shared_ptr<BankAccount>>& get_all_accounts() {
        return accounts;
    }

    bool delete_account(int id) {
        auto it = std::remove_if(accounts.begin(), accounts.end(),
                                 [id](auto& acc){ return acc->get_id() == id; });
        if (it != accounts.end()) {
            accounts.erase(it, accounts.end());
            return true;
        }
        return false;
    }

    bool rename_account(int id, const std::string& new_name) {
        auto acc = get_account(id);
        if (!acc) return false;
        acc->set_name(new_name);
        return true;
    }
};
