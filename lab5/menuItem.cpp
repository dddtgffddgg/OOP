#include <iostream>
#include "MenuItem.h"

using namespace std;

MenuItem::MenuItem()
    : name(""), category(""), price(0.0), nutrients(), calories(0.0) {}

MenuItem::MenuItem(const std::string& name, const std::string& category, float price)
    : name(name), category(category), price(price), nutrients(), calories(0.0) {}

MenuItem::MenuItem(const std::string& name, const std::string& category, float price, const Nutrients& nutrients)
    : name(name), category(category), price(price), nutrients(nutrients), calories(0.0) {}

MenuItem::MenuItem(const MenuItem& other)
    : name(other.name),
      category(other.category),
      price(other.price),
      nutrients(other.nutrients),
      calories(other.calories) {}

MenuItem& MenuItem::operator=(const MenuItem& other) {
    if (this != &other) {
        name = other.name;
        category = other.category;
        price = other.price;
        nutrients = other.nutrients;
        calories = other.calories;
    }
    return *this;
}

MenuItem::~MenuItem() {}

void MenuItem::setName(const std::string& name) {
    this->name = name;
}

void MenuItem::setCategory(const std::string& category) {
    this->category = category;
}

void MenuItem::setPrice(float price) {
    this->price = price;
}

void MenuItem::setNutrients(const Nutrients& nutrients) {
    this->nutrients = nutrients;
}

float MenuItem::getCalories() const {
    return calories;
}

std::string MenuItem::getName() const {
    return name;
}

std::string MenuItem::getCategory() const {
    return category;
}

Nutrients& MenuItem::getNutrients() {
    return nutrients;
}

const Nutrients& MenuItem::getNutrients() const {
    return nutrients;
}

// Дружественная функция для отображения нутриентов
void displayNutrients(const Nutrients& nutrients) {
    cout << "Углеводы: " << nutrients.getCarbs() << " г, "
         << "Жиры: " << nutrients.getFats() << " г, "
         << "Белки: " << nutrients.getProteins() << " г" << endl;
}
