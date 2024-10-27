#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

struct Student {
    char surname[50];
    char name[50];
    int course;
    char group[10];
    int marks[4];
};

void RW(Student* students, int n) {
    ofstream file("INFO.DAT", ios::binary);
    if (!file) {
        cerr << "Помилка вiдкриття файлу!" << endl;
        return;
    }
    file.write((char*)students, n * sizeof(Student));
    file.close();
}

double calculateMark(Student student) {
    double sum = 0;
    for (int i = 0; i < 4; i++) {
        sum += student.marks[i];
    }
    return sum / 4;
}

void RD(Student* students, int n) {
    ifstream file("INFO.DAT", ios::binary);

    if (!file) {
        cerr << "Помилка вiдкриття файлу!" << endl;
        return;
    }

    file.read((char*)students, n * sizeof(Student));
    file.close();

    cout << endl;
    cout << "Студенти по успiшностi:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (calculateMark(students[i]) < calculateMark(students[j])) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "Прiзвище: " << students[i].surname << endl;
        cout << "Iм'я: " << students[i].name << endl;
        cout << "Курс: " << students[i].course << endl;
        cout << "Група: " << students[i].group << endl;
        cout << "Оцiнки: ";
        for (int j = 0; j < 4; j++) {
            cout << students[i].marks[j] << " ";
        }
        cout << endl;
        cout << "Середнiй бал: " << calculateMark(students[i]) << endl;
    }
    cout << endl;

}


struct Carowner {
    char surname[50];
    char model[50];
    char number[15];
};

void RW(const char* filename, Carowner* owners, int n) {
    ofstream file(filename);
    if (!file) {
        cerr << "Помилка вiдкриття файлу!" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        file << owners[i].surname << endl;
        file << owners[i].model << endl;
        file << owners[i].number << endl;
    }
    file.close();
}

void RD(const char* filename, Carowner* owners, int n) {
    ifstream file(filename);
    if (!file) {
        cerr << "Помилка вiдкриття файлу!" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        file.getline(owners[i].surname, 50);
        file.getline(owners[i].model, 50);
        file.getline(owners[i].number, 15);
    }
    file.close();
}

void printNumber(Carowner* owners, int n) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (strstr(owners[i].number, "12") != nullptr || strstr(owners[i].number, "13") != nullptr) {
            cout << endl;
            cout << "Прiзвище власника машини: " << owners[i].surname << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Немає власників з номером 12-13." << endl;
    }
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color A");
    setlocale(LC_ALL, "Ukrainian");
    int n;
    cout << "Введiть кiлькiсть студентiв: ";
    cin >> n;
    Student* students = new Student[n];
    for (int i = 0; i < n; i++) {
        cout << endl;
        cout << "Введiть прiзвище студента: ";
        cin >> students[i].surname;
        cout << "Введiть iм'я студента: ";
        cin >> students[i].name;
        cout << "Введiть курс студента: ";
        cin >> students[i].course;
        cout << "Введiть групу студента: ";
        cin >> students[i].group;
        cout << "Введiть оцiнки студента: ";
        for (int j = 0; j < 4; j++) {
            cin >> students[i].marks[j];
        }
    }
    RW(students, n);
    RD(students, n);

    int N;
    cout << "Введiть кiлькiсть власникiв: ";
    cin >> N;
    cin.ignore(); 
    Carowner* owners = new Carowner[N];
    for (int i = 0; i < N; i++) {
        cout << endl;
        cout << "Введiть прiзвище власника: ";
        cin.getline(owners[i].surname, 50);
        cout << "Введiть марку автомобіля: ";
        cin.getline(owners[i].model, 50);
        cout << "Введiть номер автомобіля: ";
        cin.getline(owners[i].number, 15);
    }

    RW("INFO.TXT", owners, N);
    RD("INFO.TXT", owners, N);
    printNumber(owners, N);

    return 0;
}