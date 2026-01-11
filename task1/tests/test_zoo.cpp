#include <gtest/gtest.h>
#include "../src/di/DIContainer.h"
#include "../src/animals/Rabbit.h"
#include "../src/animals/Monkey.h"
#include "../src/animals/Tiger.h"
#include "../src/animals/Wolf.h"
#include "../src/vet/IHealthChecker.h"

TEST(ZooTest, TotalFoodPerDayCountsCorrectly) {
    Zoo zoo = DiContainer::zoo();

    auto rabbit = std::make_shared<Rabbit>(1, 8); // 2 кг еды
    auto tiger = std::make_shared<Tiger>(2);      // 10 кг еды
    auto wolf = std::make_shared<Wolf>(7);      // 7 кг еды

    EXPECT_TRUE(zoo.add_animal(rabbit));
    EXPECT_TRUE(zoo.add_animal(tiger));
    EXPECT_TRUE(zoo.add_animal(wolf));

    EXPECT_EQ(zoo.total_food_per_day(), 19);
}

TEST(ZooTest, KindAnimalsReturnsOnlyKindAnimals) {
    Zoo zoo = DiContainer::zoo();

    auto rabbit = std::make_shared<Rabbit>(1, 8); // kind
    auto rabbit2 = std::make_shared<Rabbit>(2, 3); // not kind
    auto monkey = std::make_shared<Monkey>(3, 6); // kind

    zoo.add_animal(rabbit);
    zoo.add_animal(rabbit2);
    zoo.add_animal(monkey);

    auto kind_animals = zoo.get_kind_animals();
    EXPECT_EQ(kind_animals.size(), 2);
    EXPECT_TRUE(kind_animals[0]->is_kind());
    EXPECT_TRUE(kind_animals[1]->is_kind());
}
