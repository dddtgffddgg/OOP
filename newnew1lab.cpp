#include <iostream>
#include <string>

using namespace std;

const int MAX_DISHES = 100; // максимальное количество блюд

struct Dish {
    string name;
    string category;
    int calories;
    int weight;
    float price;
};

Dish dishes[MAX_DISHES];
int dish_count = 0; // количество блюд в данный момент

//функции для работы с блюдами
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
            dishes[i] = dishes[i + 1]; // сдвигаем элементы
        }
        dish_count--; // уменьшаем количество блюд
    } else {
        cout << "Неправильный ввод.\n";
    }
}

void print_dishes() {
    for (int i = 0; i < get_dish_count(); ++i) {
        cout << "Блюдо " << i + 1 << ":\n";
        cout << "Название: " << dishes[i].name << "\n";
        cout << "Категория: " << dishes[i].category << "\n";
        cout << "Калории: " << dishes[i].calories << " ккал\n";
        cout << "Граммовка: " << dishes[i].weight << (dishes[i].category == "Напитки" ? " мл" : " грамм") << "\n";
        cout << "Прайс: " << dishes[i].price << " руб. \n\n";
    }
}

void print_first_courses() {
    cout << "Основные блюда:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Основные блюда") {
            cout << "Блюдо " << i + 1 << ":\n";
            cout << "Название: " << dishes[i].name << "\n";
            cout << "Калории: " << dishes[i].calories << " ккал\n";
            cout << "Граммовка: " << dishes[i].weight << " грамм\n";
            cout << "Прайс: " << dishes[i].price << " руб. \n\n";
        }
    }
}

void print_second_courses() {
    cout << "Вторые блюда:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Вторые блюда") {
            cout << "Блюдо " << i + 1 << ":\n";
            cout << "Нзвание: " << dishes[i].name << "\n";
            cout << "Калории: " << dishes[i].calories << " ккал\n";
            cout << "Граммы: " << dishes[i].weight << " грамм\n";
            cout << "Прайс: " << dishes[i].price << " руб. \n\n";
        }
    }
}

void print_desserts() {
    cout << "Десерты:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Десерты") {
            cout << "Блюдо " << i + 1 << ":\n";
            cout << "Название: " << dishes[i].name << "\n";
            cout << "Калории: " << dishes[i].calories << " ккал\n";
            cout << "Граммовки: " << dishes[i].weight << " грамм\n";
            cout << "Прайс: " << dishes[i].price << " руб. \n\n";
        }
    }
}

void print_drinks() {
    cout << "Напитки:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Напитки") {
            cout << "Блюдо " << i + 1 << ":\n";
            cout << "Название: " << dishes[i].name << "\n";
            cout << "Калории: " << dishes[i].calories << " ккал\n";
            cout << "Объем: " << dishes[i].weight << " мл\n";
            cout << "Прайс: " << dishes[i].price << " руб. \n\n";
        }
    }
}

int main() {
    int choice;

    while (true) {
        cout << "1. Добавить блюдо\n";
        cout << "2. Удалить блюдо\n";
        cout << "3. Вывод всех блюд\n";
        cout << "4. Вывод основных блюд\n";
        cout << "5. Вывод вторых блюд\n";
        cout << "6. Вывод дессертов\n";
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
            cout << "3 - Дессерты\n";
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
                    new_dish.category = "Дессерты";
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
            print_first_courses();
        } else if (choice == 5) {
            print_second_courses();
        } else if (choice == 6) {
            print_desserts();
        } else if (choice == 7) {
            print_drinks();
        } else if (choice == 8) {
            break;
        } else {
            cout << "Неправильный ввод, пожалуйста повторите.\n";
        }
    }

    return 0;
}
