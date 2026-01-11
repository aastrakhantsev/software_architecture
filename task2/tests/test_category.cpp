#include <gtest/gtest.h>
#include "../src/facade/category_facade.h"

TEST(CategoryFacadeTest, CreateAndGetCategory) {
    CategoryFacade facade;
    auto cat = facade.create_category("Salary", CategoryType::Income);

    ASSERT_EQ(cat->get_name(), "Salary");
    ASSERT_EQ(cat->get_type(), CategoryType::Income);
}

TEST(CategoryFacadeTest, RenameAndDelete) {
    CategoryFacade facade;
    auto cat = facade.create_category("Old Cat", CategoryType::Expense);
    
    ASSERT_TRUE(facade.rename_category(cat->get_id(), "New Cat"));
    ASSERT_EQ(cat->get_name(), "New Cat");

    ASSERT_TRUE(facade.delete_category(cat->get_id()));
    ASSERT_FALSE(facade.delete_category(cat->get_id()));
}
