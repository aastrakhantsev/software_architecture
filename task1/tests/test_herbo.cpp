#include <gtest/gtest.h>
#include "../src/animals/Rabbit.h"
#include "../src/animals/Monkey.h"

TEST(HerboTest, IsKindReturnsCorrectValue) {
    Rabbit rabbit1(1, 8);  // kindness 8
    Rabbit rabbit2(2, 4);  // kindness 4

    EXPECT_TRUE(rabbit1.is_kind());
    EXPECT_FALSE(rabbit2.is_kind());

    Monkey monkey1(3, 6);
    EXPECT_TRUE(monkey1.is_kind());
}
