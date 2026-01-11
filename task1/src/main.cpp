#include <iostream>
#include <memory>
#include <ctime>

#include "di/DIContainer.h"
#include "animals/Rabbit.h"
#include "animals/Monkey.h"
#include "animals/Tiger.h"
#include "animals/Wolf.h"
#include "inventory/Table.h"
#include "inventory/Computer.h"
#include "employees/Employee.h"

void print_menu() {
    std::cout << "\n=== Zoo ERP ===\n";
    std::cout << "1. Add animal\n";
    std::cout << "2. Show total food per day\n";
    std::cout << "3. Show kind animals\n";
    std::cout << "4. Show inventory\n";
    std::cout << "0. Exit\n";
    std::cout << "Select option: ";
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Zoo zoo = DiContainer::zoo();

    bool running = true;

    while (running) {
        print_menu();

        int command;
        std::cin >> command;

        switch (command) {
        case 1: {
            std::cout << "Select animal:\n";
            std::cout << "1. Rabbit\n2. Monkey\n3. Tiger\n4. Wolf\n";
            int type;
            std::cin >> type;

            int inventory_number;
            std::cout << "Inventory number: ";
            std::cin >> inventory_number;

            bool accepted = false;

            if (type == 1 || type == 2) {
                int kindness;
                std::cout << "Kindness level (0-10): ";
                std::cin >> kindness;
                
                if (type == 1) {
                    accepted = zoo.add_animal(
                        std::make_shared<Rabbit>(inventory_number, kindness));
                } else {
                    accepted = zoo.add_animal(
                        std::make_shared<Monkey>(inventory_number, kindness));
                }
            } else if (type == 3) {
                accepted = zoo.add_animal(
                    std::make_shared<Tiger>(inventory_number));
            } else if (type == 4) {
                accepted = zoo.add_animal(
                    std::make_shared<Wolf>(inventory_number));
            }

            if (accepted) {
                std::cout << "Animal accepted to zoo\n";
            } else {
                std::cout << "Animal rejected by vet clinic\n";
            }

            break;
        }

        case 2:
            std::cout << "Total food per day: "
                      << zoo.total_food_per_day()
                      << " kg\n";
            break;

        case 3: {
            auto kind_animals = zoo.get_kind_animals();
            std::cout << "Kind animals:\n";
            for (const auto& animal : kind_animals) {
                std::cout << animal->get_name()
                          << " #" << animal->get_inventory_number()
                          << "\n";
            }
            break;
        }

        case 4: {
            std::cout << "Inventory list:\n";
            for (const auto& item : zoo.get_inventory()) {
                std::cout << "Inventory #"
                          << item->get_inventory_number()
                          << "\n";
            }
            break;
        }

        case 0:
            running = false;
            break;

        default:
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}
