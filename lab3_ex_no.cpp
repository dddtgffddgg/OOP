#include <iostream>
#include <iomanip> 
#include <string>

using namespace std;

const int MAX_DISHES = 100;

//класс Nutrients для хранения информации о нутриентах
class Nutrients { 
private:
    float carbs;    // Углеводы (г)
    float fats;     // Жиры (г)
    float proteins; // Белки (г)

public:
    //конструктор по умолчанию с параметрами по умолчанию
    Nutrients(float carbs = 0.0, float fats = 0.0, float proteins = 0.0)
        : carbs(carbs), fats(fats), proteins(proteins) {}

    /*//конструктор копирования
    Nutrients(const Nutrients& other)
        : carbs(other.carbs), fats(other.fats), proteins(other.proteins) {}*/


    //геттеры для получения значений нутриентов
    float getCarbs() const { return carbs; }
    float getFats() const { return fats; }
    float getProteins() const { return proteins; }

    //сеттеры для установки значений нутриентов
    void setCarbs(float value) { carbs = value; }
    void setFats(float value) { fats = value; }
    void setProteins(float value) { proteins = value; }

    //метод для вычисления калорийности на основе БЖУ
    float calculateCalories() const {
        return (carbs * 4) + (fats * 9) + (proteins * 4); // калории = углеводы * 4 + жиры * 9 + белки * 4
    }

    /*//перегрузка оператора сложения
    Nutrients operator+(const Nutrients& other) const {
        return Nutrients(carbs + other.carbs,
                        fats + other.fats,
                        proteins + other.proteins);
    }*/

    /*//перегрузка оператора вычитания
    Nutrients operator-(const Nutrients& other) const {
        cout<<"operator-\n";
        return Nutrients(carbs - other.carbs,
                        fats - other.fats,
                        proteins - other.proteins);
    }*/

    //перегрузка унарного минуса
    Nutrients operator-() const {
    cout << "Перегруженный оператор - вызван\n";
    return Nutrients(-carbs, -fats, -proteins);
    }


    /*//перегрузка оператора сравнения (равенство)
    bool operator==(const Nutrients& other) const {
                cout<<"operator==\n";
        return (carbs == other.carbs) &&
               (fats == other.fats) &&
               (proteins == other.proteins);
    }*/
   
};

//класс Dish для хранения информации о блюде
class Dish { 
private:
    string name;           
    string category;      
    int weight;            
    float price;           
    Nutrients nutrients;   
    float calories;        

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

    //сеттеры для установки значений полей
    void setName(const string& newName) { name = newName; }
    void setCategory(const string& newCategory) { category = newCategory; }
    void setWeight(int weight) { this->weight = weight; }
    void setPrice(float price) { this->price = price; }
    void setNutrients(const Nutrients& nutrients) { this->nutrients = nutrients; }

    //метод для расчета калорийности блюда
    void calculateCalories() {
        calories = nutrients.calculateCalories(); // Получаем калории через класс Nutrients
    }

    //метод для вывода информации о блюде
    void print(int index) const {
        cout << "| " << left << setw(5) << index + 1
             << "| " << setw(16) << name
             << "| " << setw(20) << category
             << "| " << setw(10) << calories
             << "| " << setw(12) << (to_string(weight) + ((category == "Напитки") ? " мл" : " г"))
             << "| " << setw(10) << nutrients.getCarbs()
             << "| " << setw(10) << nutrients.getFats()
             << "| " << setw(10) << nutrients.getProteins()
             << "| " << setw(10) << fixed << setprecision(2) << price << " руб." << " |" << endl;
    }

    //делаем доступ к этому методу для класса DishManager
    friend class DishManager;
};

//класс DishManager для управления списком блюд
class DishManager { 
private:
    Dish dishes[MAX_DISHES]; //массив блюд
    int dishCount = 0;       //текущее колво блюд

    //метод для получения текущего количества блюд
    int getDishCount() const { return dishCount; }

    //метод для добавления нового блюда
    void addDish(const Dish& newDish) { 
        if (dishCount < MAX_DISHES) { 
            dishes[dishCount++] = newDish;
            cout << "Блюдо добавлено!\n\n";
        } else {
            cout << "Невозможно добавить больше блюд.\n";
        }
    }

    //метод для удаления блюда по индексу
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

    //метод для вывода заголовка таблицы блюд
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

    //метод для вывода всех блюд
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

    //метод для вывода блюд по определенной категории
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

    //метод для ввода информации о новом блюде
    Dish inputDish() {
        string name, category;
        int weight, categoryChoice;
        float price, carbs, fats, proteins;

        cout << "Введите название: ";
        cin.ignore();  
        getline(cin, name);  

        //выбор категории блюда
        cout << "Выберите категорию:\n";
        cout << "1 - Основные блюда\n";
        cout << "2 - Вторые блюда\n";
        cout << "3 - Десерты\n";
        cout << "4 - Напитки\n";
        cout << "Введите номер категории: ";

        //проверка на корректность ввода категории
        while (!(cin >> categoryChoice) || categoryChoice < 1 || categoryChoice > 4) {
            cout << "Неправильный ввод. Введите номер категории (1-4): ";
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  //очищаем буфер
        }

        //присвоение названия категории в зависимости от выбора
        switch (categoryChoice) {
            case 1: category = "Основные блюда"; break;
            case 2: category = "Вторые блюда"; break;
            case 3: category = "Десерты"; break;
            case 4: category = "Напитки"; break;
        }

        //ввод веса блюда с проверкой
        do {
            cout << "Введите вес (в граммах или мл): ";
            if (!(cin >> weight) || weight <= 0) {
                cout << "Вес должен быть положительным числом. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                weight = -1;  
            }
        } while (weight <= 0);

        //ввод углеводов с проверкой
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

        do {
            cout << "Введите прайс: ";
            if (!(cin >> price) || price < 0) {
                cout << "Цена должна быть положительным числом. Повторите ввод.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                price = -1;  
            }
        } while (price < 0);

        // Создание объекта Nutrients и Dish
        Nutrients nutrients(carbs, fats, proteins);
        Dish dish(name, category, weight, price, nutrients);

        // После создания блюда пересчитываем калории
        dish.calculateCalories();

        return dish;
    }

public:
    //метод для запуска менеджера блюд
    void run() {
        int choice;
        while (true) {
            //вывод меню
            cout << "1. Добавить блюдо\n";
            cout << "2. Удалить блюдо\n";
            cout << "3. Вывод всех блюд\n";
            cout << "4. Вывод основных блюд\n";
            cout << "5. Вывод вторых блюд\n";
            cout << "6. Вывод десертов\n";
            cout << "7. Вывод напитков\n";
            cout << "8. Тестирование класса Nutrients\n"; // Новый пункт меню
            cout << "9. Выход\n";
            cin >> choice;

            //обработка выбора пользователя
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
            } 
            else if (choice == 8) { // Тестирование класса Nutrients
            cout << "\n--- Тестирование класса Nutrients ---\n";
            Nutrients n1(100, 250, 100);
            cout << "Исходные значения Nutrients:\n";
            cout << "Углеводы: " << n1.getCarbs() << " г\n";
            cout << "Жиры: " << n1.getFats() << " г\n";
            cout << "Белки: " << n1.getProteins() << " г\n";

            // Применение перегруженного оператора -
            Nutrients n2 = -n1;

            cout << "\nПосле применения оператора -:\n";
            cout << "Углеводы: " << n2.getCarbs() << " г\n";
            cout << "Жиры: " << n2.getFats() << " г\n";
            cout << "Белки: " << n2.getProteins() << " г\n";
            cout << "---------------------------------------\n\n";
            }
            else if (choice == 8) {
                cout << "Выход из программы.\n";
                break; 
            } else {
                cout << "Неправильный ввод, пожалуйста повторите.\n";
            }
        }
    }
};

//основная функция программы
int main() {
    DishManager manager; 
    manager.run();       
    return 0;            
}
