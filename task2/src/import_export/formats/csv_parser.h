#pragma once
#include "../import_template.h"
#include <fstream>
#include <sstream>

class CSVImport : public ImportTemplate {
public:
    CSVImport(OperationFacade& facade) : ImportTemplate(facade) {}

protected:
    std::vector<std::shared_ptr<Operation>> parse_file(const std::string& filename) override {
        std::vector<std::shared_ptr<Operation>> ops;
        std::ifstream file(filename);
        if (!file.is_open()) return ops;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id, bank_id, category_id;
            std::string type_str, description, date;
            double amount;
            std::getline(ss, type_str, ',');
            ss >> id >> bank_id >> category_id >> amount;
            ss.ignore();
            std::getline(ss, description, ',');
            std::getline(ss, date, ',');

            OperationType type = (type_str == "Income") ? OperationType::Income : OperationType::Expense;
            ops.push_back(std::make_shared<Operation>(id, bank_id, category_id, type, amount, description, date));
        }
        return ops;
    }
};
