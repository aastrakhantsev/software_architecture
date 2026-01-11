#pragma once
#include <string>
#include <stdexcept>

class BankAccount {
private:
    int id;
    std::string name;
    double balance;

public:
    BankAccount(int id, const std::string& name, double balance)
        : id(id), name(name), balance(balance) {
        if (balance < 0) throw std::invalid_argument("Balance cannot be negative");
    }

    int get_id() const { return id; }
    std::string get_name() const { return name; }
    double get_balance() const { return balance; }

    void set_name(std::string new_name) {
        name = new_name;
    }

    void deposit(double amount) {
        if (amount < 0) throw std::invalid_argument("Amount must be positive");
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount < 0) throw std::invalid_argument("Amount must be positive");
        if (amount > balance) throw std::runtime_error("Insufficient funds");
        balance -= amount;
    }
};
