#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
const int MAX_FLIGHTS = 20;

struct FlightInfo {
    char time[50];   // время посадки
    char marka[50];  // марка ЛА
    char number[50]; // бортовой номер
    char point[50];  // пункт отправления
};

void printTable(const FlightInfo flights[], int count);//ф-ция печати тпблицы
bool isDigit(char c);// Проверка является ли символ цифрой
int strLength(const char* s);//определение длины строки
bool isValidTime(const char* time);// Проверка корректности времени "HH:MM"
bool isValidBoardNumber(const char* number);// Проверка наличия '-' в строке и длины >=5
int loadData(const char* filename, FlightInfo flights[], int& count);// Загрузка данных из файла
bool lessThan(const char* s1, const char* s2);// Сравнение строк для сортировки (возвращает true если s1 < s2)
void indexSort(FlightInfo flights[], int indices[], int n);// Индексная сортировка по времени посадки


void printTable(const FlightInfo flights[], int count) {
    // Заголовок таблицы
    setlocale(LC_ALL, "C");
    cout << char(218) << setfill(char(196)) << setw(20) << char(194)
        << setw(20) << char(194) << setw(20) << char(194) << setw(20)
        << char(191) << endl;

    cout << char(179) << setfill(' ') << setw(19);
    setlocale(LC_ALL, "Russian");
    cout << "Время посадки";
    setlocale(LC_ALL, "C");
    cout << char(179) << setw(19);
    setlocale(LC_ALL, "Russian");
    cout << "Марка ЛА";
    setlocale(LC_ALL, "C");
    cout << char(179) << setw(19);
    setlocale(LC_ALL, "Russian");
    cout << "Бортовой №";
    setlocale(LC_ALL, "C");
    cout << char(179) << setw(19);
    setlocale(LC_ALL, "Russian");
    cout << "Пункт отправления";
    setlocale(LC_ALL, "C");
    cout << char(179) << endl;

    cout << char(195) << setfill(char(196)) << setw(20) << char(197)
        << setw(20) << char(197) << setw(20) << char(197) << setw(20)
        << char(180) << endl;

    // Строки таблицы
    for (int i = 0; i < count; ++i) {
        setlocale(LC_ALL, "C");
        cout << char(179) << setfill(' ') << setw(19);
        setlocale(LC_ALL, "Russian");
        cout << flights[i].time;
        setlocale(LC_ALL, "C");
        cout << char(179) << setw(19);
        setlocale(LC_ALL, "Russian");
        cout << flights[i].marka;
        setlocale(LC_ALL, "C");
        cout << char(179) << setw(19);
        setlocale(LC_ALL, "Russian");
        cout << flights[i].number;
        setlocale(LC_ALL, "C");
        cout << char(179) << setw(19);
        setlocale(LC_ALL, "Russian");
        cout << flights[i].point;
        setlocale(LC_ALL, "C");
        cout << char(179) << endl;
    }

    // Нижняя часть таблицы
    cout << char(192) << setfill(char(196)) << setw(20) << char(193)
        << setw(20) << char(193) << setw(20) << char(193) << setw(20)
        << char(217) << endl;
    setlocale(LC_ALL, "Russian");
}


// Проверка является ли символ цифрой
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Проверка длины строки
int strLength(const char* s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

// Проверка корректности времени "HH:MM"
bool isValidTime(const char* time) {
    if (strLength(time) != 5) return false;
    if (time[2] != ':') return false;

    if (!(isDigit(time[0]) && isDigit(time[1]) && isDigit(time[3]) && isDigit(time[4])))
        return false;

    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');

    return (hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60);
}

// Проверка наличия '-' в строке и длины >=5
bool isValidBoardNumber(const char* number) {
    int len = strLength(number);
    if (len < 5) return false;

    for (int i = 0; i < len; ++i) {
        if (number[i] == '-') return true;
    }
    return false;
}

// Загрузка данных из файла
int loadData(const char* filename, FlightInfo flights[], int& count) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка при открытии файла.\n";
        return 1;
    }

    count = 0;
    while (file >> flights[count].time >> flights[count].marka
        >> flights[count].number >> flights[count].point) {

        if (!isValidTime(flights[count].time)) {
            cerr << "Ошибка: некорректное время посадки: " << flights[count].time << endl;
            return 2;
        }

        if (!isValidBoardNumber(flights[count].number)) {
            cerr << "Ошибка: некорректный бортовой номер: " << flights[count].number << endl;
            return 3;
        }

        count++;
        if (count >= MAX_FLIGHTS) break;
    }

    file.close();
    return 0;
}

// Сравнение строк для сортировки (возвращает true если s1 < s2)
bool lessThan(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) return true;
        if (s1[i] > s2[i]) return false;
        i++;
    }
    // Если одна строка короче и совпала до конца, она считается меньше
    if (s1[i] == '\0' && s2[i] != '\0') return true;
    return false;
}

// Индексная сортировка по времени посадки
void indexSort(FlightInfo flights[], int indices[], int n) {
    for (int i = 0; i < n; ++i) indices[i] = i;

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (lessThan(flights[indices[j]].time, flights[indices[min_idx]].time))
                min_idx = j;
        }
        int temp = indices[i];
        indices[i] = indices[min_idx];
        indices[min_idx] = temp;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    FlightInfo flights[MAX_FLIGHTS];
    FlightInfo sortedFlights[MAX_FLIGHTS];
    int count;
    int indices[MAX_FLIGHTS];

    if (loadData("ASY_WD_1.1.txt", flights, count) != 0) {
        return 1;
    }

    // Вывод данных ДО сортировки
    cout << "Данные до сортировки:" << endl;
    printTable(flights, count);
    
    

    // Сортируем
    indexSort(flights, indices, count);
    for (int i = 0; i < count; i++)
        sortedFlights[i] = flights[indices[i]];
    // Вывод данных ПОСЛЕ сортировки
    cout << "\nДанные после сортировки по времени посадки:" << endl;
    printTable(sortedFlights, count);

    return 0;
}