#pragma once
#include "../facade/operation_facade.h"
#include "../facade/category_facade.h"
#include "../facade/bank_account_facade.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <memory>

class AnalyticsFacade {
private:
    OperationFacade& operation_facade;
    CategoryFacade& category_facade;
    BankAccountFacade& bank_facade;

    std::vector<std::shared_ptr<Operation>> filter_operations_by_date(
        const std::string& start_date = "", const std::string& end_date = "")
    {
        std::vector<std::shared_ptr<Operation>> result;
        for (auto& op : operation_facade.get_all_operations()) {
            if (start_date.empty() || (op->get_date() >= start_date && op->get_date() <= end_date))
                result.push_back(op);
        }
        return result;
    }

public:
    AnalyticsFacade(OperationFacade& o, CategoryFacade& c, BankAccountFacade& b)
        : operation_facade(o), category_facade(c), bank_facade(b) {}

    void income_expense_per_account(const std::string& start_date = "", const std::string& end_date = "") {
        auto ops = filter_operations_by_date(start_date, end_date);

        for (auto& acc : bank_facade.get_all_accounts()) {
            double income = 0, expense = 0;
            for (auto& op : ops) {
                if (op->get_bank_account_id() == acc->get_id()) {
                    if (op->get_type() == OperationType::Income) income += op->get_amount();
                    else expense += op->get_amount();
                }
            }
            std::cout << acc->get_name()
                      << " | Total Income: " << income
                      << " | Total Expense: " << expense
                      << " | Current Balance: " << acc->get_balance()
                      << "\n";
        }
    }

    void group_by_category_per_account(const std::string& start_date = "", const std::string& end_date = "") {
        auto ops = filter_operations_by_date(start_date, end_date);

        std::cout << "\n--- Group by category per account ---\n";
        for (auto& acc : bank_facade.get_all_accounts()) {
            std::map<int, double> income_map;
            std::map<int, double> expense_map;

            for (auto& op : ops) {
                if (op->get_bank_account_id() != acc->get_id()) continue;
                if (op->get_type() == OperationType::Income)
                    income_map[op->get_category_id()] += op->get_amount();
                else
                    expense_map[op->get_category_id()] += op->get_amount();
            }

            std::cout << "Account: " << acc->get_name() << "\n";
            for (auto& [cat_id, amount] : income_map) {
                auto cat = category_facade.get_category(cat_id);
                std::cout << "  Income - " << (cat ? cat->get_name() : "Unknown") << ": " << amount << "\n";
            }
            for (auto& [cat_id, amount] : expense_map) {
                auto cat = category_facade.get_category(cat_id);
                std::cout << "  Expense - " << (cat ? cat->get_name() : "Unknown") << ": " << amount << "\n";
            }
        }
    }
};
