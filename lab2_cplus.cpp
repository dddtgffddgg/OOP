#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_DISHES = 100; //максимальное количество блюд, которое можно добавить

class Nutrients { //хранение инфы о нутриентах
public:
    float carbs;
    float fats;
    float proteins;
    //конструктор для инициализации значений
    Nutrients(float carbs = 0.0, float fats = 0.0, float proteins = 0.0)
        : carbs(carbs), fats(fats), proteins(proteins) {}
};

class Dish { //хранение инфы о блюде
public:
    string name;
    string category;
    int calories;
    int weight;
    float price;
    Nutrients nutrients;

    //конструктор с основными параметрами блюда
    Dish(string name, string category, int calories, int weight)
        : name(name), category(category), calories(calories), weight(weight), price(0.0), nutrients() {}
    //конструктор для инициализации блюда с параметрами по умолчанию
    Dish(string name = "", string category = "", int calories = 0, int weight = 0, float price = 0.0, Nutrients nutrients = {})
        : name(name), category(category), calories(calories), weight(weight), price(price), nutrients(nutrients) {}

    void print(int index) const {
        cout << "| " << left << setw(5) << index + 1
             << "| " << setw(16) << name
             << "| " << setw(20) << category
             << "| " << setw(10) << calories
             << "| " << setw(12) << (to_string(weight) + (category == "Напитки" ? " мл" : " г"))
             << "| " << setw(10) << nutrients.carbs
             << "| " << setw(10) << nutrients.fats
             << "| " << setw(10) << nutrients.proteins
             << "| " << setw(10) << fixed << setprecision(2) << price << " руб." << " |" << endl;
    }
};

class DishManager { //класс для управления списком блюд
private:
    Dish dishes[MAX_DISHES]; //массив блюд
    int dishCount = 0;       //текущее количество блюд

public:
    int getDishCount() const {
        return dishCount;
    }
    //метод добавлений блюда
    void addDish(const Dish& newDish) {
        if (dishCount < MAX_DISHES) {
            dishes[dishCount] = newDish;
            dishCount++;
            cout << "Блюдо добавлено!\n\n";
        } else {
            cout << "Невозможно добавить больше блюд.\n";
        }
    }
    //метод удаления блюда
    void deleteDish(int index) {
        if (index >= 0 && index < dishCount) {
            for (int i = index; i < dishCount - 1; ++i) {
                dishes[i] = dishes[i + 1];
            }
            dishCount--;
            cout << "Блюдо удалено!\n";
        } else {
            cout << "Неправильный ввод.\n";
        }
    }
    
    void printTableHeader() const {
        cout << "| " << left << setw(7) << "№"
             << "| " << setw(25) << "Название"
             << "| " << setw(20) << "Категория"
             << "| " << setw(19) << "Калории"
             << "| " << setw(15) << "Вес"
             << "| " << setw(11) << "Угл"
             << "| " << setw(14) << "Жиры"
             << "| " << setw(15) << "Белки"
             << "| " << setw(18) << "Цена" << " |" << endl;
        cout << string(130, '-') << endl;
    }

    void printDishes() const {
        if (dishCount == 0) {
            cout << "Список блюд пуст.\n";
            return;
        }

        printTableHeader();
        for (int i = 0; i < dishCount; ++i) {
            dishes[i].print(i);
        }
        cout << string(130, '-') << endl;
        cout << endl;
    }
    //метод для печати блюд по категориям
    void printDishesByCategory(const string& categoryName) const {
        bool found = false;
        printTableHeader();
        for (int i = 0; i < dishCount; ++i) {
            if (dishes[i].category == categoryName) {
                found = true;
                dishes[i].print(i);
            }
        }
        cout << string(130, '-') << endl;
        if (!found) {
            cout << "Нет блюд в категории \"" << categoryName << "\".\n";
        }
        cout << endl;
    }
};

int main() {
    DishManager manager;
    int choice;

    while (true) {
        cout << "1. Добавить блюдо\n";
        cout << "2. Удалить блюдо\n";
        cout << "3. Вывод всех блюд\n";
        cout << "4. Вывод основных блюд\n";
        cout << "5. Вывод вторых блюд\n";
        cout << "6. Вывод десертов\n";
        cout << "7. Вывод напитков\n";
        cout << "8. Выход\n";
        cout << "Введите свой выбор: ";
        cin >> choice;

        if (choice == 1) {
            Dish newDish;
            int categoryChoice;

            cout << "Введите название: ";
            cin.ignore();
            getline(cin, newDish.name);

            cout << "Выберите категорию:\n";
            cout << "1 - Основные блюда\n";
            cout << "2 - Вторые блюда\n";
            cout << "3 - Десерты\n";
            cout << "4 - Напитки\n";
            cout << "Введите номер категории: ";
            cin >> categoryChoice;

            switch (categoryChoice) {
                case 1: newDish.category = "Основные блюда"; break;
                case 2: newDish.category = "Вторые блюда"; break;
                case 3: newDish.category = "Десерты"; break;
                case 4: newDish.category = "Напитки"; break;
                default: cout << "Неправильный выбор категории.\n"; continue;
            }

            cout << "Введите калории (в ккал): ";
            cin >> newDish.calories;
            cout << "Введите " << (newDish.category == "Напитки" ? "объем (в мл): " : "вес (в граммах): ");
            cin >> newDish.weight;

            cout << "Введите углеводы (г): ";
            cin >> newDish.nutrients.carbs;
            cout << "Введите жиры (г): ";
            cin >> newDish.nutrients.fats;
            cout << "Введите белки (г): ";
            cin >> newDish.nutrients.proteins;

            cout << "Введите прайс: ";
            cin >> newDish.price;

            manager.addDish(newDish);

        } else if (choice == 2) {
            int index;
            cout << "Для удаления введите номер блюда: ";
            cin >> index;
            manager.deleteDish(index - 1);
        } else if (choice == 3) {
            manager.printDishes();
        } else if (choice == 4) {
            manager.printDishesByCategory("Основные блюда");
        } else if (choice == 5) {
            manager.printDishesByCategory("Вторые блюда");
        } else if (choice == 6) {
            manager.printDishesByCategory("Десерты");
        } else if (choice == 7) {
            manager.printDishesByCategory("Напитки");
        } else if (choice == 8) {
            break;
        } else {
            cout << "Неправильный ввод, пожалуйста повторите.\n";
        }
    }

    return 0;
}
