#include <iostream>
#include <string>

using namespace std;

const int MAX_DISHES = 100; // максимальное количество блюд

// Определение структуры для блюда
struct Dish {
    string name;
    string category;
    int calories;
    int weight;
    float price;
};

// Массив для хранения блюд и счетчик блюд
Dish dishes[MAX_DISHES];
int dish_count = 0; // количество блюд в данный момент

// Функции для работы с блюдами
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

void print_dishes() {
    for (int i = 0; i < get_dish_count(); ++i) {
        cout << "Dish " << i + 1 << ":\n";
        cout << "Name: " << dishes[i].name << "\n";
        cout << "Category: " << dishes[i].category << "\n";
        cout << "Calories: " << dishes[i].calories << " kcal\n";
        cout << "Weight: " << dishes[i].weight << (dishes[i].category == "Drinks" ? " ml" : " grams") << "\n";
        cout << "Price: $" << dishes[i].price << "\n\n";
    }
}

void print_first_courses() {
    cout << "First Courses:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "First Courses") {
            cout << "Dish " << i + 1 << ":\n";
            cout << "Name: " << dishes[i].name << "\n";
            cout << "Calories: " << dishes[i].calories << " kcal\n";
            cout << "Weight: " << dishes[i].weight << " grams\n";
            cout << "Price: $" << dishes[i].price << "\n\n";
        }
    }
}

void print_second_courses() {
    cout << "Second Courses:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Second Courses") {
            cout << "Dish " << i + 1 << ":\n";
            cout << "Name: " << dishes[i].name << "\n";
            cout << "Calories: " << dishes[i].calories << " kcal\n";
            cout << "Weight: " << dishes[i].weight << " grams\n";
            cout << "Price: $" << dishes[i].price << "\n\n";
        }
    }
}

void print_desserts() {
    cout << "Desserts:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Desserts") {
            cout << "Dish " << i + 1 << ":\n";
            cout << "Name: " << dishes[i].name << "\n";
            cout << "Calories: " << dishes[i].calories << " kcal\n";
            cout << "Weight: " << dishes[i].weight << " grams\n";
            cout << "Price: $" << dishes[i].price << "\n\n";
        }
    }
}

void print_drinks() {
    cout << "Drinks:\n";
    for (int i = 0; i < get_dish_count(); ++i) {
        if (dishes[i].category == "Drinks") {
            cout << "Dish " << i + 1 << ":\n";
            cout << "Name: " << dishes[i].name << "\n";
            cout << "Calories: " << dishes[i].calories << " kcal\n";
            cout << "Volume: " << dishes[i].weight << " ml\n";
            cout << "Price: $" << dishes[i].price << "\n\n";
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
            cin.ignore();  
            getline(cin, new_dish.name);  

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
            print_desserts();
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
