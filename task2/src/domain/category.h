#pragma once
#include <string>

enum class CategoryType { Income, Expense };

class Category {
private:
    int id;
    std::string name;
    CategoryType type;

public:
    Category(int id, const std::string& name, CategoryType type)
        : id(id), name(name), type(type) {}

    int get_id() const { return id; }

    void set_name(std::string new_name) {
        name = new_name;
    }
    
    std::string get_name() const { return name; }
    CategoryType get_type() const { return type; }
};
