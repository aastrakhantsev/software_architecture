#pragma once
#include <string>

enum class OperationType { Income, Expense };

class Operation {
private:
    int id;
    int bank_account_id;
    int category_id;
    OperationType type;
    double amount;
    std::string description;
    std::string date;

public:
    Operation(int i, int b_id, int c_id, OperationType t, double a,
              const std::string& desc, const std::string& d)
        : id(i), bank_account_id(b_id), category_id(c_id), type(t), amount(a), description(desc), date(d) {}

    int get_id() const { return id; }
    int get_bank_account_id() const { return bank_account_id; }
    int get_category_id() const { return category_id; }
    OperationType get_type() const { return type; }
    double get_amount() const { return amount; }

    void set_amount(double new_amount) {
        amount = new_amount;
    }
    const std::string& get_description() const { return description; }

    void set_description(std::string new_description) {
        description = new_description;
    }

    const std::string& get_date() const { return date; }
};
