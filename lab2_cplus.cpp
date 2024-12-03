#include <iostream>
#include <iomanip> 
#include <string>

using namespace std;

const int MAX_DISHES = 100;

class Nutrients { 
private:
    float carbs;    // углеводы
    float fats;     // жиры
    float proteins; // белки

public:
    // конструктор Nutrients
    Nutrients(float carbs = 0.0, float fats = 0.0, float proteins = 0.0)
        : carbs(carbs), fats(fats), proteins(proteins) {}

    // для БЖУ
    float getCarbs() const { return carbs; }
    float getFats() const { return fats; }
    float getProteins() const { return proteins; }

    // для БЖУ
    void setCarbs(float value) { carbs = value; }
    void setFats(float value) { fats = value; }
    void setProteins(float value) { proteins = value; }

    //метод для вычисления калорийности на основе БЖУ
    float calculateCalories() const {
        return (carbs * 4) + (fats * 9) + (proteins * 4); // калории = углеводы * 4 + жиры * 9 + белки * 4
    }
};

class Dish { 
private:
    string name;
    string category;
    int weight;
    float price;
    Nutrients nutrients;
    float calories; // калории

public:
    //конструктор по умолчанию
    Dish() 
        : name(""), category(""), weight(0), price(0.0), nutrients(), calories(0.0) {}

    //конструктор с основными параметрами
    Dish(const string& name, const string& category, int weight)
        : name(name), category(category), weight(weight), price(0.0), nutrients(), calories(0.0) {}

    //конструктор со всеми параметрами
    Dish(const string& name, const string& category, int weight, float price, const Nutrients& nutrients)
        : name(name), category(category), weight(weight), price(price), nutrients(nutrients), calories(0.0) {
        //при создании блюда сразу вычисляем калории
        calculateCalories();
    }

    void setName(const string& name) { this->name = name; }
    void setCategory(const string& category) { this->category = category; }
    void setWeight(int weight) { this->weight = weight; }
    void setPrice(float price) { this->price = price; }
    void setNutrients(const Nutrients& nutrients) { this->nutrients = nutrients; }

    //метод для расчета калорий
    void calculateCalories() {
        calories = nutrients.calculateCalories(); // Получаем калории через класс Nutrients
    }

    //метод для вывода блюда
    void print(int index) const {
        cout << "| " << left << setw(5) << index + 1
             << "| " << setw(16) << name
             << "| " << setw(20) << category
             << "| " << setw(10) << calories
             << "| " << setw(12) << (to_string(weight) + (category == "Напитки" ? " мл" : " г"))
             << "| " << setw(10) << nutrients.getCarbs()
             << "| " << setw(10) << nutrients.getFats()
             << "| " << setw(10) << nutrients.getProteins()
             << "| " << setw(10) << fixed << setprecision(2) << price << " руб." << " |" << endl;
    }

    //делаем доступ к этому методу для DishManager
    friend class DishManager;
};

class DishManager { 
private:
    Dish dishes[MAX_DISHES];
    int dishCount = 0;

    int getDishCount() const { return dishCount; }

    void addDish(const Dish& newDish) { 
        if (dishCount < MAX_DISHES) { 
            dishes[dishCount++] = newDish;
            cout << "Блюдо добавлено!\n\n";
        } else {
            cout << "Невозможно добавить больше блюд.\n";
        }
    }

    void deleteDish(int index) { 
        if (index >= 0 && index < dishCount) {
            for (int i = index; i < dishCount - 1; ++i) {
                dishes[i] = dishes[i + 1];
            }
            --dishCount;
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

    Dish inputDish() {
        string name, category;
        int weight, categoryChoice;
        float price, carbs, fats, proteins;

        cout << "Введите название: ";
        cin.ignore();  
        getline(cin, name);  

        cout << "Выберите категорию:\n";
        cout << "1 - Основные блюда\n";
        cout << "2 - Вторые блюда\n";
        cout << "3 - Десерты\n";
        cout << "4 - Напитки\n";
        cout << "Введите номер категории: ";

        //проверка на корректность ввода категории
        while (!(cin >> categoryChoice) || categoryChoice < 1 || categoryChoice > 4) {
            cout << "Неправильный ввод. Введите номер категории (1-4): ";
            cin.clear();  // Сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем буфер
        }

        switch (categoryChoice) {
            case 1: category = "Основные блюда"; break;
            case 2: category = "Вторые блюда"; break;
            case 3: category = "Десерты"; break;
            case 4: category = "Напитки"; break;
        }

        //проверка на ввод веса
        do {
            cout << "Введите вес (в граммах или мл): ";
            if (!(cin >> weight) || weight <= 0) {
                cout << "Вес должен быть положительным числом. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                weight = -1;  // Устанавливаем некорректное значение для продолжения цикла
            }
        } while (weight <= 0);

        //проверка на ввод углеводов
        do {
            cout << "Введите углеводы (г): ";
            if (!(cin >> carbs) || carbs < 0 || carbs > 100) {
                cout << "Углеводы должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                carbs = -1;  //некорректное значение для повторного ввода
            }
        } while (carbs < 0 || carbs > 100);

        //проверка на ввод жиров
        do {
            cout << "Введите жиры (г): ";
            if (!(cin >> fats) || fats < 0 || fats > 100) {
                cout << "Жиры должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                fats = -1;  
            }
        } while (fats < 0 || fats > 100);

        //проверка на ввод белков
        do {
            cout << "Введите белки (г): ";
            if (!(cin >> proteins) || proteins < 0 || proteins > 100) {
                cout << "Белки должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                proteins = -1;  
            }
        } while (proteins < 0 || proteins > 100);

        //проверка на ввод цены
        do {
            cout << "Введите прайс: ";
            if (!(cin >> price) || price < 0) {
                cout << "Цена должна быть положительным числом. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                price = -1;  
            }
        } while (price < 0);

        Nutrients nutrients(carbs, fats, proteins);
        Dish dish(name, category, weight, price, nutrients);

        //после создания блюда пересчитываем калории
        dish.calculateCalories();

        return dish;
    }

public:
    void run() {
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
                Dish newDish = inputDish();
                addDish(newDish);
            } else if (choice == 2) {
                int index;
                cout << "Для удаления введите номер блюда: ";
                cin >> index;
                deleteDish(index - 1);
            } else if (choice == 3) {
                printDishes();
            } else if (choice == 4) {
                printDishesByCategory("Основные блюда");
            } else if (choice == 5) {
                printDishesByCategory("Вторые блюда");
            } else if (choice == 6) {
                printDishesByCategory("Десерты");
            } else if (choice == 7) {
                printDishesByCategory("Напитки");
            } else if (choice == 8) {
                break;
            } else {
                cout << "Неправильный ввод, пожалуйста повторите.\n";
            }
        }
    }
};

//основная функция
int main() {
    DishManager manager;
    manager.run();
    return 0;
}
