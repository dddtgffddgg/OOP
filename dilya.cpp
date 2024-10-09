#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_FRIENDS = 100; // Максимальное количество друзей

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

Friend friends[MAX_FRIENDS];
int friend_count = 0; // Текущее количество друзей

int get_friend_count() {
    return friend_count;
}

// Функция для добавления друга
void add_friend(const Friend& new_friend) {
    if (get_friend_count() < MAX_FRIENDS) {
        friends[friend_count] = new_friend;
        friend_count++;
    } else {
        cout << "Невозможно добавить больше друзей.\n";
    }
}

// Функция для удаления друга
void delete_friend(int index) {
    if (index >= 0 && index < get_friend_count()) {
        for (int i = index; i < friend_count - 1; ++i) {
            friends[i] = friends[i + 1];
        }
        friend_count--;
    } else {
        cout << "Неправильный ввод.\n";
    }
}

// Заголовок таблицы
void print_table_header() {
    cout << "| " << left << setw(5) << "№"
         << "| " << setw(15) << "Фамилия"
         << "| " << setw(10) << "Имя"
         << "| " << setw(15) << "Отчество"
         << "| " << setw(12) << "День рождения"
         << "| " << setw(20) << "Адрес"
         << "| " << setw(15) << "Телефон" << " |" << endl;
    cout << string(100, '-') << endl;
}

// Функция для вывода всех друзей
void print_friends() {
    if (get_friend_count() == 0) {
        cout << "Список друзей пуст.\n";
        return;
    }

    print_table_header();
    for (int i = 0; i < get_friend_count(); ++i) {
        cout << "| " << left << setw(5) << i + 1
             << "| " << setw(15) << friends[i].lastName
             << "| " << setw(10) << friends[i].firstName
             << "| " << setw(15) << friends[i].middleName
             << "| " << friends[i].day << "."
             << friends[i].month << "." << friends[i].year
             << "| " << setw(20) << friends[i].address
             << "| " << setw(15) << friends[i].phone << " |" << endl;
    }
    cout << string(100, '-') << endl;
}

// Функция для вывода друзей по месяцу рождения
void print_friends_by_month(int month) {
    bool found = false;
    print_table_header();
    for (int i = 0; i < get_friend_count(); ++i) {
        if (friends[i].month == month) {
            found = true;
            cout << "| " << left << setw(5) << i + 1
                 << "| " << setw(15) << friends[i].lastName
                 << "| " << setw(10) << friends[i].firstName
                 << "| " << setw(15) << friends[i].middleName
                 << "| " << friends[i].day << "."
                 << friends[i].month << "." << friends[i].year
                 << "| " << setw(20) << friends[i].address
                 << "| " << setw(15) << friends[i].phone << " |" << endl;
        }
    }
    cout << string(100, '-') << endl;
    if (!found) {
        cout << "Нет друзей, родившихся в этом месяце.\n";
    }
}

// Главное меню
int main() {
    int choice;

    while (true) {
        cout << "1. Добавить друга\n";
        cout << "2. Удалить друга\n";
        cout << "3. Показать всех друзей\n";
        cout << "4. Показать друзей по месяцу рождения\n";
        cout << "5. Выход\n";
        cout << "Введите свой выбор: ";
        cin >> choice;

        if (choice == 1) {
            Friend new_friend;
            
            cout << "Введите фамилию: ";
            cin.ignore(); 
            getline(cin, new_friend.lastName);

            cout << "Введите имя: ";
            getline(cin, new_friend.firstName);

            cout << "Введите отчество: ";
            getline(cin, new_friend.middleName);

            cout << "Введите день рождения: ";
            cin >> new_friend.day;

            cout << "Введите месяц рождения: ";
            cin >> new_friend.month;

            cout << "Введите год рождения: ";
            cin >> new_friend.year;
            cin.ignore();  

            cout << "Введите адрес: ";
            getline(cin, new_friend.address);

            cout << "Введите телефон: ";
            getline(cin, new_friend.phone);

            add_friend(new_friend);
            cout << "Друг добавлен!\n\n";

        } else if (choice == 2) {
            int index;
            cout << "Введите номер друга для удаления: ";
            cin >> index;
            delete_friend(index - 1);

        } else if (choice == 3) {
            print_friends();

        } else if (choice == 4) {
            int month;
            cout << "Введите месяц (1-12): ";
            cin >> month;
            print_friends_by_month(month);

        } else if (choice == 5) {
            break;

        } else {
            cout << "Неправильный ввод, пожалуйста повторите.\n";
        }
    }

    return 0;
}
