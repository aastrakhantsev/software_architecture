#include <iostream>
#include <string>
#include "facade/bank_account_facade.h"
#include "facade/category_facade.h"
#include "facade/operation_facade.h"
#include "facade/analytics_facade.h"
#include "domain/operation.h"
#include "import_export/export_visitor.h"

int main() {
    BankAccountFacade bank_facade;
    CategoryFacade category_facade;
    OperationFacade operation_facade(bank_facade);
    AnalyticsFacade analytics_facade(operation_facade, category_facade, bank_facade);

    bank_facade.create_account("Main Account", 1000);
    bank_facade.create_account("Savings Account", 500);

    int option = -1;

    while(option != 0) {
        std::cout << "\n=== FinanceERP ===\n"
                  << "1. Create account\n"
                  << "2. Edit account\n"
                  << "3. Delete account\n"
                  << "4. Create category\n"
                  << "5. Edit category\n"
                  << "6. Delete category\n"
                  << "7. Add operation\n"
                  << "8. Edit operation\n"
                  << "9. Delete operation\n"
                  << "10. List accounts\n"
                  << "11. List categories\n"
                  << "12. List operations\n"
                  << "13. Show analytics\n"
                  << "0. Exit\n"
                  << "Select option: ";
        std::cin >> option;
        std::cin.ignore();

        try {
            switch(option) {
                // --- ACCOUNTS ---
                case 1: { // Create
                    std::string name; double balance;
                    std::cout << "Account name: "; std::getline(std::cin, name);
                    std::cout << "Initial balance: "; std::cin >> balance; std::cin.ignore();
                    bank_facade.create_account(name, balance);
                    break;
                }
                case 2: { // Edit
                    int id; std::string name;
                    std::cout << "Account ID to rename: "; std::cin >> id; std::cin.ignore();
                    std::cout << "New name: "; std::getline(std::cin, name);
                    if (!bank_facade.rename_account(id, name))
                        std::cout << "Account not found\n";
                    break;
                }
                case 3: { // Delete
                    int id; std::cout << "Account ID to delete: "; std::cin >> id; std::cin.ignore();
                    if (!bank_facade.delete_account(id))
                        std::cout << "Account not found\n";
                    break;
                }

                // --- CATEGORIES ---
                case 4: { // Create
                    std::string name; int type;
                    std::cout << "Category name: "; std::getline(std::cin, name);
                    std::cout << "Type (0: Expense, 1: Income): "; std::cin >> type; std::cin.ignore();
                    category_facade.create_category(name, type == 1 ? CategoryType::Income : CategoryType::Expense);
                    break;
                }
                case 5: { // Edit
                    int id; std::string name;
                    std::cout << "Category ID to rename: "; std::cin >> id; std::cin.ignore();
                    std::cout << "New name: "; std::getline(std::cin, name);
                    if (!category_facade.rename_category(id, name))
                        std::cout << "Category not found\n";
                    break;
                }
                case 6: { // Delete
                    int id; std::cout << "Category ID to delete: "; std::cin >> id; std::cin.ignore();
                    if (!category_facade.delete_category(id))
                        std::cout << "Category not found\n";
                    break;
                }

                // --- OPERATIONS ---
                case 7: { // Add
                    int bank_id, cat_id, type_int;
                    double amount; std::string desc, date;
                    std::cout << "Bank account ID: "; std::cin >> bank_id; std::cin.ignore();
                    std::cout << "Category ID: "; std::cin >> cat_id; std::cin.ignore();
                    std::cout << "Type (0: Expense, 1: Income): "; std::cin >> type_int; std::cin.ignore();
                    std::cout << "Amount: "; std::cin >> amount; std::cin.ignore();
                    std::cout << "Description: "; std::getline(std::cin, desc);
                    std::cout << "Date (YYYY-MM-DD): "; std::getline(std::cin, date);

                    operation_facade.add_operation(bank_id, cat_id,
                        type_int == 1 ? OperationType::Income : OperationType::Expense,
                        amount, desc, date);
                    std::cout << "Operation added!\n";
                    break;
                }
                case 8: { // Edit
                    int id; double amount; std::string desc;
                    std::cout << "Operation ID to edit: "; std::cin >> id; std::cin.ignore();
                    std::cout << "New amount: "; std::cin >> amount; std::cin.ignore();
                    std::cout << "New description: "; std::getline(std::cin, desc);
                    if (!operation_facade.edit_operation(id, amount, desc))
                        std::cout << "Operation not found or insufficient funds\n";
                    break;
                }
                case 9: { // Delete
                    int id; std::cout << "Operation ID to delete: "; std::cin >> id; std::cin.ignore();
                    if (!operation_facade.delete_operation(id))
                        std::cout << "Operation not found\n";
                    break;
                }

                // --- LISTS ---
                case 10: { // Accounts
                    std::cout << "--- Accounts ---\n";
                    for (auto& acc : bank_facade.get_all_accounts())
                        std::cout << acc->get_id() << ": " << acc->get_name()
                                  << " | Balance: " << acc->get_balance() << "\n";
                    break;
                }
                case 11: { // Categories
                    std::cout << "--- Categories ---\n";
                    for (auto& cat : category_facade.get_all_categories())
                        std::cout << cat->get_id() << ": " << cat->get_name()
                                  << " | Type: " << (cat->get_type() == CategoryType::Income ? "Income" : "Expense") << "\n";
                    break;
                }
                case 12: {
                    std::cout << "--- Operations ---\n";
                    for (auto& op : operation_facade.get_all_operations())
                        std::cout << op->get_id() << ": " 
                                  << "Account " << op->get_bank_account_id()
                                  << ", Category " << op->get_category_id()
                                  << ", " << (op->get_type() == OperationType::Income ? "Income" : "Expense")
                                  << ", Amount: " << op->get_amount()
                                  << ", Desc: " << op->get_description()
                                  << ", Date: " << op->get_date()
                                  << "\n";
                    break;
                }
                case 13: {
                    std::string start = "", end = "";
                    std::cout << "Start date (YYYY-MM-DD, leave empty for all): "; std::getline(std::cin, start);
                    if (start != "") {
                        std::cout << "End date (YYYY-MM-DD, leave empty for all): "; std::getline(std::cin, end);
                    }
                    
                    analytics_facade.income_expense_per_account(start, end);
                    analytics_facade.group_by_category_per_account(start, end);
                    break;
                }

                case 0: std::cout << "Exiting...\n"; break;

                default: std::cout << "Invalid option\n"; break;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    CSVExportVisitor exporter;
    exporter.visit(operation_facade.get_all_operations(), "operations_export.csv");

    return 0;
}
