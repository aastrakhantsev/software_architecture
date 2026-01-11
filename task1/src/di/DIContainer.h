#pragma once
#include "../vet/VetClinic.h"
#include "../zoo/Zoo.h"

class DiContainer {
public:
    static VetClinic& vet_clinic() {
        static VetClinic instance;
        return instance;
    }

    static Zoo zoo() {
        return Zoo(vet_clinic());
    }
};
