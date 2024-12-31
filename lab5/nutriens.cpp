#include <iostream>
#include "Nutrients.h"

Nutrients::Nutrients(float carbs, float fats, float proteins)
    : carbs(carbs), fats(fats), proteins(proteins) {}

Nutrients::Nutrients(const Nutrients& other)
    : carbs(other.carbs), fats(other.fats), proteins(other.proteins) {}

Nutrients& Nutrients::operator=(const Nutrients& other) {
    if (this != &other) {
        carbs = other.carbs;
        fats = other.fats;
        proteins = other.proteins;
    }
    return *this;
}

float Nutrients::getCarbs() const {
    return carbs;
}

float Nutrients::getFats() const {
    return fats;
}

float Nutrients::getProteins() const {
    return proteins;
}

void Nutrients::setCarbs(float value) {
    carbs = value;
}

void Nutrients::setFats(float value) {
    fats = value;
}

void Nutrients::setProteins(float value) {
    proteins = value;
}

float Nutrients::calculateCalories() const {
    // калории = (углеводы * 4) + (жиры * 9) + (белки * 4)
    return (carbs * 4) + (fats * 9) + (proteins * 4);
}
