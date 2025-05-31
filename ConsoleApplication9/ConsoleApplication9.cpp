#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_FLIGHTS = 20;
//не коректныу тесты
const char* filename = "ASY_WD_1.1.txt";//Не удалось открыть файл: ASY_WD_1.1.txt
//const char* filename = "ASY_WD_1.2.txt";
/*
[ОШИБКА] Строка 2: недостаточно данных для обработки.
   > 07:20 SSJ-100 RA-89005
[ОШИБКА] Строка 3: некорректный бортовой номер или марка ЛА
   > 15:50 RA-64521 Самара
[ОШИБКА] Строка 7: некорректное время посадки
   > Су-34 RA-93005 Новосибирск
[ОШИБКА] Строка 9: некорректный бортовой номер или марка ЛА
   > 09:45 RA-89001 Омск
[ОШИБКА] Строка 12: недостаточно данных для обработки.
   > 13:25 Ту-204 Ростов-на-Дону
[ОШИБКА] Строка 15: недостаточно данных для обработки.
   > 09:00 Ил-96 Нижневартовск
[ОШИБКА] Строка 19: некорректный бортовой номер или марка ЛА
   > 12:00 RA-89123 Казань
*/
//const char* filename = "ASY_WD_1.3.txt";//повтор времени посадки
//const char* filename = "ASY_WD_1.4.txt";//конфликт бортового номера с разными марками.

struct FlightInfo {
    char time[6];
    char marka[8];
    char number[20];
    char point[50];
};

// Функции
void printTable(const FlightInfo flights[], int count);
bool isDigit(char c);
int strLength(const char* s);
bool isValidTime(const char* time);
bool isValidBoardNumber(const char* number);
bool stringsEqual(const char* a, const char* b);
void copyString(char* dest, const char* src, int maxLen);
bool lessThan(const char* s1, const char* s2);
void indexSort(FlightInfo flights[], int indices[], int n);

// Обработка ошибок
void error_coder(int code, int line = -1, const char* line_text = nullptr, const FlightInfo* flights = nullptr, int count = 0) {
    switch (code) {
    case 1:
        cerr << "[ОШИБКА] Не удалось открыть файл: " << filename << endl;
        break;
    case 2:
        cerr << "[ОШИБКА] Строка " << line << ": некорректное время посадки " << (flights ? flights[count].time : "") << endl;
        break;
    case 3:
        cerr << "[ОШИБКА] Строка " << line << ": некорректный бортовой номер или марка ЛА " << (flights ? flights[count].number : "") << endl;
        break;
    case 4:
        cerr << "[ОШИБКА] Строка " << line << ": недостаточно данных для обработки." << endl;
        break;
    case 5:
        cerr << "[ОШИБКА] Строка " << line << ": повтор времени посадки." << endl;
        break;
    case 6:
        cerr << "[ОШИБКА] Строка " << line << ": конфликт бортового номера с разными марками." << endl;
        break;
    default:
        cerr << "[ОШИБКА] Неизвестный код ошибки: " << code << endl;
        break;
    }

    if (line_text) {
        cerr << "   > " << line_text << endl;
    }
}

void printTable(const FlightInfo flights[], int count) {
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

    cout << char(192) << setfill(char(196)) << setw(20) << char(193)
        << setw(20) << char(193) << setw(20) << char(193) << setw(20)
        << char(217) << endl;
    setlocale(LC_ALL, "Russian");
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

int strLength(const char* s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

bool isValidTime(const char* time) {
    if (strLength(time) != 5) return false;
    if (time[2] != ':') return false;
    if (!(isDigit(time[0]) && isDigit(time[1]) && isDigit(time[3]) && isDigit(time[4])))
        return false;
    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');
    return (hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60);
}

bool isValidBoardNumber(const char* number) {
    int len = strLength(number);
    if (len < 5) return false;
    for (int i = 0; i < len; ++i) {
        if (number[i] == '-') return true;
    }
    return false;
}

bool stringsEqual(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

void copyString(char* dest, const char* src, int maxLen) {
    int i = 0;
    for (; i < maxLen - 1 && src[i] != '\0'; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
}

void loadData(const char* filename, FlightInfo flights[], int& count, int& code_err, int& error_line) {
    ifstream file(filename);
    const int LINE_SIZE = 256;
    char line[LINE_SIZE];
    count = 0;
    error_line = 0;

    if (!file) {
        code_err = 1;
        error_coder(code_err);
        return;
    }

    while (file.getline(line, LINE_SIZE)) {
        error_line++;
        if (line[0] == '\0') continue;

        char time[6] = {}, marka[8] = {}, number[20] = {}, point[50] = {};
        int pos = 0, i = 0;

        // Время
        while (line[pos] != ' ' && line[pos] != '\0' && i < 5)
            time[i++] = line[pos++];
        time[i] = '\0';
        while (line[pos] == ' ') pos++;

        // Марка
        i = 0;
        while (line[pos] != ' ' && line[pos] != '\0' && i < 7)
            marka[i++] = line[pos++];
        marka[i] = '\0';
        while (line[pos] == ' ') pos++;

        // Бортовой номер
        i = 0;
        while (line[pos] != ' ' && line[pos] != '\0' && i < 19)
            number[i++] = line[pos++];
        number[i] = '\0';
        while (line[pos] == ' ') pos++;

        // Пункт
        i = 0;
        while (line[pos] != '\0' && i < 49)
            point[i++] = line[pos++];
        point[i] = '\0';

        if (time[0] == '\0' || marka[0] == '\0' || number[0] == '\0' || point[0] == '\0') {
            error_coder(4, error_line, line);
            continue;
        }
        if (!isValidTime(time)) {
            error_coder(2, error_line, line);
            continue;
        }
        if (!isValidBoardNumber(number)) {
            error_coder(3, error_line, line);
            continue;
        }

        bool duplicateTime = false;
        for (int j = 0; j < count; ++j) {
            if (stringsEqual(flights[j].time, time)) {
                error_coder(5, error_line, line);
                duplicateTime = true;
                break;
            }
        }
        if (duplicateTime) continue;

        bool conflictNumber = false;
        for (int j = 0; j < count; ++j) {
            if (stringsEqual(flights[j].number, number) && !stringsEqual(flights[j].marka, marka)) {
                error_coder(6, error_line, line);
                conflictNumber = true;
                break;
            }
        }
        if (conflictNumber) continue;

        copyString(flights[count].time, time, 6);
        copyString(flights[count].marka, marka, 8);
        copyString(flights[count].number, number, 20);
        copyString(flights[count].point, point, 50);
        count++;
        if (count >= MAX_FLIGHTS) break;
    }

    file.close();
}

bool lessThan(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) return true;
        if (s1[i] > s2[i]) return false;
        i++;
    }
    return s1[i] == '\0' && s2[i] != '\0';
}

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
    int code_err = 0, error_line = -1, count = 0;
    int indices[MAX_FLIGHTS];

    loadData(filename, flights, count, code_err, error_line);
    if (code_err == 1) 
    {
        return 1;
    }
    cout << "Данные до сортировки:" << endl;
    printTable(flights, count);

    indexSort(flights, indices, count);
    for (int i = 0; i < count; i++)
        sortedFlights[i] = flights[indices[i]];

    cout << "\nДанные после сортировки по времени посадки:" << endl;
    printTable(sortedFlights, count);

    return 0;
}
