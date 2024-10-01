#include <iostream>
#include <string>

using namespace std;

const int MAX_DISHES = 100; // макс количество блюд

class Dish {
public:
    string name;
    string category;
    int calories;
    int weight;
    float price;

    void print() const {
        cout << "Name: " << name << "\n";
        cout << "Category: " << category << "\n";
        cout << "Calories: " << calories << " kcal\n";
        cout << "Weight: " << weight << (category == "Drinks" ? " ml" : " grams") << "\n";
        cout << "Price: $" << price << "\n";
    }
};

Dish dishes[MAX_DISHES];
int dish_count = 0; // количество блюд в данный момент

int get_dish_count() {
    return dish_count;
}

void add_dish(const Dish& new_dish) {
    if (get_dish_count() < MAX_DISHES) {
        dishes[dish_count] = new_dish;
        dish_count++;
    } else {
        cout << "Unable to add more dishes.\n";
    }
}

void delete_dish(int index) {
    if (index >= 0 && index < get_dish_count()) {
        for (int i = index; i < dish_count - 1; ++i) {
            dishes[i] = dishes[i + 1]; // сдвигаем элементы
        }
        dish_count--; // уменьшаем количество блюд
    } else {
        cout << "Invalid index.\n";
    }
}

// вывод всех блюд
void print_dishes() {
    for (int i = 0; i < get_dish_count(); ++i) {
        cout << "Dish " << i + 1 << ":\n";
        dishes[i].print();
        cout << "\n";
    }
}

// вывод только первых блюд
void print_first_courses() {
    cout << "First Courses:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "First Courses") {
            cout << "Dish " << i + 1 << ":\n";
            dishes[i].print();
            cout << "\n";
        }
    }
}

// вывод вторых блюд
void print_second_courses() {
    cout << "Second Courses:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Second Courses") {
            cout << "Dish " << i + 1 << ":\n";
            dishes[i].print();
            cout << "\n";
        }
    }
}

// вывод десертов
void print_dishes_courses() {
    cout << "Desserts:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Desserts") {
            cout << "Dish " << i + 1 << ":\n";
            dishes[i].print();
            cout << "\n";
        }
    }
}

// вывод напитков
void print_drinks() {
    cout << "Drinks:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Drinks") {
            cout << "Dish " << i + 1 << ":\n";
            dishes[i].print();
            cout << "\n";
        }
    }
}

int main() {

    int choice;

    while (true) {
        cout << "1. Add a dish\n";
        cout << "2. Delete a dish\n";
        cout << "3. Print all dishes\n";
        cout << "4. Print first courses\n";
        cout << "5. Print second courses\n";
        cout << "6. Print desserts\n";
        cout << "7. Print drinks\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Dish new_dish;
            int category_choice;

            cout << "Enter the name: ";
            cin.ignore();  // очищаем 1 символ (остатки после предыдущего ввода)
            getline(cin, new_dish.name);  // корректно считываем название блюда

            cout << "Select a category:\n";
            cout << "1 - First Courses\n";
            cout << "2 - Second Courses\n";
            cout << "3 - Desserts\n";
            cout << "4 - Drinks\n";
            cout << "Enter the category number: ";
            cin >> category_choice;

            cin.ignore(); 

            switch (category_choice) {
                case 1:
                    new_dish.category = "First Courses";
                    break;
                case 2:
                    new_dish.category = "Second Courses";
                    break;
                case 3:
                    new_dish.category = "Desserts";
                    break;
                case 4:
                    new_dish.category = "Drinks";
                    break;
                default:
                    cout << "Invalid category selection.\n";
                    continue;
            }

            cout << "Enter the calories (in kcal): ";
            cin >> new_dish.calories;

            if (new_dish.category == "Drinks") {
                cout << "Enter the volume (in milliliters): ";  
            } else {
                cout << "Enter the weight (in grams): ";       
            }
            cin >> new_dish.weight;

            cout << "Enter the price: ";
            cin >> new_dish.price;

            add_dish(new_dish);
            cout << "Dish added!\n\n";

        } else if (choice == 2) {
            int index;
            cout << "Enter the index of the dish to delete: ";
            cin >> index;
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
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
