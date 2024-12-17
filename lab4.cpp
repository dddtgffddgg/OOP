#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <memory>

using namespace std;

const int MAX_DISHES = 100;

// Forward declaration for friend function
class Nutrients;
class DishManager;
void displayNutrients(const Nutrients& nutrients);

// Абстрактный класс MenuItem
class MenuItem {
public:
    virtual void print(int index) const = 0;
    virtual void calculateCalories() = 0;
    virtual ~MenuItem() {}
};

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

    // Дружественная функция для доступа к приватным членам
    friend void displayNutrients(const Nutrients& nutrients);

    // Дружественный класс
    friend class DishManager;
};

// Дружественная функция для отображения нутриентов
void displayNutrients(const Nutrients& nutrients) {
    cout << "Углеводы: " << nutrients.carbs << " г, "
         << "Жиры: " << nutrients.fats << " г, "
         << "Белки: " << nutrients.proteins << " г" << endl;
}

// Класс Dish наследует от MenuItem
class Dish : public MenuItem {
protected:
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
    void calculateCalories() override {
        calories = nutrients.calculateCalories();
    }

    // Геттеры для сравнения калорий
    float getCalories() const { return calories; }
    string getName() const { return name; }

    // Реализация виртуальных методов из MenuItem
    void print(int index) const override {
        cout << "| " << left << setw(4) << index + 1 << " | "
             << left << setw(15) << name << " | "
             << left << setw(19) << category << " | "
             << right << setw(8) << calories << " | "
             << right << setw(10) << ((category == "Напитки") ? to_string(weight) + " мл" : to_string(weight) + " г") << " | "
             << right << setw(8) << nutrients.getCarbs() << " | "
             << right << setw(8) << nutrients.getFats() << " | "
             << right << setw(8) << nutrients.getProteins() << " | "
             << right << setw(10) << fixed << setprecision(2) << price << " руб. | "
             << left << setw(14) << "" << " |" << endl;
    }

    // Объявление дружественных операторов инкремента и декремента
    friend Dish& operator++(Dish& dish, int); // Постфиксный инкремент
    friend Dish& operator--(Dish& dish, int); // Постфиксный декремент

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

// Класс MainDish наследуется от Dish
class MainDish : public Dish {
public:
    MainDish() : Dish() {}
    MainDish(const string& name, const string& category, int weight, float price, const Nutrients& nutrients)
        : Dish(name, category, weight, price, nutrients) {}

    void print(int index) const override {
        Dish::print(index);
    }
};

// Класс Beverage наследуется от Dish
class Beverage : public Dish {
public:
    Beverage() : Dish() {}
    Beverage(const string& name, const string& category, int weight, float price, const Nutrients& nutrients)
        : Dish(name, category, weight, price, nutrients) {}

    void print(int index) const override {
        Dish::print(index);
    }
};

// Класс HotBeverage наследуется от Beverage
class HotBeverage : public Beverage {
public:
    string temperature; // Дополнительное свойство

    HotBeverage()
        : Beverage(), temperature("") {}

    HotBeverage(const string& name, const string& category, int weight, float price, const Nutrients& nutrients, const string& temperature)
        : Beverage(name, category, weight, price, nutrients), temperature(temperature) {}

    // Перегрузка метода print для отображения температуры
    void print(int index) const override {
        cout << "| " << left << setw(4) << index + 1 << " | "
             << left << setw(15) << name << " | "
             << left << setw(19) << category << " | "
             << right << setw(8) << calories << " | "
             << right << setw(10) << ((category == "Напитки") ? to_string(weight) + " мл" : to_string(weight) + " г") << " | "
             << right << setw(8) << nutrients.getCarbs() << " | "
             << right << setw(8) << nutrients.getFats() << " | "
             << right << setw(8) << nutrients.getProteins() << " | "
             << right << setw(10) << fixed << setprecision(2) << price << " руб. | "
             << left << setw(14) << temperature << " |" << endl;
    }
};

// Класс DishManager
class DishManager {
private:
    MenuItem* dishes[MAX_DISHES];
    int dishCount = 0;

    int getDishCount() const { return dishCount; }

    // Метод для добавления блюда
    void addDish(MenuItem* newDish) {
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
            delete dishes[index]; // Освобождение памяти
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

    // Метод для копирования блюда
    void copyDish(int index) {
        if (index >= 0 && index < dishCount) {
            if (dishCount >= MAX_DISHES) {
                cout << "Невозможно добавить больше блюд.\n";
                return;
            }
            // Определяем тип блюда и создаем копию соответствующего типа
            MenuItem* original = dishes[index];
            MenuItem* copiedDish = nullptr;

            if (HotBeverage* hb = dynamic_cast<HotBeverage*>(original)) {
                copiedDish = new HotBeverage(*hb);
            }
            else if (Beverage* b = dynamic_cast<Beverage*>(original)) {
                copiedDish = new Beverage(*b);
            }
            else if (MainDish* md = dynamic_cast<MainDish*>(original)) {
                copiedDish = new MainDish(*md);
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

    // Метод для присваивания одного блюда другому
    void assignDish(int sourceIndex, int destIndex) {
        if (sourceIndex >= 0 && sourceIndex < dishCount && destIndex >= 0 && destIndex < dishCount) {
            // Определяем тип исходного блюда
            MenuItem* source = dishes[sourceIndex];
            MenuItem* dest = dishes[destIndex];

            // Удаляем текущий dest
            delete dest;

            // Копируем источник в пункт назначения
            if (HotBeverage* hb = dynamic_cast<HotBeverage*>(source)) {
                dishes[destIndex] = new HotBeverage(*hb);
            }
            else if (Beverage* b = dynamic_cast<Beverage*>(source)) {
                dishes[destIndex] = new Beverage(*b);
            }
            else if (MainDish* md = dynamic_cast<MainDish*>(source)) {
                dishes[destIndex] = new MainDish(*md);
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

    // Метод для печати заголовка таблицы
    void printTableHeader() const {
        cout << "| " << left << setw(6) << "№" 
             << " | " << left << setw(22) << "Название" 
             << " | " << left << setw(20) << "Категория" 
             << " | " << right << setw(15) << "Калории" 
             << " | " << right << setw(12) << "Вес" 
             << " | " << right << setw(15) << "Углеводы" 
             << " | " << right << setw(12) << "Жиры" 
             << " | " << right << setw(7) << "Белки" 
             << " | " << right << setw(18) << "Цена" 
             << " | " << left << setw(20) << "Температура" << " |" << endl;
        cout << string(135, '-') << endl;
    }

    // Метод для печати всех блюд
    void printDishes() const {
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

    // Метод для печати блюд по категории
    void printDishesByCategory(const string& categoryName, bool hotOnly = false) const {
        bool found = false;
        printTableHeader();
        for (int i = 0; i < dishCount; ++i) {
            Dish* dish = dynamic_cast<Dish*>(dishes[i]);
            if (dish && dish->category == categoryName) {
                if (hotOnly) {
                    if (dynamic_cast<HotBeverage*>(dish)) {
                        found = true;
                        dishes[i]->print(i);
                    }
                }
                else {
                    found = true;
                    dishes[i]->print(i);
                }
            }
        }
        cout << string(142, '-') << endl;
        if (!found) {
            cout << "Нет блюд в категории \"" << categoryName << "\".\n";
        }
        cout << endl;
    }

    // Метод для сравнения калорий двух блюд
    void compareCalories(int index1, int index2) { // сравнение калорий двух блюд
        if (index1 >= 0 && index1 < dishCount && index2 >= 0 && index2 < dishCount) {
            Dish* dish1 = dynamic_cast<Dish*>(dishes[index1]);
            Dish* dish2 = dynamic_cast<Dish*>(dishes[index2]);

            if (dish1 && dish2) {
                cout << "\nСравнение калорий:\n";
                cout << "Блюдо 1: " << dish1->getName() << " (" << dish1->getCalories() << " калорий)\n";
                cout << "Блюдо 2: " << dish2->getName() << " (" << dish2->getCalories() << " калорий)\n";

                if (dish1->getCalories() > dish2->getCalories()) {
                    cout << "Блюдо \"" << dish1->getName() << "\" содержит больше калорий.\n";
                }
                else if (dish1->getCalories() < dish2->getCalories()) {
                    cout << "Блюдо \"" << dish2->getName() << "\" содержит больше калорий.\n";
                }
                else {
                    cout << "Оба блюда содержат одинаковое количество калорий.\n";
                }
            }
            else {
                cout << "Ошибка: невозможно сравнить выбранные блюда.\n";
            }
        }
        else {
            cout << "Ошибка: неверные индексы блюд для сравнения.\n";
        }
    }

    // Метод для увеличения веса блюда
    void incrementDishWeight(int index) {
        if (index >= 0 && index < dishCount) {
            Dish* dish = dynamic_cast<Dish*>(dishes[index]);
            if (dish) {
                (*dish)++; // Постфиксный инкремент без создания временных объектов
                cout << "Вес блюда увеличен: ";
                dishes[index]->print(index);
            }
        }
        else {
            cout << "Неверный номер блюда.\n";
        }
    }

    // Метод для уменьшения веса блюда
    void decrementDishWeight(int index) {
        if (index >= 0 && index < dishCount) {
            Dish* dish = dynamic_cast<Dish*>(dishes[index]);
            if (dish) {
                (*dish)--; // Постфиксный декремент без создания временных объектов
                cout << "Вес блюда уменьшен: ";
                dishes[index]->print(index);
            }
        }
        else {
            cout << "Неверный номер блюда.\n";
        }
    }

    // Метод для ввода данных о блюде
    MenuItem* inputDish() {
        string name, category;
        int weight, categoryChoice;
        float price, carbs, fats, proteins;
        int dishTypeChoice;
        string temperature = ""; // Для HotBeverage

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

        // Выбор типа напитка, если категория "Напитки"
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

        // Создание объекта в зависимости от типа блюда
        if (category == "Напитки") {
            if (dishTypeChoice == 1) { // Охлажденный напиток
                return new Beverage(name, category, weight, price, nutrients);
            }
            else { // Горячий напиток
                // Устанавливаем температуру на основе выбора
                temperature = "Горячий";
                return new HotBeverage(name, category, weight, price, nutrients, temperature);
            }
        }
        else {
            // Для остальных категорий создаем MainDish
            return new MainDish(name, category, weight, price, nutrients);
        }
    }

public:
    // Конструктор
    DishManager() {
        for (int i = 0; i < MAX_DISHES; ++i) {
            dishes[i] = nullptr;
        }
    }

    // Деструктор для освобождения памяти
    ~DishManager() {
        for (int i = 0; i < dishCount; ++i) {
            delete dishes[i];
        }
    }

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
            cout << "8. Вывод горячих напитков\n"; // Новая опция
            cout << "9. Увеличить вес блюда\n";
            cout << "10. Уменьшить вес блюда\n";
            cout << "11. Сравнить калории блюд\n";
            cout << "12. Копировать блюдо\n";
            cout << "13. Присвоить одно блюдо другому\n";
            cout << "14. Показать нутриенты блюда\n";
            cout << "15. Выход\n"; // Новая опция выхода
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
            else if (choice == 8) { // Новая опция
                printDishesByCategory("Напитки", true); // Вывод только горячих напитков
            }
            else if (choice == 9) {
                int index;
                cout << "Введите номер блюда для увеличения веса: ";
                cin >> index;
                incrementDishWeight(index - 1);
            }
            else if (choice == 10) {
                int index;
                cout << "Введите номер блюда для уменьшения веса: ";
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
                    Dish* dish = dynamic_cast<Dish*>(dishes[index - 1]);
                    if (dish) {
                        displayNutrients(dish->nutrients);
                    }
                    else {
                        cout << "Ошибка: выбранный объект не является блюдом.\n";
                    }
                }
                else {
                    cout << "Неверный номер блюда.\n";
                }
            }
            else if (choice == 15) { // Новая опция выхода
                break;
            }
            else {
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
