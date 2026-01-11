#pragma once
#include "../domain/category.h"
#include <vector>
#include <memory>
#include <algorithm>

class CategoryFacade {
private:
    std::vector<std::shared_ptr<Category>> categories;
    int next_id = 1;

public:
    std::shared_ptr<Category> create_category(const std::string& name, CategoryType type) {
        auto cat = std::make_shared<Category>(next_id++, name, type);
        categories.push_back(cat);
        return cat;
    }

    std::shared_ptr<Category> get_category(int id) {
        auto it = std::find_if(categories.begin(), categories.end(),
                               [id](auto& cat){ return cat->get_id() == id; });
        return (it != categories.end()) ? *it : nullptr;
    }

    std::vector<std::shared_ptr<Category>>& get_all_categories() {
        return categories;
    }

    bool delete_category(int id) {
        auto it = std::remove_if(categories.begin(), categories.end(),
                                 [id](auto& cat){ return cat->get_id() == id; });
        if (it != categories.end()) {
            categories.erase(it, categories.end());
            return true;
        }
        return false;
    }

    bool rename_category(int id, const std::string& new_name) {
        auto cat = get_category(id);
        if (!cat) return false;
        cat->set_name(new_name);
        return true;
    }
};
