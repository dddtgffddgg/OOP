#include <iostream>
#include <list>
#include <string>
#include <iomanip>

using namespace std;

// Структура для хранения данных о друге
struct Friend 
{
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
void inputFriend(Friend &f) 
{
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
    cin.ignore();  // Очищаем буфер
    cout << "  Адрес: ";
    getline(cin, f.address);
    cout << "  Телефон: ";
    getline(cin, f.phone);
}

// Функция для печати одного друга
void printFriend(const Friend &f, int widths[]) {
    cout << "| " << setw(widths[0]) << f.lastName 
         << " | " << setw(widths[1]) << f.firstName 
         << " | " << setw(widths[2]) << f.middleName 
         << " | " << setw(widths[3]) << f.day << "." << setw(2) << f.month << "." << f.year 
         << " | " << setw(widths[4]) << f.address 
         << " | " << setw(widths[5]) << f.phone << " |\n";
}

// Функция для нахождения максимальной ширины каждой колонки
void findMaxWidths(const list<Friend> &friends, int widths[]) {
    widths[0] = 8; // "Фамилия"
    widths[1] = 4; // "Имя"
    widths[2] = 8; // "Отчество"
    widths[3] = 13; // "Дата рождения"
    widths[4] = 6; // "Адрес"
    widths[5] = 7; // "Телефон"
    
    for (const auto &f : friends) {
        if (f.lastName.length() > widths[0]) widths[0] = f.lastName.length();
        if (f.firstName.length() > widths[1]) widths[1] = f.firstName.length();
        if (f.middleName.length() > widths[2]) widths[2] = f.middleName.length();
        string dateOfBirth = to_string(f.day) + "." + to_string(f.month) + "." + to_string(f.year);
        if (dateOfBirth.length() > widths[3]) widths[3] = dateOfBirth.length();
        if (f.address.length() > widths[4]) widths[4] = f.address.length();
        if (f.phone.length() > widths[5]) widths[5] = f.phone.length();
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
    cout << "| " << setw(widths[0]) << "Фамилия" 
         << " | " << setw(widths[1]) << "Имя" 
         << " | " << setw(widths[2]) << "Отчество" 
         << " | " << setw(widths[3]) << "Дата рождения" 
         << " | " << setw(widths[4]) << "Адрес" 
         << " | " << setw(widths[5]) << "Телефон" << " |\n";
    cout << string(2 + widths[0] + 3 + widths[1] + 3 + widths[2] + 3 + widths[3] + 3 + widths[4] + 3 + widths[5] + 2, '-') << "\n";

    for (const auto &f : friends) {
        printFriend(f, widths);
    }
}

// Функция для поиска и вывода друзей, родившихся в заданном месяце
void findFriendsByMonth(const list<Friend> &friends, int month) 
{
    bool found = false;
    cout << "Друзья, родившиеся в месяце " << month << ":\n";
    for (const auto &f : friends) {
        if (f.month == month) {
            found = true;
            int widths[6];
            findMaxWidths(friends, widths);
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
