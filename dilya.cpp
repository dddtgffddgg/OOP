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
    cout << "  Адрес (город): ";
    getline(cin, f.address);
    cout << "  Телефон: ";
    getline(cin, f.phone);
}

// Функция для форматированного вывода строки с фиксированной шириной
string formatColumn(const string &str, int width) 
{
    if (str.length() > width) 
        return str.substr(0, width - 1) + "."; // Обрезаем и добавляем точку
    else 
        return str + string(width - str.length(), ' '); // Заполняем пробелами
}

// Функция для печати информации о друге
void printFriend(const Friend &f) {
    cout << formatColumn(f.lastName, 12) << " | " 
         << formatColumn(f.firstName, 12) << " | " 
         << formatColumn(f.middleName, 12) << " | " 
         << setw(2) << setfill('0') << f.day << "." 
         << setw(2) << setfill('0') << f.month << "." 
         << f.year << " | " 
         << formatColumn(f.address, 20) << " | " 
         << formatColumn(f.phone, 15) << endl;
}

// Функция для печати всех друзей
void printAllFriends(const list<Friend> &friends) {
    if (friends.empty()) {
        cout << "[INFORMATION] --- Список друзей пуст.\n";
        return;
    }
    cout << left << formatColumn("Фамилия", 12) << " | " 
         << formatColumn("Имя", 12) << " | " 
         << formatColumn("Отчество", 12) << " | Дата рождения | " 
         << formatColumn("Адрес", 20) << " | " 
         << formatColumn("Телефон", 15) << endl;
    cout << string(92, '-') << endl;
    for (const auto &f : friends) {
        printFriend(f);
    }
}

// Функция для поиска и вывода друзей, родившихся в заданном месяце
void findFriendsByMonth(const list<Friend> &friends, int month) 
{
    bool found = false;
    cout << "Друзья, родившиеся в месяце " << month << ":\n";
    for (const auto &f : friends) {
        if (f.month == month) {
            printFriend(f);
            found = true;
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
    auto id = friends.begin();
    advance(id, index);
    friends.erase(id);
    cout << "[INFORMATION] --- Друг удалён.\n";
}

// Печатаем меню
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
        cin.ignore(); // Очищаем буфер
        
        switch (command) {
            case 1: {  // Добавить друга
                Friend newFriend;
                inputFriend(newFriend);
                friends.push_back(newFriend);
                cout << "[INFORMATION] --- Друг добавлен.\n";
                break;
            }
            case 2: {  // Удалить друга
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
            case 3: {  // Показать всех друзей
                printAllFriends(friends);
                break;
            }
            case 4: {  // Найти друзей по месяцу рождения
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
            case 0: // Выход из программы
                cout << "[INFORMATION] --- Программа завершена.\n";
                break;
            default:
                cout << "[ERROR] Нет такой команды! Введите корректный символ.\n";
        }
    } while (command != 0);
    return 0;
}
