#include <iostream>
#include <list>
#include <string>
#include <iomanip>

using namespace std;

// Структура для хранения данных о друге
struct Friend {
    string lastName;     
    string firstName;    
    string middleName;   
    int day;             
    int month;           
    int year;            
    string address;      
    string phone;       
};

// Функция для ввода данных о друге
void inputFriend(Friend &f) {
    cout << "Введите данные о друге:\n";
    cout << "  Фамилия: ";
    getline(cin, f.lastName);
    cout << "  Имя: ";
    getline(cin, f.firstName);
    cout << "  Отчество: ";
    getline(cin, f.middleName);
    cout << "  День рождения (число): ";
    cin >> f.day;
    cout << "  Месяц рождения (число): ";
    cin >> f.month;
    cout << "  Год рождения: ";
    cin >> f.year;
    cin.ignore();
    cout << "  Адрес: ";
    getline(cin, f.address);
    cout << "  Телефон: ";
    getline(cin, f.phone);
}

// Функция для печати одного друга
void printFriend(const Friend &f, int widths[]) {
    cout << "| " << left << setw(widths[0]) << f.lastName 
         << " | " << left << setw(widths[1]) << f.firstName 
         << " | " << left << setw(widths[2]) << f.middleName 
         << " | " << right << setw(2) << setfill('0') << f.day << "." 
         << setw(2) << setfill('0') << f.month << "." << setw(4) << setfill(' ') << f.year
         << " | " << left << setw(widths[4]) << f.address 
         << " | " << left << setw(widths[5]) << f.phone << " |\n";
}

// Функция для нахождения максимальной ширины каждой колонки
void findMaxWidths(const list<Friend> &friends, int widths[]) {
    widths[0] = max(8, (int)string("Фамилия").length());
    widths[1] = max(4, (int)string("Имя").length());
    widths[2] = max(8, (int)string("Отчество").length());
    widths[3] = string("Дата рождения").length();
    widths[4] = max(6, (int)string("Адрес").length());
    widths[5] = max(7, (int)string("Телефон").length());
    
    for (const auto &f : friends) {
        widths[0] = max(widths[0], (int)f.lastName.length());
        widths[1] = max(widths[1], (int)f.firstName.length());
        widths[2] = max(widths[2], (int)f.middleName.length());
        widths[4] = max(widths[4], (int)f.address.length());
        widths[5] = max(widths[5], (int)f.phone.length());
    }
}

// Функция для печати всех друзей
void printAllFriends(const list<Friend> &friends) {
    if (friends.empty()) {
        cout << "[INFORMATION] --- Список друзей пуст.\n";
        return;
    }

    int widths[6];
    findMaxWidths(friends, widths);

    // Печатаем заголовок
    cout << "| " << left << setw(widths[0]) << "Фамилия" 
         << " | " << left << setw(widths[1]) << "Имя" 
         << " | " << left << setw(widths[2]) << "Отчество" 
         << " | " << left << setw(widths[3]) << "Дата рождения" 
         << " | " << left << setw(widths[4]) << "Адрес" 
         << " | " << left << setw(widths[5]) << "Телефон" << " |\n";
    cout << string(3 + widths[0] + widths[1] + widths[2] + widths[3] + widths[4] + widths[5] + 13, '-') << "\n";

    for (const auto &f : friends) {
        printFriend(f, widths);
    }
}

// Функция для поиска и вывода друзей, родившихся в заданном месяце
void findFriendsByMonth(const list<Friend> &friends, int month) {
    bool found = false;
    int widths[6];
    findMaxWidths(friends, widths);
    cout << "Друзья, родившиеся в месяце " << month << ":\n";
    for (const auto &f : friends) {
        if (f.month == month) {
            found = true;
            printFriend(f, widths);
        }
    }
    if (!found) {
        cout << "[INFORMATION] --- Нет друзей, которые родились в этом месяце.\n";
    }
}

// Функция для удаления друга по индексу
void removeFriend(list<Friend> &friends, int index) {
    if (index < 0 || index >= friends.size()) {
        cout << "[ERROR] Неверный индекс.\n";
        return;
    }
    auto it = friends.begin();
    advance(it, index);
    friends.erase(it);
    cout << "[INFORMATION] --- Друг удалён.\n";
}

// Печатаем менюшку
void printMenu() {
    cout << "[1] Добавить друга\n";
    cout << "[2] Удалить друга\n";
    cout << "[3] Показать всех друзей\n";
    cout << "[4] Найти друзей по месяцу рождения\n";
    cout << "[0] Выйти\n";
    cout << " Введите-> ";
}

int main() {
    list<Friend> friends;
    int command;
    
    do {
        printMenu();
        cin >> command;
        cin.ignore();
        
        switch (command) {
            case 1: {  
                Friend newFriend;
                inputFriend(newFriend);
                friends.push_back(newFriend);
                cout << "[INFORMATION] --- Друг добавлен.\n";
                break;
            }
            case 2: {  
                if (friends.empty()) {
                    cout << "[INFORMATION] --- Список друзей пуст.\n";
                } else {
                    int index;
                    cout << "Введите номер друга для удаления (1 - " << friends.size() << "): ";
                    cin >> index;
                    removeFriend(friends, index - 1);
                }
                break;
            }
            case 3: {  
                printAllFriends(friends);
                break;
            }
            case 4: {  
                if (friends.empty()) {
                    cout << "[INFORMATION] --- Список друзей пуст.\n";
                } else {
                    int month;
                    cout << "Введите месяц (1-12): ";
                    cin >> month;
                    findFriendsByMonth(friends, month);
                }
                break;
            }
            case 0: 
                cout << "[INFORMATION] --- Программа завершена.\n";
                break;
            default:
                cout << "[ERROR] Нет такой команды! Введите корректную команду.\n";
        }
    } while (command != 0);
    return 0;
}
