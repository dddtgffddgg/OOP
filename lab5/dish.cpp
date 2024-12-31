#include <iostream>
#include <iomanip>
#include "Dish.h"

using namespace std;

Dish::Dish()
    : MenuItem(), weight(0) {}

Dish::Dish(const std::string& name, const std::string& category, int weight)
    : MenuItem(name, category, 0.0), weight(weight) {}

Dish::Dish(const std::string& name, const std::string& category, int weight, float price, const Nutrients& nutrients)
    : MenuItem(name, category, price, nutrients), weight(weight)
{
    calculateCalories();
}

Dish::Dish(const Dish& other)
    : MenuItem(other),
      weight(other.weight)
{
}

Dish& Dish::operator=(const Dish& other) {
    if (this != &other) {
        MenuItem::operator=(other);
        weight = other.weight;
    }
    return *this;
}

void Dish::setWeight(int weight) {
    this->weight = weight;
}

int Dish::getWeight() const {
    return weight;
}

void Dish::calculateCalories() {
    calories = nutrients.calculateCalories();
}

void Dish::print(int index) const {
    cout << "| " << left << setw(4) << index + 1 << " | "
         << left << setw(15) << name << " | "
         << left << setw(19) << category << " | "
         << right << setw(8) << calories << " | "
         << right << setw(10) << to_string(weight) + " г" << " | "
         << right << setw(8) << nutrients.getCarbs() << " | "
         << right << setw(8) << nutrients.getFats() << " | "
         << right << setw(8) << nutrients.getProteins() << " | "
         << right << setw(10) << fixed << setprecision(2) << price << " руб. | "
         << left << setw(14) << "" << " |" << endl;
}

//постфиксный инкремент: увеличивает вес блюда
Dish& operator++(Dish& dish, int) {
    dish.weight++;
    dish.calculateCalories();
    return dish;
}

//постфиксный декремент: уменьшает вес блюда
Dish& operator--(Dish& dish, int) {
    if (dish.weight > 0) {
        dish.weight--;
        dish.calculateCalories();
    }
    return dish;
}
