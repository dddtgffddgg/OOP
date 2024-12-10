#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int MAX_DISHES = 100;

// Класс Nutrients
class Nutrients {
private:
    float carbs;    // Углеводы
    float fats;     // Жиры
    float proteins; // Белки

public:
    // Конструктор по умолчанию и с параметрами
    Nutrients(float carbs = 0.0, float fats = 0.0, float proteins = 0.0)
        : carbs(carbs), fats(fats), proteins(proteins) {}

    // Копирующий конструктор
    Nutrients(const Nutrients& other)
        : carbs(other.carbs), fats(other.fats), proteins(other.proteins) {}

    // Оператор присваивания
    Nutrients& operator=(const Nutrients& other) {
        if (this != &other) {
            carbs = other.carbs;
            fats = other.fats;
            proteins = other.proteins;
        }
        return *this;
    }

    // Геттеры
    float getCarbs() const { return carbs; }
    float getFats() const { return fats; }
    float getProteins() const { return proteins; }

    // Сеттеры
    void setCarbs(float value) { carbs = value; }
    void setFats(float value) { fats = value; }
    void setProteins(float value) { proteins = value; }

    // Метод для расчета калорий
    float calculateCalories() const {
        return (carbs * 4) + (fats * 9) + (proteins * 4); // Калории = Углеводы * 4 + Жиры * 9 + Белки * 4
    }
};

// Предварительное объявление класса DishManager для объявления дружественных функций
class DishManager;

// Класс Dish
class Dish {
private:
    string name;
    string category;
    int weight;
    float price;
    Nutrients nutrients;
    float calories;

public:
    // Конструкторы
    Dish()
        : name(""), category(""), weight(0), price(0.0), nutrients(), calories(0.0) {}

    Dish(const string& name, const string& category, int weight)
        : name(name), category(category), weight(weight), price(0.0), nutrients(), calories(0.0) {}

    Dish(const string& name, const string& category, int weight, float price, const Nutrients& nutrients)
        : name(name), category(category), weight(weight), price(price), nutrients(nutrients), calories(0.0) {
        calculateCalories();
    }

    // Копирующий конструктор
    Dish(const Dish& other)
        : name(other.name), category(other.category), weight(other.weight),
          price(other.price), nutrients(other.nutrients), calories(other.calories) {}

    // Оператор присваивания без использования `this->`
    Dish& operator=(const Dish& other) {
        if (&other != this) { // Проверка самоприсваивания
            name = other.name;
            category = other.category;
            weight = other.weight;
            price = other.price;
            nutrients = other.nutrients;
            calories = other.calories;
        }
        return *this;
    }

    // Сеттеры
    void setName(const string& name) { this->name = name; }
    void setCategory(const string& category) { this->category = category; }
    void setWeight(int weight) { this->weight = weight; }
    void setPrice(float price) { this->price = price; }
    void setNutrients(const Nutrients& nutrients) { this->nutrients = nutrients; }

    // Метод для расчета калорий
    void calculateCalories() {
        calories = nutrients.calculateCalories();
    }

    // Метод для вывода информации о блюде
    void print(int index) const {
        cout << "| " << left << setw(5) << index + 1
             << "| " << setw(16) << name
             << "| " << setw(20) << category
             << "| " << setw(10) << calories
             << "| " << setw(12) << ((category == "Напитки") ? to_string(weight) + " мл" : to_string(weight) + " г")
             << "| " << setw(10) << nutrients.getCarbs()
             << "| " << setw(10) << nutrients.getFats()
             << "| " << setw(10) << nutrients.getProteins()
             << "| " << setw(10) << fixed << setprecision(2) << price << " руб." << " |" << endl;
    }

    // Объявление дружественных операторов инкремента и декремента
    friend Dish& operator++(Dish& dish, int); // Постфиксный инкремент
    friend Dish& operator--(Dish& dish, int); // Постфиксный декремент

    // Геттеры для сравнения калорий
    float getCalories() const { return calories; }
    string getName() const { return name; }

    // Дружественный класс DishManager
    friend class DishManager;
};

// Реализация оператора постфиксного инкремента без создания временных объектов и без использования `this`
Dish& operator++(Dish& dish, int) { // Постфиксный инкремент
    dish.weight++;               // Увеличиваем вес
    dish.calculateCalories();    // Пересчитываем калории
    return dish;                 // Возвращаем ссылку на текущий объект
}

// Реализация оператора постфиксного декремента без создания временных объектов и без использования `this`
Dish& operator--(Dish& dish, int) { // Постфиксный декремент
    if (dish.weight > 0) {        // Уменьшаем вес, если он больше 0
        dish.weight--;
        dish.calculateCalories();
    }
    return dish;                 // Возвращаем ссылку на текущий объект
}

// Класс DishManager
class DishManager {
private:
    Dish dishes[MAX_DISHES];
    int dishCount = 0;

    int getDishCount() const { return dishCount; }

    // Метод для добавления блюда
    void addDish(const Dish& newDish) {
        if (dishCount < MAX_DISHES) {
            dishes[dishCount++] = newDish;
            cout << "Блюдо добавлено!\n\n";
        } else {
            cout << "Невозможно добавить больше блюд.\n";
        }
    }

    // Метод для удаления блюда
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

    // Метод для копирования блюда
    void copyDish(int index) {
        if (index >= 0 && index < dishCount) {
            if (dishCount >= MAX_DISHES) {
                cout << "Невозможно добавить больше блюд.\n";
                return;
            }
            Dish copiedDish = dishes[index]; // Используем копирующий конструктор
            addDish(copiedDish);
            cout << "Блюдо успешно скопировано.\n";
        } else {
            cout << "Неверный номер блюда для копирования.\n";
        }
    }

    // Метод для присваивания одного блюда другому
    void assignDish(int sourceIndex, int destIndex) {
        if (sourceIndex >= 0 && sourceIndex < dishCount && destIndex >= 0 && destIndex < dishCount) {
            dishes[destIndex] = dishes[sourceIndex]; // Используем оператор присваивания
            cout << "Блюдо успешно присвоено.\n";
        } else {
            cout << "Неверные номера блюд для присваивания.\n";
        }
    }

    // Метод для печати заголовка таблицы
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

    // Метод для печати всех блюд
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

    // Метод для печати блюд по категории
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

    // Метод для сравнения калорий двух блюд
    void compareCalories(int index1, int index2) { // сравнение калорий двух блюд
        if (index1 >= 0 && index1 < dishCount && index2 >= 0 && index2 < dishCount) {
            Dish& dish1 = dishes[index1];
            Dish& dish2 = dishes[index2];
            
            cout << "\nСравнение калорий:\n";
            cout << "Блюдо 1: " << dish1.getName() << " (" << dish1.getCalories() << " калорий)\n";
            cout << "Блюдо 2: " << dish2.getName() << " (" << dish2.getCalories() << " калорий)\n";
            
            if (dish1.getCalories() > dish2.getCalories()) {
                cout << "Блюдо \"" << dish1.getName() << "\" содержит больше калорий.\n";
            } else if (dish1.getCalories() < dish2.getCalories()) {
                cout << "Блюдо \"" << dish2.getName() << "\" содержит больше калорий.\n";
            } else {
                cout << "Оба блюда содержат одинаковое количество калорий.\n";
            }
        } else {
            cout << "Ошибка: неверные индексы блюд для сравнения.\n";
        }
    }

    // Метод для увеличения веса блюда
    void incrementDishWeight(int index) {
        if (index >= 0 && index < dishCount) {
            dishes[index]++; // Постфиксный инкремент без создания временных объектов
            cout << "Вес блюда увеличен: ";
            dishes[index].print(index);
        } else {
            cout << "Неверный номер блюда.\n";
        }
    }

    // Метод для уменьшения веса блюда
    void decrementDishWeight(int index) {
        if (index >= 0 && index < dishCount) {
            dishes[index]--; // Постфиксный декремент без создания временных объектов
            cout << "Вес блюда уменьшен: ";
            dishes[index].print(index);
        } else {
            cout << "Неверный номер блюда.\n";
        }
    }

    // Метод для ввода данных о блюде
    Dish inputDish() {
        string name, category;
        int weight, categoryChoice;
        float price, carbs, fats, proteins;

        cout << "Введите название: ";
        cin.ignore(); // Очистка буфера ввода перед getline
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
            case 2: category = "Вторые блюда"; break;
            case 3: category = "Десерты"; break;
            case 4: category = "Напитки"; break;
        }

        // Ввод веса
        do {
            cout << "Введите вес (в граммах или мл): ";
            if (!(cin >> weight) || weight <= 0) {
                cout << "Вес должен быть положительным числом. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                weight = -1;
            }
        } while (weight <= 0);

        // Ввод цены
        do {
            cout << "Введите цену: ";
            if (!(cin >> price) || price < 0) {
                cout << "Цена должна быть положительным числом. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                price = -1;
            }
        } while (price < 0);

        // Ввод углеводов
        do {
            cout << "Введите углеводы (г): ";
            if (!(cin >> carbs) || carbs < 0 || carbs > 100) {
                cout << "Углеводы должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                carbs = -1;
            }
        } while (carbs < 0 || carbs > 100);

        // Ввод жиров
        do {
            cout << "Введите жиры (г): ";
            if (!(cin >> fats) || fats < 0 || fats > 100) {
                cout << "Жиры должны быть в диапазоне от 0 до 100. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                fats = -1;
            }
        } while (fats < 0 || fats > 100);

        // Ввод белков
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
        Dish dish(name, category, weight, price, nutrients);
        dish.calculateCalories();

        return dish;
    }

public:
    // Основной метод для запуска менеджера
    void run() {
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
            cout << "8. Выход\n";
            cout << "9. Увеличить вес блюда\n";
            cout << "10. Уменьшить вес блюда\n";
            cout << "11. Сравнить калории блюд\n";
            cout << "12. Копировать блюдо\n";
            cout << "13. Присвоить одно блюдо другому\n";
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
            } else if (choice == 9) {
                int index;
                cout << "Введите номер блюда для увеличения веса: ";
                cin >> index;
                incrementDishWeight(index - 1);
            } else if (choice == 10) {
                int index;
                cout << "Введите номер блюда для уменьшения веса: ";
                cin >> index;
                decrementDishWeight(index - 1);
            } else if (choice == 11) {
                int index1, index2;
                cout << "Введите номер первого блюда для сравнения: ";
                cin >> index1;
                cout << "Введите номер второго блюда для сравнения: ";
                cin >> index2;
                compareCalories(index1 - 1, index2 - 1);
            } else if (choice == 12) {
                int index;
                cout << "Введите номер блюда для копирования: ";
                cin >> index;
                copyDish(index - 1);
            } else if (choice == 13) {
                int sourceIndex, destIndex;
                cout << "Введите номер исходного блюда: ";
                cin >> sourceIndex;
                cout << "Введите номер блюда, которому нужно присвоить данные: ";
                cin >> destIndex;
                assignDish(sourceIndex - 1, destIndex - 1);
            } else {
                cout << "Неправильный ввод, пожалуйста, повторите.\n";
            }
        }
    }
};

// Основная функция
int main() {
    DishManager manager;
    manager.run();
    return 0;
}
