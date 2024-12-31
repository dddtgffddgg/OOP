#include <iostream>
#include <iomanip>
#include "Beverage.h"

using namespace std;

Beverage::Beverage()
    : MenuItem(), volume(0) {}

Beverage::Beverage(const std::string& name, const std::string& category, int volume, float price, const Nutrients& nutrients)
    : MenuItem(name, category, price, nutrients), volume(volume)
{
    calculateCalories();
}

Beverage::Beverage(const Beverage& other)
    : MenuItem(other),
      volume(other.volume)
{
}

Beverage& Beverage::operator=(const Beverage& other) {
    if (this != &other) {
        MenuItem::operator=(other);
        volume = other.volume;
    }
    return *this;
}

void Beverage::setVolume(int volume) {
    this->volume = volume;
}

int Beverage::getVolume() const {
    return volume;
}

void Beverage::calculateCalories() {
    calories = nutrients.calculateCalories();
}

void Beverage::print(int index) const {
    cout << "| " << left << setw(4) << index + 1 << " | "
         << left << setw(15) << name << " | "
         << left << setw(19) << category << " | "
         << right << setw(8) << calories << " | "
         << right << setw(10) << to_string(volume) + " мл" << " | "
         << right << setw(8) << nutrients.getCarbs() << " | "
         << right << setw(8) << nutrients.getFats() << " | "
         << right << setw(8) << nutrients.getProteins() << " | "
         << right << setw(10) << fixed << setprecision(2) << price << " руб. | "
         << left << setw(14) << "" << " |" << endl;
}
