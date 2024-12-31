#include <iostream>
#include <iomanip>
#include "TempBeverage.h"

using namespace std;

TempBeverage::TempBeverage()
    : Beverage(), temperature("") {}

TempBeverage::TempBeverage(const std::string& name, const std::string& category, int volume, float price,
                           const Nutrients& nutrients, const std::string& temperature)
    : Beverage(name, category, volume, price, nutrients),
      temperature(temperature) {}

TempBeverage::TempBeverage(const TempBeverage& other)
    : Beverage(other),
      temperature(other.temperature) {}

TempBeverage& TempBeverage::operator=(const TempBeverage& other) {
    if (this != &other) {
        Beverage::operator=(other);
        temperature = other.temperature;
    }
    return *this;
}

void TempBeverage::print(int index) const {
    cout << "| " << left << setw(4) << index + 1 << " | "
         << left << setw(15) << name << " | "
         << left << setw(19) << category << " | "
         << right << setw(8) << calories << " | "
         << right << setw(10) << to_string(volume) + " мл" << " | "
         << right << setw(8) << nutrients.getCarbs() << " | "
         << right << setw(8) << nutrients.getFats() << " | "
         << right << setw(8) << nutrients.getProteins() << " | "
         << right << setw(10) << fixed << setprecision(2) << price << " руб. | "
         << left << setw(14) << temperature << " |" << endl;
}
