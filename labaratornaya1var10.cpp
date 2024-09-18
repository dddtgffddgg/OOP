#include <iostream>
#include <string>
#include <vector>

// Используем константу вместо #define
const int MAX_COMPUTERS = 100;

class Computer {
public:
    std::string processor;
    int memory;
    int storage;
    std::string video_adapter;
    float cost;
    int purchase_year;

    void print() const {
        std::cout << "Processor: " << processor << "\n";
        std::cout << "Memory: " << memory << " GB\n";
        std::cout << "Storage: " << storage << " GB\n";
        std::cout << "Video adapter: " << video_adapter << "\n";
        std::cout << "Cost: $" << cost << "\n";
        std::cout << "Purchase year: " << purchase_year << "\n";
    }
};

std::vector<Computer> computers;

int get_computer_count() {
    return computers.size(); // Возвращаем текущее количество компьютеров
}

void add_computer(const Computer& new_computer) {
    if (get_computer_count() < MAX_COMPUTERS) {
        computers.push_back(new_computer);
    } else {
        std::cout << "Cannot add more computers. The limit is reached.\n";
    }
}

void delete_computer(int index) {
    if (index >= 0 && index < get_computer_count()) {
        computers.erase(computers.begin() + index);
    } else {
        std::cout << "Invalid index.\n";
    }
}

void print_computers() {
    for (int i = 0; i < get_computer_count(); ++i) {
        std::cout << "Computer " << i + 1 << ":\n";
        computers[i].print();
        std::cout << "\n";
    }
}

void print_outdated_computers(int current_year) {
    for (int i = 0; i < get_computer_count(); ++i) {
        if (current_year - computers[i].purchase_year > 5) {
            std::cout << "Outdated computer " << i + 1 << ":\n";
            computers[i].print();
            std::cout << "\n";
        }
    }
}

int main() {
    int choice;
    int current_year = 2023;

    while (true) {
        std::cout << "1. Add computer\n";
        std::cout << "2. Delete computer\n";
        std::cout << "3. Print all computers\n";
        std::cout << "4. Print outdated computers\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            Computer new_computer;
            std::cout << "Enter processor: ";
            std::cin >> new_computer.processor;
            std::cout << "Enter memory (in GB): ";
            std::cin >> new_computer.memory;
            std::cout << "Enter storage (in GB): ";
            std::cin >> new_computer.storage;
            std::cout << "Enter video adapter: ";
            std::cin >> new_computer.video_adapter;
            std::cout << "Enter cost: ";
            std::cin >> new_computer.cost;
            std::cout << "Enter purchase year: ";
            std::cin >> new_computer.purchase_year;
            add_computer(new_computer);
        } else if (choice == 2) {
            int index;
            std::cout << "Enter index of computer to delete: ";
            std::cin >> index;
            delete_computer(index - 1);
        } else if (choice == 3) {
            print_computers();
        } else if (choice == 4) {
            print_outdated_computers(current_year);
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice, please try again.\n";
        }
    }
    return 0;
}

