#include <iostream>
#include <iomanip> 
#include <string>
#include <limits> //для std::numeric_limits

using namespace std;

const int MAX_DISHES = 100;

// Класс для хранения информации о БЖУ (углеводы, жиры, белки)
class Nutrients { 
private:
    float carbs;    // углеводы
    float fats;     // жиры
    float proteins; // белки

public:
    // Конструктор Nutrients с параметрами по умолчанию
    Nutrients(float carbs = 0.0, float fats = 0.0, float proteins = 0.0)
        : carbs(carbs), fats(fats), proteins(proteins) {}

    // Геттеры для БЖУ
    float getCarbs() const { return carbs; }
    float getFats() const { return fats; }
    float getProteins() const { return proteins; }

    // Сеттеры для БЖУ
    void setCarbs(float value) { carbs = value; }
    void setFats(float value) { fats = value; }
    void setProteins(float value) { proteins = value; }

    // Метод для вычисления калорийности на основе БЖУ
    float calculateCalories() const {
        return (carbs * 4) + (fats * 9) + (proteins * 4); // Калории = углеводы * 4 + жиры * 9 + белки * 4
    }
};

// Класс для хранения информации о блюде
class Dish { 
private:
    string name;         // Название блюда
    string category;     // Категория блюда
    int weight;          // Вес блюда (г или мл)
    float price;         // Цена блюда
    Nutrients nutrients; // Информация о БЖУ
    float calories;      // Калорийность блюда

public:
    // Конструктор по умолчанию
    Dish() 
        : name(""), category(""), weight(0), price(0.0), nutrients(), calories(0.0) {}

    // Конструктор с основными параметрами
    Dish(const string& name, const string& category, int weight)
        : name(name), category(category), weight(weight), price(0.0), nutrients(), calories(0.0) {}

    // Конструктор со всеми параметрами
    Dish(const string& name, const string& category, int weight, float price, const Nutrients& nutrients)
        : name(name), category(category), weight(weight), price(price), nutrients(nutrients), calories(0.0) {
        // При создании блюда сразу вычисляем калории
        calculateCalories();
    }

    // Сеттеры для полей класса
    void setName(const string& name) { this->name = name; }
    void setCategory(const string& category) { this->category = category; }
    void setWeight(int weight) { this->weight = weight; }
    void setPrice(float price) { this->price = price; }
    void setNutrients(const Nutrients& nutrients) { this->nutrients = nutrients; }

    // Метод для расчета калорий
    void calculateCalories() {
        calories = nutrients.calculateCalories(); // Получаем калории через класс Nutrients
    }

    // Метод для вывода информации о блюде
    void print(int index) const {
        cout << "| " << left << setw(5) << index + 1
             << "| " << setw(16) << name
             << "| " << setw(20) << category
             << "| " << setw(10) << fixed << setprecision(1) << calories
             << "| " << setw(12) << (to_string(weight) + (category == "Напитки" ? " мл" : " г"))
             << "| " << setw(10) << nutrients.getCarbs()
             << "| " << setw(10) << nutrients.getFats()
             << "| " << setw(10) << nutrients.getProteins()
             << "| " << setw(10) << fixed << setprecision(2) << price << " руб." << " |" << endl;
    }

    // Делаем доступ к закрытым методам для класса DishManager
    friend class DishManager;
};

// Класс для управления списком блюд // Менеджер блюд
class DishManager { 
private:
    Dish dishes[MAX_DISHES]; // Массив блюд
    int dishCount = 0;       // Текущее количество блюд

    // Метод для получения текущего количества блюд
    int getDishCount() const { return dishCount; }

    // Метод для добавления блюда по объекту
    void addDish(const Dish& newDish) { 
        if (dishCount < MAX_DISHES) { 
            dishes[dishCount++] = newDish;
            cout << "Блюдо добавлено!\n\n";
        } else {
            cout << "Невозможно добавить больше блюд.\n";
        }
    }

    // Перегруженный метод для добавления блюда по параметрам
    void addDish(const string& name, const string& category, int weight, float price, const Nutrients& nutrients) {
        if (dishCount < MAX_DISHES) {
            dishes[dishCount++] = Dish(name, category, weight, price, nutrients);
            cout << "Блюдо добавлено!\n\n";
        } else {
            cout << "Невозможно добавить больше блюд.\n";
        }
    }

    // Метод для удаления блюда по индексу
    void deleteDish(int index) { 
        if (index >= 0 && index < dishCount) {
            for (int i = index; i < dishCount - 1; ++i) {
                dishes[i] = dishes[i + 1];
            }
            --dishCount;
            cout << "Блюдо удалено!\n";
        } else {
            cout << "Неправильный ввод. Укажите корректный номер блюда.\n";
        }
    }

    // Метод для вывода заголовка таблицы
    void printTableHeader() const {
        cout << "| " << left << setw(7) << "№" 
             << "| " << setw(25) << "Название" 
             << "| " << setw(20) << "Категория" 
             << "| " << setw(19) << "Калории" 
             << "| " << setw(15) << "Вес" 
             << "| " << setw(11) << "Углеводы" 
             << "| " << setw(14) << "Жиры" 
             << "| " << setw(15) << "Белки" 
             << "| " << setw(18) << "Цена" << " |" << endl;
        cout << string(130, '-') << endl;
    }

    // Метод для вывода всех блюд
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

    // Перегруженный метод для вывода блюд по категории
    void printDishes(const string& categoryName) const {
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

    // Метод для ввода данных блюда с проверкой диапазона и корректности
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

        // Проверка на корректность ввода категории
        while (!(cin >> categoryChoice) || categoryChoice < 1 || categoryChoice > 4) {
            cout << "Неправильный ввод. Введите номер категории (1-4): ";
            cin.clear();  // Сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем буфер
        }

        // Установка категории на основе выбора пользователя
        switch (categoryChoice) {
            case 1: category = "Основные блюда"; break;
            case 2: category = "Вторые блюда"; break;
            case 3: category = "Десерты"; break;
            case 4: category = "Напитки"; break;
        }

        // Проверка на ввод веса
        do {
            cout << "Введите вес (в граммах или мл): ";
            if (!(cin >> weight) || weight <= 0) {
                cout << "Вес должен быть положительным числом. Повторите ввод.\n";
                cin.clear();  // Сбрасываем флаг ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем буфер
                weight = -1;  // Устанавливаем некорректное значение для продолжения цикла
            }
        } while (weight <= 0);

        // Проверка на ввод углеводов
        do {
            cout << "Введите углеводы (г, от 0 до 100): ";
            if (!(cin >> carbs) || carbs < 0 || carbs > 100) {
                cout << "Углеводы должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
                cin.clear();  // Сбрасываем флаг ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем буфер
                carbs = -1;  // Некорректное значение для повторного ввода
            }
        } while (carbs < 0 || carbs > 100);

        // Проверка на ввод жиров
        do {
            cout << "Введите жиры (г, от 0 до 100): ";
            if (!(cin >> fats) || fats < 0 || fats > 100) {
                cout << "Жиры должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
                cin.clear();  // Сбрасываем флаг ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем буфер
                fats = -1;  
            }
        } while (fats < 0 || fats > 100);

        // Проверка на ввод белков
        do {
            cout << "Введите белки (г, от 0 до 100): ";
            if (!(cin >> proteins) || proteins < 0 || proteins > 100) {
                cout << "Белки должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
                cin.clear();  // Сбрасываем флаг ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем буфер
                proteins = -1;  
            }
        } while (proteins < 0 || proteins > 100);

        // Проверка на ввод цены
        do {
            cout << "Введите цену (руб.): ";
            if (!(cin >> price) || price < 0) {
                cout << "Цена должна быть положительным числом. Повторите ввод.\n";
                cin.clear();  // Сбрасываем флаг ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем буфер
                price = -1;  
            }
        } while (price < 0);

        // Создание объекта Nutrients и блюда
        Nutrients nutrients(carbs, fats, proteins);
        Dish dish(name, category, weight, price, nutrients);

        // Пересчитываем калории
        dish.calculateCalories();

        return dish;
    }

public:
    // Перегруженный метод для добавления блюда с вводом параметров
    void addDish() {
        // Вызов метода inputDish для ввода данных через пользовательский ввод
        Dish newDish = inputDish();
        addDish(newDish); // Вызов перегруженного метода добавления по объекту
    }

    // Перегруженный метод для добавления блюда по параметрам (не через ввод)
    void addDishDirect(const string& name, const string& category, int weight, float price, const Nutrients& nutrients) {
        addDish(name, category, weight, price, nutrients); // Вызов перегруженного метода добавления по параметрам
    }

    // Перегруженный метод для вывода блюд по категории
    void printDishesByCategory(const string& categoryName) const {
        printDishes(categoryName); // Вызов перегруженного метода вывода по категории
    }

    // Основной метод для запуска программы
    void run() {
        int choice;
        while (true) {
            // Вывод меню
            cout << "\nМеню:\n";
            cout << "1. Добавить блюдо (через ввод)\n";
            cout << "2. Добавить блюдо (по параметрам)\n";
            cout << "3. Удалить блюдо\n";
            cout << "4. Вывод всех блюд\n";
            cout << "5. Вывод основных блюд\n";
            cout << "6. Вывод вторых блюд\n";
            cout << "7. Вывод десертов\n";
            cout << "8. Вывод напитков\n";
            cout << "9. Выход\n";
            cout << "Введите свой выбор: ";
            cin >> choice;

            if (choice == 1) {
                // Добавление блюда через ввод
                addDish();
            } else if (choice == 2) {
                // Добавление блюда по параметрам без ввода
                string name, category;
                int weight;
                float price, carbs, fats, proteins;

                cout << "Введите название: ";
                cin.ignore();  
                getline(cin, name);

                cout << "Выберите категорию:\n1 - Основные блюда\n2 - Вторые блюда\n3 - Десерты\n4 - Напитки\nВведите номер категории: ";
                while (!(cin >> choice) || choice < 1 || choice > 4) {
                    cout << "Неправильный ввод. Введите номер категории (1-4): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                switch (choice) {
                    case 1: category = "Основные блюда"; break;
                    case 2: category = "Вторые блюда"; break;
                    case 3: category = "Десерты"; break;
                    case 4: category = "Напитки"; break;
                }

                cout << "Введите вес (г, положительное число): ";
                while (!(cin >> weight) || weight <= 0) {
                    cout << "Ошибка! Вес должен быть положительным числом: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Введите углеводы (г, от 0 до 100): ";
                while (!(cin >> carbs) || carbs < 0 || carbs > 100) {
                    cout << "Ошибка! Углеводы должны быть от 0 до 100: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Введите жиры (г, от 0 до 100): ";
                while (!(cin >> fats) || fats < 0 || fats > 100) {
                    cout << "Ошибка! Жиры должны быть от 0 до 100: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Введите белки (г, от 0 до 100): ";
                while (!(cin >> proteins) || proteins < 0 || proteins > 100) {
                    cout << "Ошибка! Белки должны быть от 0 до 100: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Введите цену (руб., положительное число): ";
                while (!(cin >> price) || price < 0) {
                    cout << "Ошибка! Цена должна быть положительным числом: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // Создание объекта Nutrients и блюда
                Nutrients nutrients(carbs, fats, proteins);
                addDishDirect(name, category, weight, price, nutrients); // Вызов перегруженного метода
            } else if (choice == 3) {
                // Удаление блюда
                int index;
                cout << "Введите номер блюда для удаления: ";
                cin >> index;
                deleteDish(index - 1);
            } else if (choice == 4) {
                // Вывод всех блюд
                printDishes();
            } else if (choice == 5) {
                // Вывод основных блюд
                printDishesByCategory("Основные блюда");
            } else if (choice == 6) {
                // Вывод вторых блюд
                printDishesByCategory("Вторые блюда");
            } else if (choice == 7) {
                // Вывод десертов
                printDishesByCategory("Десерты");
            } else if (choice == 8) {
                // Вывод напитков
                printDishesByCategory("Напитки");
            } else if (choice == 9) {
                // Выход из программы
                cout << "Выход из программы. До свидания!\n";
                break;
            } else {
                // Обработка неправильного ввода
                cout << "Неправильный ввод, пожалуйста повторите.\n";
            }
        }
    }
};

int main() {
    DishManager manager; // Создание объекта менеджера блюд
    manager.run();       // Запуск программы
    return 0;
}
