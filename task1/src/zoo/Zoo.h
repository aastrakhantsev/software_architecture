#pragma once
#include <vector>
#include <memory>
#include "vet/IHealthChecker.h"
#include "animals/Herbo.h"
#include "interfaces/IInventory.h"

class Zoo {
private:
    const IHealthChecker& vet_clinic;
    std::vector<std::shared_ptr<Animal>> animals;
    std::vector<std::shared_ptr<IInventory>> inventory;

public:
    explicit Zoo(const IHealthChecker& vet_clinic)
        : vet_clinic(vet_clinic) {}

    bool add_animal(const std::shared_ptr<Animal>& animal) {
        if (vet_clinic.check_health(*animal)) {
            animals.push_back(animal);
            inventory.push_back(animal);
            return true;
        }
        return false;
    }

    void add_inventory(const std::shared_ptr<IInventory>& item) {
        inventory.push_back(item);
    }

    int total_food_per_day() const {
        int total = 0;
        for (const auto& animal : animals) {
            total += animal->get_food_per_day();
        }
        return total;
    }

    std::vector<std::shared_ptr<Herbo>> get_kind_animals() const {
        std::vector<std::shared_ptr<Herbo>> result;
        for (const auto& animal : animals) {
            if (auto herbo = std::dynamic_pointer_cast<Herbo>(animal);
                herbo && herbo->is_kind()) {
                result.push_back(herbo);
            }
        }
        return result;
    }

    const std::vector<std::shared_ptr<IInventory>>& get_inventory() const {
        return inventory;
    }
};
