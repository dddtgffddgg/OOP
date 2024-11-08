#include <iostream>
#include <iomanip> 
#include <string>

using namespace std;

const int MAX_DISHES = 100; //макс количество блюд

struct Nutrients { 
    float carbs; //углеводы
    float fats;  //жиры
    float proteins;// белки
};

struct Dish {
    string name;
    string category;
    int calories;
    int weight;
    float price;
    Nutrients nutrients; //добавляю структуру Nutrients
};

Dish dishes[MAX_DISHES];
int dish_count = 0; //количество блюд в данный момент

int get_dish_count() {
    return dish_count;
}

void add_dish(const Dish& new_dish) {
    if (get_dish_count() < MAX_DISHES) {
        dishes[dish_count] = new_dish;
        dish_count++;
    } else {
        cout << "Невозможно добавить больше блюд.\n";
    }
}

void delete_dish(int index) {
    if (index >= 0 && index < get_dish_count()) {
        for (int i = index; i < dish_count - 1; ++i) {
            dishes[i] = dishes[i + 1]; 
        }
        dish_count--; 
    } else {
        cout << "Неправильный ввод.\n";
    }
}

void print_table_header() { //заголовок таблицы
    cout << "| " << left << setw(7) << "№" 
         << "| " << setw(28) << "Название" 
         << "| " << setw(21) << "Категория" 
         << "| " << setw(17) << "Калории" 
         << "| " << setw(15) << "Вес" 
         << "| " << setw(11) << "Угл" 
         << "| " << setw(14) << "Жиры" 
         << "| " << setw(15) << "Белки" 
         << "| " << setw(18) << "Цена" << " |" << endl;
    cout << string(130, '-') << endl;
}

void print_dishes() { //вывод табл
    if (get_dish_count() == 0) {
        cout << "Список блюд пуст.\n";
        return;
    }

    print_table_header(); 
    for (int i = 0; i < get_dish_count(); ++i) {
        cout << "| " << left << setw(5) << i + 1
             << "| " << setw(23) << dishes[i].name
             << "| " << setw(22) << dishes[i].category
             << "| " << setw(10) << dishes[i].calories
             << "| " << setw(12) << (to_string(dishes[i].weight) + (dishes[i].category == "Напитки" ? " мл" : " г"))
             << "| " << setw(10) << dishes[i].nutrients.carbs
             << "| " << setw(10) << dishes[i].nutrients.fats
             << "| " << setw(10) << dishes[i].nutrients.proteins
             << "| " << setw(10) << fixed << setprecision(2) << dishes[i].price << " руб." << " |" << endl;
    }
    cout << string(130, '-') << endl; 
    cout << endl;
}

void print_dishes_by_category(const string& category_name) {
    bool found = false;
    print_table_header();
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == category_name) {
            found = true;
            cout << "| " << left << setw(5) << i + 1
                 << "| " << setw(20) << dishes[i].name
                 << "| " << setw(20) << dishes[i].category
                 << "| " << setw(10) << dishes[i].calories
                 << "| " << setw(12) << (to_string(dishes[i].weight) + (dishes[i].category == "Напитки" ? " мл" : " г"))
                 << "| " << setw(10) << dishes[i].nutrients.carbs
                 << "| " << setw(10) << dishes[i].nutrients.fats
                 << "| " << setw(10) << dishes[i].nutrients.proteins
                 << "| " << setw(10) << fixed << setprecision(2) << dishes[i].price << " руб." << " |" << endl;
        }
    }
    cout << string(130, '-') << endl; 
    if (!found) {
        cout << "Нет блюд в категории \"" << category_name << "\".\n";
    }
    cout << endl;
}

int main() { 
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
            Dish new_dish;
            int category_choice;

            cout << "Введите название: ";
            cin.ignore();  
            getline(cin, new_dish.name);  

            cout << "Выберите категорию:\n";
            cout << "1 - Основные блюда\n";
            cout << "2 - Вторые блюда\n";
            cout << "3 - Десерты\n";
            cout << "4 - Напитки\n";
            cout << "Введите номер категории: ";
            cin >> category_choice;

            cin.ignore(); 

            switch (category_choice) {
                case 1:
                    new_dish.category = "Основные блюда";
                    break;
                case 2:
                    new_dish.category = "Вторые блюда";
                    break;
                case 3:
                    new_dish.category = "Десерты";
                    break;
                case 4:
                    new_dish.category = "Напитки";
                    break;
                default:
                    cout << "Неправильный выбор категории.\n";
                    continue;
            }

            cout << "Введите калории (в ккал): ";
            cin >> new_dish.calories;

            if (new_dish.category == "Напитки") {
                cout << "Введите объем (в мл): ";  
            } else {
                cout << "Введите объем (в граммах): ";       
            }
            cin >> new_dish.weight;

            cout << "Введите углеводы (г): ";
            cin >> new_dish.nutrients.carbs;
            
            cout << "Введите жиры (г): ";
            cin >> new_dish.nutrients.fats;
            
            cout << "Введите белки (г): ";
            cin >> new_dish.nutrients.proteins;

            cout << "Введите прайс: ";
            cin >> new_dish.price;

            add_dish(new_dish);
            cout << "Блюдо добавлено!\n\n";

        } else if (choice == 2) {
            int index;
            cout << "Для удаления введите номер блюда: ";
            cin >> index;
            delete_dish(index - 1);
        } else if (choice == 3) {
            print_dishes();
        } else if (choice == 4) {
            print_dishes_by_category("Основные блюда");
        } else if (choice == 5) {
            print_dishes_by_category("Вторые блюда");
        } else if (choice == 6) {
            print_dishes_by_category("Десерты");
        } else if (choice == 7) {
            print_dishes_by_category("Напитки");
        } else if (choice == 8) {
            break;
        } else {
            cout << "Неправильный ввод, пожалуйста повторите.\n";
        }
    }

    return 0;
}
