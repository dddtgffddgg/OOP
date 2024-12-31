#include <iostream>
#include <iomanip>
#include <limits>
#include "DishManager.h"

#include "Dish.h"
#include "Beverage.h"
#include "TempBeverage.h"

using namespace std;

DishManager::DishManager() : dishCount(0) {
    for (int i = 0; i < MAX_DISHES; ++i) {
        dishes[i] = nullptr;
    }
}

DishManager::~DishManager() {
    for (int i = 0; i < dishCount; ++i) {
        delete dishes[i];
    }
}

int DishManager::getDishCount() const {
    return dishCount;
}

void DishManager::addDish(MenuItem* newDish) {
    if (dishCount < MAX_DISHES) {
        dishes[dishCount++] = newDish;
        cout << "Блюдо добавлено!\n\n";
    } else {
        cout << "Невозможно добавить больше блюд.\n";
    }
}

void DishManager::deleteDish(int index) {
    if (index >= 0 && index < dishCount) {
        delete dishes[index];
        for (int i = index; i < dishCount - 1; ++i) {
            dishes[i] = dishes[i + 1];
        }
        dishes[dishCount - 1] = nullptr;
        --dishCount;
        cout << "Блюдо удалено!\n";
    } else {
        cout << "Неправильный ввод.\n";
    }
}

void DishManager::copyDish(int index) {
    if (index >= 0 && index < dishCount) {
        if (dishCount >= MAX_DISHES) {
            cout << "Невозможно добавить больше блюд.\n";
            return;
        }
        MenuItem* original = dishes[index];
        MenuItem* copiedDish = nullptr;

        if (TempBeverage* hb = dynamic_cast<TempBeverage*>(original)) {
            copiedDish = new TempBeverage(*hb);
        }
        else if (Beverage* b = dynamic_cast<Beverage*>(original)) {
            copiedDish = new Beverage(*b);
        }
        else if (Dish* d = dynamic_cast<Dish*>(original)) {
            copiedDish = new Dish(*d);
        }

        if (copiedDish) {
            addDish(copiedDish);
            cout << "Блюдо успешно скопировано.\n";
        }
        else {
            cout << "Ошибка копирования блюда: неизвестный тип.\n";
        }
    }
    else {
        cout << "Неверный номер блюда для копирования.\n";
    }
}

void DishManager::assignDish(int sourceIndex, int destIndex) {
    if (sourceIndex >= 0 && sourceIndex < dishCount &&
        destIndex >= 0 && destIndex < dishCount)
    {
        MenuItem* source = dishes[sourceIndex];
        MenuItem* dest = dishes[destIndex];

        delete dest;

        if (TempBeverage* hb = dynamic_cast<TempBeverage*>(source)) {
            dishes[destIndex] = new TempBeverage(*hb);
        }
        else if (Beverage* b = dynamic_cast<Beverage*>(source)) {
            dishes[destIndex] = new Beverage(*b);
        }
        else if (Dish* d = dynamic_cast<Dish*>(source)) {
            dishes[destIndex] = new Dish(*d);
        }
        else {
            dishes[destIndex] = nullptr;
            cout << "Ошибка присваивания: неизвестный тип.\n";
            return;
        }

        cout << "Блюдо успешно присвоено.\n";
    }
    else {
        cout << "Неверные номера блюд для присваивания.\n";
    }
}

void DishManager::printTableHeader() const {
    cout << "| " << left << setw(6) << "№"
         << " | " << left << setw(22) << "Название"
         << " | " << left << setw(20) << "Категория"
         << " | " << right << setw(15) << "Калории"
         << " | " << right << setw(12) << "Вес/Объём"
         << " | " << right << setw(15) << "Углеводы"
         << " | " << right << setw(12) << "Жиры"
         << " | " << right << setw(7) << "Белки"
         << " | " << right << setw(18) << "Цена"
         << " | " << left << setw(20) << "Температура" << " |" << endl;
    cout << string(135, '-') << endl;
}

void DishManager::printDishes() const {
    if (dishCount == 0) {
        cout << "Список блюд пуст.\n";
        return;
    }
    printTableHeader();
    for (int i = 0; i < dishCount; ++i) {
        dishes[i]->print(i);
    }
    cout << string(142, '-') << endl;
    cout << endl;
}

void DishManager::printDishesByCategory(const string& categoryName, bool TempOnly) const {
    bool found = false;
    printTableHeader();
    for (int i = 0; i < dishCount; ++i) {
        MenuItem* item = dishes[i];
        if (item->getCategory() == categoryName) {
            if (TempOnly) {
                if (dynamic_cast<TempBeverage*>(item)) {
                    found = true;
                    item->print(i);
                }
            } else {
                found = true;
                item->print(i);
            }
        }
    }
    cout << string(142, '-') << endl;
    if (!found) {
        cout << "Нет блюд в категории \"" << categoryName << "\".\n";
    }
    cout << endl;
}

void DishManager::compareCalories(int index1, int index2) {
    if (index1 >= 0 && index1 < dishCount && index2 >= 0 && index2 < dishCount) {
        MenuItem* item1 = dishes[index1];
        MenuItem* item2 = dishes[index2];

        cout << "\nСравнение калорий:\n";
        cout << "Блюдо 1: " << item1->getName() << " (" << item1->getCalories() << " калорий)\n";
        cout << "Блюдо 2: " << item2->getName() << " (" << item2->getCalories() << " калорий)\n";

        if (item1->getCalories() > item2->getCalories()) {
            cout << "Блюдо \"" << item1->getName() << "\" содержит больше калорий.\n";
        }
        else if (item1->getCalories() < item2->getCalories()) {
            cout << "Блюдо \"" << item2->getName() << "\" содержит больше калорий.\n";
        }
        else {
            cout << "Оба блюда содержат одинаковое количество калорий.\n";
        }
    }
    else {
        cout << "Ошибка: неверные индексы блюд для сравнения.\n";
    }
}

void DishManager::incrementDishWeight(int index) {
    if (index >= 0 && index < dishCount) {
        if (Dish* dish = dynamic_cast<Dish*>(dishes[index])) {
            (*dish)++; 
            cout << "Вес блюда увеличен: ";
            dish->print(index);
        }
        else if (Beverage* bev = dynamic_cast<Beverage*>(dishes[index])) {
            bev->setVolume(bev->getVolume() + 1);
            bev->calculateCalories();
            cout << "Объём напитка увеличен: ";
            bev->print(index);
        }
    }
    else {
        cout << "Неверный номер блюда.\n";
    }
}

void DishManager::decrementDishWeight(int index) {
    if (index >= 0 && index < dishCount) {
        if (Dish* dish = dynamic_cast<Dish*>(dishes[index])) {
            (*dish)--; 
            cout << "Вес блюда уменьшен: ";
            dish->print(index);
        }
        else if (Beverage* bev = dynamic_cast<Beverage*>(dishes[index])) {
            int vol = bev->getVolume();
            if (vol > 0) {
                bev->setVolume(vol - 1);
                bev->calculateCalories();
            }
            cout << "Объём напитка уменьшен: ";
            bev->print(index);
        }
    }
    else {
        cout << "Неверный номер блюда.\n";
    }
}

MenuItem* DishManager::inputDish() {
    string name, category;
    int size; 
    float price, carbs, fats, proteins;
    int categoryChoice;
    int dishTypeChoice;
    string temperature = "";

    cout << "Введите название: ";
    cin.ignore();
    getline(cin, name);

    cout << "Выберите категорию:\n";
    cout << "1 - Основные блюда\n";
    cout << "2 - Вторые блюда\n";
    cout << "3 - Десерты\n";
    cout << "4 - Напитки\n";
    cout << "Введите номер категории: ";
    while (!(cin >> categoryChoice) || categoryChoice < 1 || categoryChoice > 4) {
        cout << "Неправильный ввод. Введите номер категории (1-4): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (categoryChoice) {
        case 1: category = "Основные блюда"; break;
        case 2: category = "Вторые блюда";   break;
        case 3: category = "Десерты";        break;
        case 4: category = "Напитки";        break;
    }

    if (category == "Напитки") {
        cout << "Выберите тип напитка:\n";
        cout << "1 - Охлажденный напиток\n";
        cout << "2 - Горячий напиток\n";
        cout << "Введите номер типа напитка: ";
        while (!(cin >> dishTypeChoice) || (dishTypeChoice != 1 && dishTypeChoice != 2)) {
            cout << "Неправильный ввод. Введите 1 или 2: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    do {
        cout << "Введите ";
        if (category == "Напитки") cout << "объём (в мл): ";
        else                       cout << "вес (в граммах): ";

        if (!(cin >> size) || size <= 0) {
            cout << "Значение должно быть положительным числом. Повторите ввод.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            size = -1;
        }
    } while (size <= 0);

    do {
        cout << "Введите цену: ";
        if (!(cin >> price) || price < 0) {
            cout << "Цена должна быть положительным числом. Повторите ввод.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            price = -1;
        }
    } while (price < 0);

    do {
        cout << "Введите углеводы (г): ";
        if (!(cin >> carbs) || carbs < 0 || carbs > 100) {
            cout << "Углеводы должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            carbs = -1;
        }
    } while (carbs < 0 || carbs > 100);

    do {
        cout << "Введите жиры (г): ";
        if (!(cin >> fats) || fats < 0 || fats > 100) {
            cout << "Жиры должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            fats = -1;
        }
    } while (fats < 0 || fats > 100);

    do {
        cout << "Введите белки (г): ";
        if (!(cin >> proteins) || proteins < 0 || proteins > 100) {
            cout << "Белки должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            proteins = -1;
        }
    } while (proteins < 0 || proteins > 100);

    Nutrients nutrients(carbs, fats, proteins);

    if (category == "Напитки") {
        if (dishTypeChoice == 1) {
            temperature = "Охлажденный";
            return new TempBeverage(name, category, size, price, nutrients, temperature);
        } else {
            temperature = "Горячий";
            return new TempBeverage(name, category, size, price, nutrients, temperature);
        }
    } else {
        return new Dish(name, category, size, price, nutrients);
    }
}

void DishManager::run() {
    int choice;
    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить блюдо\n";
        cout << "2. Удалить блюдо\n";
        cout << "3. Вывод всех блюд\n";
        cout << "4. Вывод основных блюд\n";
        cout << "5. Вывод вторых блюд\n";
        cout << "6. Вывод десертов\n";
        cout << "7. Вывод напитков\n";
        cout << "8. Вывод горячих напитков\n";
        cout << "9. Увеличить вес/объём блюда\n";
        cout << "10. Уменьшить вес/объём блюда\n";
        cout << "11. Сравнить калории блюд\n";
        cout << "12. Копировать блюдо\n";
        cout << "13. Присвоить одно блюдо другому\n";
        cout << "14. Показать нутриенты блюда\n";
        cout << "15. Выход\n";
        cout << "Введите свой выбор: ";
        cin >> choice;

        if (choice == 1) {
            MenuItem* newDish = inputDish();
            addDish(newDish);
        }
        else if (choice == 2) {
            int index;
            cout << "Для удаления введите номер блюда: ";
            cin >> index;
            deleteDish(index - 1);
        }
        else if (choice == 3) {
            printDishes();
        }
        else if (choice == 4) {
            printDishesByCategory("Основные блюда");
        }
        else if (choice == 5) {
            printDishesByCategory("Вторые блюда");
        }
        else if (choice == 6) {
            printDishesByCategory("Десерты");
        }
        else if (choice == 7) {
            printDishesByCategory("Напитки");
        }
        else if (choice == 8) {
            printDishesByCategory("Напитки", true);
        }
        else if (choice == 9) {
            int index;
            cout << "Введите номер блюда для увеличения веса/объёма: ";
            cin >> index;
            incrementDishWeight(index - 1);
        }
        else if (choice == 10) {
            int index;
            cout << "Введите номер блюда для уменьшения веса/объёма: ";
            cin >> index;
            decrementDishWeight(index - 1);
        }
        else if (choice == 11) {
            int index1, index2;
            cout << "Введите номер первого блюда для сравнения: ";
            cin >> index1;
            cout << "Введите номер второго блюда для сравнения: ";
            cin >> index2;
            compareCalories(index1 - 1, index2 - 1);
        }
        else if (choice == 12) {
            int index;
            cout << "Введите номер блюда для копирования: ";
            cin >> index;
            copyDish(index - 1);
        }
        else if (choice == 13) {
            int sourceIndex, destIndex;
            cout << "Введите номер исходного блюда: ";
            cin >> sourceIndex;
            cout << "Введите номер блюда, которому нужно присвоить данные: ";
            cin >> destIndex;
            assignDish(sourceIndex - 1, destIndex - 1);
        }
        else if (choice == 14) {
            int index;
            cout << "Введите номер блюда для отображения нутриентов: ";
            cin >> index;
            if (index >= 1 && index <= dishCount) {
                MenuItem* item = dishes[index - 1];
                displayNutrients(item->getNutrients());
            }
            else {
                cout << "Неверный номер блюда.\n";
            }
        }
        else if (choice == 15) {
            break;
        }
        else {
            cout << "Неправильный ввод, пожалуйста, повторите.\n";
        }
    }
}
