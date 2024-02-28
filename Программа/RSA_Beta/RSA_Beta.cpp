#include <iostream> 
#include <string> 
#include <windows.h> 
#include <stdlib.h> 
using namespace std;
struct User {
    char Name[100];
    int OpenKey[2];
    int SecretKey[2];
};

int encryption(int e, int n, int m) {
    long long int c;
    c = pow(m, e);
    c %= n;
    return c;
}
int decryption(int d, int n, int c) {
    long long int m;
    m = pow(c, d);
    m %= n;
    return m;
}
int nod(int a, int b) {
    if (b == 0) {
        return a;
    }
    else {
        return nod(b, a % b);
    }
}
bool mutuallySimply(int a, int b) {
    return nod(a, b) == 1;
}

void Key_generation(int& n, int& e, int& d) {
    int of = rand();
    int p = 3;
    int q = 11;
    n = p * q;
    int Eiler = (p - 1) * (q - 1);
    cout << "Значение функции Эйлера от n = " << n << " : " << Eiler << endl << endl;
    int i = rand() % 450 + 100;
    for (int k = 6; k < Eiler; k++) {
        if (mutuallySimply(Eiler, k)) {
            e = k;
            break;
        }
    }
    for (int i = 2; i < 1000000000000; i++) {
        if (((i * e) - 1) % Eiler == 0) {
            d = i;
            break;
        }
    }
}

struct Users {
    User b;
    Users* next;
    Users* prev;
};

Users* head = NULL, * tail = NULL;

void Find_user(char name[], int& n, int& e, int& d) {
    int check = 0;
    Users* a = new Users;
    a = head;
    while (a) {
        if (!strcmp(a->b.Name, name)) {
            n = a->b.OpenKey[1];
            e = a->b.OpenKey[0];
            d = a->b.SecretKey[0];
            check = 1;
        }
        a = a->next;
    }
    if (check == 1) {
        cout << "Пользователь найден: " << endl << endl << "Имя\t" << "Открытый ключ\t" << "Закрытый ключ" << endl << endl
            << name << "\t" << "{" << e << "," << n << "}\t        " << "{" << d << "," << n << "}" << endl << endl;
    }
    else {
        cout << "Указанный пользователь не найден" << endl;
        exit(0);
    }
}

string Word_encryption(string message, int e, int n) {
    string Coded_Message;
    for (int i = 0; i < size(message); i++) {
        Coded_Message.resize(Coded_Message.size() + 1);
        Coded_Message[size(Coded_Message) - 1] = encryption(e, n, int(message[i]));
        cout << "Буква " << message[i] << " в числовом виде: " << int(message[i]) << ",\t" << "Буква " << message[i]
            << " в закодированном виде: " << int(Coded_Message[size(Coded_Message) - 1]) << endl;
    }
    return Coded_Message;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n = 0, e = 0, d = 0;
    Key_generation(n, e, d);
    Users* b1 = new Users;
    User k = { "Алексей",{e,n}, {d,n} };
    b1->prev = NULL;
    b1->next = NULL;
    b1->b = k;
    tail = b1;
    head = b1;
    Users* ard = new Users;
    ard = head;
    cout << "Имя\t" << "Открытый ключ\t" << "Закрытый ключ" << endl << endl;
    while (ard) {
        cout << ard->b.Name << "\t" << "{" << ard->b.OpenKey[0] << "," << ard->b.OpenKey[1] << "}\t        {" << ard->b.SecretKey[0] << "," << ard->b.SecretKey[1] << "}\n";
        ard = ard->next;
    }
    char UserName[100];
    cout << "\nВведите имя пользователя, которому хотите отправить сообщение: ";
    cin >> UserName;
    cout << endl;
    Find_user(UserName, n, e, d);
    string message;
    cout << "Введите сообщение, которое хотите отправить: ";
    cin.ignore(1, '\n');
    getline(cin, message);
    cout << endl << endl;
    string Enscrypted = Word_encryption(message, e, n);
    cout << endl;
    for (int i = 0; i < Enscrypted.size(); i++) {
        cout << "Декодированное число " << int(Enscrypted[i]) << ": " << decryption(d, n, int(Enscrypted[i])) << endl << endl;
    }
    cout << "Итоговое декодированное сообщение: ";
    for (int i = 0; i < Enscrypted.size(); i++) {
        cout << char(decryption(d, n, int(Enscrypted[i])));
    }
    cout << endl;
    system("pause");
}