#include <iostream>
#include <string>
#include <vector>

const int MAX_DISHES = 100; // макс количество блюд

// Описание блюда
class Dish {
public:
    std::string name;
    std::string category;
    int calories;
    int weight;
    float price;

    void print() const {
        std::cout << "Название: " << name << "\n";
        std::cout << "Категория: " << category << "\n";
        std::cout << "Калории: " << calories << " ккал\n";
        std::cout << "Вес: " << weight << (category == "Напитки" ? " мл" : " граммов") << "\n";
        std::cout << "Цена: руб." << price << "\n";
    }

};

std::vector<Dish> dishes;

int get_dish_count() {
    return dishes.size();
}

void add_dish(const Dish& new_dish) {
    if (get_dish_count() < MAX_DISHES) {
        dishes.push_back(new_dish);
    } else {
        std::cout << "Невозможно добавить больше блюд.\n";
    }
}


void delete_dish(int index) {
    if (index >= 0 && index < get_dish_count()) {
        dishes.erase(dishes.begin() + index);
    } else {
        std::cout << "Неправильный индекс.\n";
    }
}

//вывод всех блюд
void print_dishes() {
    for (int i = 0; i < get_dish_count(); ++i) {
        std::cout << "Блюдо " << i + 1 << ":\n";
        dishes[i].print();
        std::cout << "\n";
    }
}

//вывод только первых блюд
void print_first_courses() {
    std::cout << "Основные блюда:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Основные блюда") {
            std::cout << "Блюдо " << i + 1 << ":\n";
            dishes[i].print();
            std::cout << "\n";
        }
    }
}

void print_second_courses() {
    std::cout << "Вторые блюда:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Вторые блюда") {
            std::cout << "Блюдо " << i + 1 << ":\n";
            dishes[i].print();
            std::cout << "\n";
        }
    }
}

void print_dishes_courses() {
    std::cout << "Десерты:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Десерты") {
            std::cout << "Блюдо " << i + 1 << ":\n";
            dishes[i].print();
            std::cout << "\n";
        }
    }
}

void print_drinks() {
    std::cout << "Напитки:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Напитки") {
            std::cout << "Блюдо " << i + 1 << ":\n";
            dishes[i].print();
            std::cout << "\n";
        }
    }
}

int main() {
    int choice;

    while (true) {
        std::cout << "1. Добавить блюдо\n";
        std::cout << "2. Удалить блюдо\n";
        std::cout << "3. Вывод всех блюд\n";
        std::cout << "4. Вывод первых блюд\n";
        std::cout << "5. Вывод вторых блюд\n";
        std::cout << "6. Вывод десертов\n";
        std::cout << "7. Вывод напитков\n";
        std::cout << "8. Выход\n";
        std::cout << "Введите цифру: \n";
        std::cin >> choice;

        if (choice == 1) {
            Dish new_dish;
            int category_choice;

            std::cout << "Введите название: ";
            std::cin.ignore(); 
            std::getline(std::cin, new_dish.name);


            std::cout << "Выберите категорию:\n";
            std::cout << "1 - Основные блюда\n";
            std::cout << "2 - Вторые блюда\n";
            std::cout << "3 - Десерты\n";
            std::cout << "4 - Напитки\n";
            std::cout << "Введите номер категории: ";
            std::cin >> category_choice;

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
                    std::cout << "Неверный выбор категории.\n";
                    continue; 
            }

            //ввод калорийности
            std::cout << "Введите калории (в ккал): ";
            std::cin >> new_dish.calories;

            if (new_dish.category == "Напитки") {
                std::cout << "Введите объем (в миллилитрах): ";  
            } else {
                std::cout << "Введите вес (в граммах): ";       
            }
            std::cin >> new_dish.weight;

            std::cout << "Введите цену: ";
            std::cin >> new_dish.price;

            //добавляем новое блюдо в список
            add_dish(new_dish);
            std::cout << "Блюдо добавлено!\n\n";
        } else if (choice == 2) {
            int index;
            std::cout << "Введите индекс блюда, которое нужно удалить: ";
            std::cin >> index;
            delete_dish(index - 1);
        } else if (choice == 3) {
            print_dishes();
        } else if (choice == 4) {
            print_first_courses();
        } else if (choice == 5) {
            print_second_courses();
        } else if (choice == 6) {
            print_dishes_courses();
        } else if (choice == 7) {
            print_drinks();
        } else if (choice == 8) {
            break;
        } else {
            std::cout << "Неверный выбор, попробуйте еще раз.\n";
        }
    }

    return 0;
}
