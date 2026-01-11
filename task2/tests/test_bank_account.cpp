#include <gtest/gtest.h>
#include "../src/facade/bank_account_facade.h"

TEST(BankAccountFacadeTest, CreateAndGetAccount) {
    BankAccountFacade facade;
    auto acc = facade.create_account("Main Account", 1000.0);
    
    ASSERT_EQ(acc->get_name(), "Main Account");
    ASSERT_EQ(acc->get_balance(), 1000.0);
    ASSERT_GT(acc->get_id(), 0);
}

TEST(BankAccountFacadeTest, DepositAndWithdraw) {
    BankAccountFacade facade;
    auto acc = facade.create_account("Savings", 500.0);

    acc->deposit(200.0);
    ASSERT_EQ(acc->get_balance(), 700.0);

    ASSERT_THROW(acc->withdraw(1000.0), std::runtime_error);
    acc->withdraw(300.0);
    ASSERT_EQ(acc->get_balance(), 400.0);
}

TEST(BankAccountFacadeTest, RenameAndDelete) {
    BankAccountFacade facade;
    auto acc = facade.create_account("Old Name", 0.0);
    ASSERT_TRUE(facade.rename_account(acc->get_id(), "New Name"));
    ASSERT_EQ(acc->get_name(), "New Name");

    ASSERT_TRUE(facade.delete_account(acc->get_id()));
    ASSERT_FALSE(facade.delete_account(acc->get_id()));
}
