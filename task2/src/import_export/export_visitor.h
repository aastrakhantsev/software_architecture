#pragma once
#include "../domain/operation.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class ExportVisitor {
public:
    virtual void visit(const std::vector<std::shared_ptr<Operation>>& operations, const std::string& filename) = 0;
};

class CSVExportVisitor : public ExportVisitor {
public:
    void visit(const std::vector<std::shared_ptr<Operation>>& operations, const std::string& filename) override {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Cannot open file " << filename << " for writing.\n";
            return;
        }
        for (auto& op : operations) {
            file << ((op->get_type() == OperationType::Income) ? "Income" : "Expense") << ","
                 << op->get_id() << "," << op->get_bank_account_id() << "," << op->get_category_id() << ","
                 << op->get_amount() << "," << op->get_description() << "," << op->get_date() << "\n";
        }
        std::cout << "Exported " << operations.size() << " operations to " << filename << "\n";
    }
};
