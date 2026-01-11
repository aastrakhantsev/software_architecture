#include <gtest/gtest.h>
#include "../src/facade/operation_facade.h"
#include "../src/facade/bank_account_facade.h"
#include "../src/facade/category_facade.h"

TEST(OperationFacadeTest, AddAndListOperations) {
    BankAccountFacade bank_facade;
    CategoryFacade category_facade;
    OperationFacade op_facade(bank_facade);

    auto acc = bank_facade.create_account("Main", 1000.0);
    auto cat_income = category_facade.create_category("Salary", CategoryType::Income);
    auto cat_expense = category_facade.create_category("Food", CategoryType::Expense);

    auto op1 = op_facade.add_operation(acc->get_id(), cat_income->get_id(), OperationType::Income, 500.0, "Salary", "2026-01-01");
    auto op2 = op_facade.add_operation(acc->get_id(), cat_expense->get_id(), OperationType::Expense, 200.0, "Lunch", "2026-01-02");

    auto ops = op_facade.get_all_operations();
    ASSERT_EQ(ops.size(), 2);
    ASSERT_EQ(acc->get_balance(), 1300.0); // 1000 + 500 - 200

    ASSERT_EQ(ops[0]->get_amount(), 500.0);
    ASSERT_EQ(ops[1]->get_description(), "Lunch");
}

TEST(OperationFacadeTest, EditAndDeleteOperation) {
    BankAccountFacade bank_facade;
    CategoryFacade category_facade;
    OperationFacade op_facade(bank_facade);

    auto acc = bank_facade.create_account("Main", 1000.0);
    auto cat = category_facade.create_category("Salary", CategoryType::Income);

    auto op = op_facade.add_operation(acc->get_id(), cat->get_id(), OperationType::Income, 500.0, "Salary", "2026-01-01");
    
    ASSERT_TRUE(op_facade.edit_operation(op->get_id(), 600.0, "Updated Salary"));
    ASSERT_EQ(op->get_amount(), 600.0);
    ASSERT_EQ(op->get_description(), "Updated Salary");

    ASSERT_TRUE(op_facade.delete_operation(op->get_id()));
    ASSERT_TRUE(op_facade.get_all_operations().empty());
}
