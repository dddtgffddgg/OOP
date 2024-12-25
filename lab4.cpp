#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

//макс кол-во блюд
const int MAX_DISHES = 100;

//хранит все нутриенты
class Nutrients {
private:
    float carbs;   
    float fats;     
    float proteins; 

public:
    //конструктор по умолчанию и с параметрами
    Nutrients(float carbs = 0.0, float fats = 0.0, float proteins = 0.0)
        : carbs(carbs), fats(fats), proteins(proteins) {}

    //копирующий конструктор
    Nutrients(const Nutrients& other)
        : carbs(other.carbs), fats(other.fats), proteins(other.proteins) {}

    //оператор присваивания
    Nutrients& operator=(const Nutrients& other) {
        if (this != &other) {
            carbs = other.carbs;
            fats = other.fats;
            proteins = other.proteins;
        }
        return *this;
    }

    float getCarbs() const { return carbs; }
    float getFats() const { return fats; }
    float getProteins() const { return proteins; }

    void setCarbs(float value) { carbs = value; }
    void setFats(float value) { fats = value; }
    void setProteins(float value) { proteins = value; }

    //метод для расчета калорий
    float calculateCalories() const {
        //калории = (углеводы * 4) + (жиры * 9) + (белки * 4)
        return (carbs * 4) + (fats * 9) + (proteins * 4);
    }
};

//объявления для дружественных функций и классов
class DishManager;
void displayNutrients(const Nutrients& nutrients);

//абстрактный класс, который содержит всю инфу
class MenuItem {
protected:
    string name;         
    string category;     
    float price;         
    Nutrients nutrients;
    float calories;      

public:
    //конструктор по умолчанию
    MenuItem()
        : name(""), category(""), price(0.0), nutrients(), calories(0.0) {}

    //конструктор с параметрами без нутриентов (для наглядности, если нужно)
    MenuItem(const string& name, const string& category, float price)
        : name(name), category(category), price(price), nutrients(), calories(0.0) {}

    //конструктор с параметрами, включая нутриенты
    MenuItem(const string& name, const string& category, float price, const Nutrients& nutrients)
        : name(name), category(category), price(price), nutrients(nutrients), calories(0.0) 
    {}

    //копирующий конструктор
    MenuItem(const MenuItem& other)
        : name(other.name),
          category(other.category),
          price(other.price),
          nutrients(other.nutrients),
          calories(other.calories) {}

    //оператор присваивания
    MenuItem& operator=(const MenuItem& other) {
        if (this != &other) {
            name = other.name;
            category = other.category;
            price = other.price;
            nutrients = other.nutrients;
            calories = other.calories;
        }
        return *this;
    }

    //виртуальный деструктор
    virtual ~MenuItem() {}

    //чисто виртуальный метод для печати информации о блюде
    virtual void print(int index) const = 0;

    //чисто виртуальный метод для расчёта калорий
    virtual void calculateCalories() = 0;

    void setName(const string& name) { this->name = name; }
    void setCategory(const string& category) { this->category = category; }
    void setPrice(float price) { this->price = price; }
    void setNutrients(const Nutrients& nutrients) { this->nutrients = nutrients; }

    float getCalories() const { return calories; }
    string getName() const { return name; }
    string getCategory() const { return category; }

    //доступ к нутриентам
    Nutrients& getNutrients() { return nutrients; }
    const Nutrients& getNutrients() const { return nutrients; }

    //дружественная функция, вывод нутриентов
    friend void displayNutrients(const Nutrients& nutrients);
    friend class DishManager;
};

//для отображения нутриентов (дружественная функция)
void displayNutrients(const Nutrients& nutrients) {
    cout << "Углеводы: " << nutrients.getCarbs() << " г, "
         << "Жиры: " << nutrients.getFats() << " г, "
         << "Белки: " << nutrients.getProteins() << " г" << endl;
}

//класс Dish наследуется от MenuItem
class Dish : public MenuItem {
protected:
    int weight; //вес в граммах

public:
    //конструкторы
    Dish()
        : MenuItem(), weight(0) {}

    //конструктор без цены/нутриентов (пример)
    Dish(const string& name, const string& category, int weight)
        : MenuItem(name, category, 0.0), weight(weight) {}

    //полный конструктор
    Dish(const string& name, const string& category, int weight, float price, const Nutrients& nutrients)
        : MenuItem(name, category, price, nutrients), weight(weight) 
    {
        calculateCalories();
    }

    //копирующий конструктор
    Dish(const Dish& other)
        : MenuItem(other), // важный вызов базового копирующего конструктора
          weight(other.weight)
    {
    }

    //оператор присваивания
    Dish& operator=(const Dish& other) {
        if (this != &other) {
            //сначала вызываем оператор присваивания базового класса
            MenuItem::operator=(other);
            weight = other.weight;
        }
        return *this;
    }

    //для веса
    void setWeight(int weight) { this->weight = weight; }
    int getWeight() const { return weight; }

    //переопределяем calculateCalories() через нутриенты
    void calculateCalories() override {
        calories = nutrients.calculateCalories();
    }

    void print(int index) const override {
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

    //объявление дружественных операторов инкремента/декремента (постфиксных)
    friend Dish& operator++(Dish& dish, int);
    friend Dish& operator--(Dish& dish, int);
};

//постфиксный инкремент: увеличивает вес блюда Dish
Dish& operator++(Dish& dish, int) {
    dish.weight++;
    dish.calculateCalories();
    return dish;
}

//постфиксный декремент: уменьшает вес блюда Dish
Dish& operator--(Dish& dish, int) {
    if (dish.weight > 0) {
        dish.weight--;
        dish.calculateCalories();
    }
    return dish;
}

//наследуется от MenuItem и записывает объем напитка
class Beverage : public MenuItem {
protected:
    int volume; //объём в мл

public:
    //конструкторы
    Beverage()
        : MenuItem(), volume(0) {}

    /*//простой конструктор (без цены/нутриентов)
    Beverage(const string& name, const string& category, int volume)
        : MenuItem(name, category, 0.0), volume(volume) {}*/

    //полный конструктор
    Beverage(const string& name, const string& category, int volume, float price, const Nutrients& nutrients)
        : MenuItem(name, category, price, nutrients), volume(volume)
    {
        calculateCalories();
    }

    //копирующий конструктор
    Beverage(const Beverage& other)
        : MenuItem(other),
          volume(other.volume)
    {
    }

    //оператор присваивания
    Beverage& operator=(const Beverage& other) {
        if (this != &other) {
            MenuItem::operator=(other);
            volume = other.volume;
        }
        return *this;
    }

    //для объёма
    void setVolume(int volume) { this->volume = volume; }
    int getVolume() const { return volume; }

    //переопределяем метод для расчёта калорий
    void calculateCalories() override {
        calories = nutrients.calculateCalories();
    }

    void print(int index) const override {
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
};

//добавляет поле температуру
class TempBeverage : public Beverage {
public:
    string temperature; //температура (например, "Горячий" или "Охлажденный")

    //конструкторы
    TempBeverage()
        : Beverage(), temperature("") {}

    TempBeverage(const string& name, const string& category, int volume, float price,
                const Nutrients& nutrients, const string& temperature)
        : Beverage(name, category, volume, price, nutrients),
          temperature(temperature) {}

    //копирующий конструктор
    TempBeverage(const TempBeverage& other)
        : Beverage(other),
          temperature(other.temperature)
    {
    }

    //оператор присваивания
    TempBeverage& operator=(const TempBeverage& other) {
        if (this != &other) {
            Beverage::operator=(other);
            temperature = other.temperature;
        }
        return *this;
    }

    //добавление столбца температуры
    void print(int index) const override {
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
};

//менеджер блюд
class DishManager {
private:
    MenuItem* dishes[MAX_DISHES]; //массив указателей на объекты MenuItem
    int dishCount = 0;           

    //получение текущего колва блюд
    int getDishCount() const { return dishCount; }

    //метод для добавления блюда
    void addDish(MenuItem* newDish) {
        if (dishCount < MAX_DISHES) {
            dishes[dishCount++] = newDish;
            cout << "Блюдо добавлено!\n\n";
        } else {
            cout << "Невозможно добавить больше блюд.\n";
        }
    }

    //метод для удаления блюда
    void deleteDish(int index) {
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

    //метод для копирования блюда
    void copyDish(int index) {
        if (index >= 0 && index < dishCount) {
            if (dishCount >= MAX_DISHES) {
                cout << "Невозможно добавить больше блюд.\n";
                return;
            }
            MenuItem* original = dishes[index];
            MenuItem* copiedDish = nullptr;

            //определяем тип блюда
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

    //метод для присваивания одного блюда другому
    void assignDish(int sourceIndex, int destIndex) {
        if (sourceIndex >= 0 && sourceIndex < dishCount &&
            destIndex >= 0 && destIndex < dishCount) 
        {
            MenuItem* source = dishes[sourceIndex];
            MenuItem* dest = dishes[destIndex];

            delete dest;

            //копируем объект нужного типа
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

    //шапка таблицы
    void printTableHeader() const {
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

    //метод для печати всех блюд
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

    //метод для печати блюд по категории
    void printDishesByCategory(const string& categoryName, bool TempOnly = false) const {
        bool found = false;
        printTableHeader();
        for (int i = 0; i < dishCount; ++i) {
            MenuItem* item = dishes[i];
            if (item->getCategory() == categoryName) {
                if (TempOnly) {
                    //проверяем, является ли напиток горячим
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

    //сравнение калорий двух блюд
    void compareCalories(int index1, int index2) {
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

    //увеличение "веса/объёма" блюда
    void incrementDishWeight(int index) {
        if (index >= 0 && index < dishCount) {
            if (Dish* dish = dynamic_cast<Dish*>(dishes[index])) {
                (*dish)++; 
                cout << "Вес блюда увеличен: ";
                dish->print(index);
            }
            //если не Dish, может быть Beverage
            else if (Beverage* bev = dynamic_cast<Beverage*>(dishes[index])) {
                // Тут логика для увеличения объёма:
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

    //уменьшение "веса/объёма" блюда
    void decrementDishWeight(int index) {
        if (index >= 0 && index < dishCount) {
            // Аналогично для Dish
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


    MenuItem* inputDish() {
        string name, category;
        int size; //здесь будет либо граммы, либо мл
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

        //если напиток — уточняем, холодный или горячий
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

        //создаём соответствующий объект
        if (category == "Напитки") {
            if (dishTypeChoice == 1) {

                temperature = "Охлажденный";

                return new TempBeverage(name, category, size, price, nutrients, temperature);
            }
            else {
                //"горячий" напиток
                temperature = "Горячий";
                return new TempBeverage(name, category, size, price, nutrients, temperature);
            }
        }
        else {
            //для остальных категорий создаём обычный Dish с весом
            return new Dish(name, category, size, price, nutrients);
        }
    }

public:
    //конструктор
    DishManager() {
        for (int i = 0; i < MAX_DISHES; ++i) {
            dishes[i] = nullptr;
        }
    }

    //деструктор для освобождения памяти
    ~DishManager() {
        for (int i = 0; i < dishCount; ++i) {
            delete dishes[i];
        }
    }

    //основной метод для запуска менеджера
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
                // Вывод только горячих напитков
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
                    //просто выводим нутриенты (дружественная функция)
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
};

int main() {
    DishManager manager;
    manager.run();
    
    return 0;
}
