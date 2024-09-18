//Variant_4_Caffe
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const int max_dishes = 50

class Caffe { //struct here probably
public:
    std::name_dish;
    int calori;
    int gramm;
    std::string category;
    float cost;

    void print() const {

        std::cout << "Name dish: " << name_dish << "\n";
        std::cout << "Calori: " << calori << "\n";
        std::cout << "Gramm: " << gramm << "\n";
        std::cout << "Category: " << category << "\n";
        std::cout << "Cost: $" << cost << "\n";
    }

};

std::vector<Caffe> dishes;

int get_dishes_count() {
    return dishes.size();
}

void add_dish(const Caffe & new_dish) {
    if (get_dishes_count() < max_dishes) {
        dishes.push_back
        
    }
}

// void print_outdated_computers(int current_year) {
//     for (int i = 0; i < computer_count; i++) {
//         if (current_year - computers[i].purchase_year > 5) {
//             printf("Outdated computer %d:\n", i+1);
//             print_computer(computers[i]);
//             printf("\n");
//         }
//     }
// }

// int main() {
//     int choice;
//     int current_year = 2023;
//     while (1) {
//         printf("1. Add computer\n");
//         printf("2. Delete computer\n");
//         printf("3. Print all computers\n");
//         printf("4. Print outdated computers\n");
//         printf("5. Exit\n");
//         printf("Enter your choice: ");
//         scanf("%d", &choice);
//         if (choice == 1) {
//             struct Computer new_computer;
//             printf("Enter processor: ");
//             scanf("%s", new_computer.processor);
//             printf("Enter memory (in GB): ");
//             scanf("%d", &new_computer.memory);
//             printf("Enter storage (in GB): ");
//             scanf("%d", &new_computer.storage);
//             printf("Enter video adapter: ");
//             scanf("%s", new_computer.video_adapter);
//             printf("Enter cost: ");
//             scanf("%f", &new_computer.cost);
//             printf("Enter purchase year: ");
//             scanf("%d", &new_computer.purchase_year);
//             add_computer(new_computer);
//         } else if (choice == 2) {
//             int index;
//             printf("Enter index of computer to delete: ");
//             scanf("%d", &index);
//             delete_computer(index - 1);
//         } else if (choice == 3) {
//             print_computers();
//         } else if (choice == 4) {
//             print_outdated_computers(current_year);
//         } else if (choice == 5) {
//             break;
//         }
//     }
// return 0;
// }
