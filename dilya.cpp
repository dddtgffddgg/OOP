#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

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

// Ограничения по ширине для столбцов
const int COLUMN_WIDTH = 15;

// Функция для разбивки строки на подстроки длиной не более COLUMN_WIDTH
vector<string> splitString(const string& str, int width) {
    vector<string> lines;
    int start = 0;
    while (start < str.length()) {
        int length = min(width, static_cast<int>(str.length()) - start);
        lines.push_back(str.substr(start, length));
        start += length;
    }
    return lines;
}

// Функция для печати строки таблицы с данными
void printTableRow(const vector<vector<string>>& columns) {
    size_t maxLines = 0;

    // Определяем максимальное количество строк среди всех столбцов
    for (const auto& col : columns) {
        maxLines = max(maxLines, col.size());
    }

    // Печатаем построчно каждую часть данных
    for (size_t line = 0; line < maxLines; ++line) {
        cout << "|";
        for (const auto& col : columns) {
            if (line < col.size()) {
                cout << " " << setw(COLUMN_WIDTH) << left << col[line] << " |";
            } else {
                cout << " " << setw(COLUMN_WIDTH) << " " << " |";
            }
        }
        cout << "\n";
    }
}

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

// Функция для печати информации о друге
void printFriend(const Friend &f) {
    vector<string> lastNameLines = splitString(f.lastName, COLUMN_WIDTH);
    vector<string> firstNameLines = splitString(f.firstName, COLUMN_WIDTH);
    vector<string> middleNameLines = splitString(f.middleName, COLUMN_WIDTH);
    vector<string> addressLines = splitString(f.address, COLUMN_WIDTH);
    vector<string> phoneLines = splitString(f.phone, COLUMN_WIDTH);
    
    // Формируем строку с датой рождения
    string dateOfBirth = to_string(f.day) + "." + to_string(f.month) + "." + to_string(f.year);
    vector<string> dateLines = splitString(dateOfBirth, COLUMN_WIDTH);
    
    // Собираем все столбцы в одну строку
    vector<vector<string>> columns = {
        lastNameLines, firstNameLines, middleNameLines, dateLines, addressLines, phoneLines
    };

    // Печатаем строки таблицы
    printTableRow(columns);
}

// Функция для печати всех друзей
void printAllFriends(const list<Friend> &friends) {
    if (friends.empty()) {
        cout << "[INFORMATION] --- Список друзей пуст.\n";
        return;
    }

    cout << "| " << setw(COLUMN_WIDTH) << "Фамилия" << " | " 
         << setw(COLUMN_WIDTH) << "Имя" << " | " 
         << setw(COLUMN_WIDTH) << "Отчество" << " | "
         << setw(COLUMN_WIDTH) << "Дата рождения" << " | "
         << setw(COLUMN_WIDTH) << "Адрес" << " | "
         << setw(COLUMN_WIDTH) << "Телефон" << " |\n";
    cout << string((COLUMN_WIDTH + 3) * 6, '-') << "\n";

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
    cout << "[INFORMATION] --- Друг удалён:(\n";
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
                cout << "[INFORMATION] --- Друг добавлен:)\n";
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
