#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//не коректныу тесты
//const char* filename = "ASY_WD_1.1.txt";//Не удалось открыть файл: ASY_WD_1.1.txt
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

//коректные тесты
const char* filename = "ASY_WD_2.1.txt";

// Структура с информацией о рейсе
struct FlightInfo 
{
    char* time;   // Время посадки в формате "HH:MM"
    char* marka;  // Марка воздушного судна (ЛА)
    char* number; // Бортовой номер
    char* point;  // Пункт отправления
};

// Обработка ошибок: выводит сообщение в консоль по коду ошибки
void error_coder(int code,//код ошибки
    int line = -1,//строка в файле данных
    const char* line_text = nullptr)//содержимое строки
{
    switch (code) {
    case 1:
        cerr << "[ОШИБКА] Не удалось открыть файл." << endl;
        break;
    case 2:
        cerr << "[ОШИБКА] Строка " << line << ": некорректное время посадки." << endl;
        break;
    case 3:
        cerr << "[ОШИБКА] Строка " << line << ": некорректный бортовой номер или марка ЛА." << endl;
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
    if (line_text)
    {
        cerr << "   > " << line_text << endl; // Показывает текст строки с ошибкой, если передан
    }
}

// Функция вывода таблицы с рейсами
void printTable(const FlightInfo flights[],//структура
    int count)//кол-во строк в таблице
{
    setlocale(LC_ALL, "C");
    // Верхняя граница таблицы
    cout << char(218) << setfill(char(196)) << setw(20) << char(194)
        << setw(20) << char(194) << setw(20) << char(194) << setw(20)
        << char(191) << endl;

    // Заголовки таблицы
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

    // Разделительная линия под заголовками
    cout << char(195) << setfill(char(196)) << setw(20) << char(197)
        << setw(20) << char(197) << setw(20) << char(197) << setw(20)
        << char(180) << endl;

    // Строки таблицы с рейсами
    for (int i = 0; i < count; ++i)
    {
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

    // Нижняя граница таблицы
    cout << char(192) << setfill(char(196)) << setw(20) << char(193)
        << setw(20) << char(193) << setw(20) << char(193) << setw(20)
        << char(217) << endl;
    setlocale(LC_ALL, "Russian");
}

//ф-ция подсчёта длины строки
int strLength(const char* s)
{
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

//ф-ция создает динамическую копию строки src в новой области памяти и возвращает указатель на неё.
char* copyNewString(const char* src)
{
    int len = strLength(src);
    char* dest = new char[len + 1]; // +1 под нуль-терминатор
    for (int i = 0; i <= len; ++i)
    {
        dest[i] = src[i];
    }
    return dest;
}

// Проверка: символ — цифра?
bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

// Проверка корректности времени: формат "HH:MM", часы от 0 до 23, минуты от 0 до 59
bool isValidTime(const char* time)
{
    if (strLength(time) != 5 || time[2] != ':')
    {
        return false;
    }
    if (!isDigit(time[0])) 
    {
        return false;
    }
    if (!isDigit(time[1])) 
    {
        return false;
    }
    if (!isDigit(time[3])) 
    {
        return false;
    }
    if (!isDigit(time[4]))
    {
        return false;
    }
    int h = (time[0] - '0') * 10 + (time[1] - '0');
    int m = (time[3] - '0') * 10 + (time[4] - '0');
    if (h < 0 || h >= 24)
    {
        return false;
    }
    if (m < 0 || m >= 60)
    {
        return false;
    }
    return true;
}

// Проверка корректности бортового номера (наличие дефиса)
bool isValidBoardNumber(const char* number) 
{
    int len = strLength(number);
    if (len < 5)
    {
        return false;
    }
    for (int i = 0; i < len; ++i)
    {
        if (number[i] == '-')
        {
            return true;
        }
    }
    return false;
}

// Сравнение строк
bool stringsEqual(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return false;
        }
        i++;
    }
    return a[i] == b[i];
}

// Загрузка и валидация данных из файла
void loadData(const char* filename,
    FlightInfo*& flights,
    int& count)
{
    ifstream file(filename); // Открытие файла для чтения
    const int LINE_SIZE = 256;
    char line[LINE_SIZE]; // Буфер для считывания строки
    count = 0; // Начальное количество загруженных рейсов

    // Проверка открытия файла
    if (!file) 
    {
        error_coder(1); // Ошибка открытия файла
        return;
    }

    int capacity = 10; // Начальная вместимость массива
    flights = new FlightInfo[capacity]; // Выделение памяти под массив структур
    int line_num = 0; // Номер текущей строки в файле

    // Построчное чтение файла
    while (file.getline(line, LINE_SIZE))
    {
        line_num++;
        if (line[0] == '\0')
        {
            continue; // Пропуск пустых строк
        }
        int pos = 0;

        
        // Указатель на начало времени
        char* time_start = line + pos;
        while (line[pos] != ' ' && line[pos] != '\0')
        {
            ++pos;
        }
        line[pos++] = '\0'; // Завершаем строку времени

        // Пропускаем пробелы между полями
        while (line[pos] == ' ')
        {
            ++pos;
        }
        // Указатель на начало марки
        char* marka_start = line + pos;
        while (line[pos] != ' ' && line[pos] != '\0')
        {
            ++pos;
        }
        line[pos++] = '\0'; // Завершаем строку марки

        while (line[pos] == ' ')
        {
            ++pos;
        }
        // Указатель на начало номера борта
        char* number_start = line + pos;
        while (line[pos] != ' ' && line[pos] != '\0')
        {
            ++pos;
        }
        line[pos++] = '\0'; // Завершаем строку номера

        while (line[pos] == ' ')
        {
            ++pos;
        }
        // Указатель на начало пункта назначения
        char* point_start = line + pos;
        // Последнее поле до конца строки — завершать не нужно

        // --- Проверка корректности данных ---
        if (*time_start == '\0') 
        {
            error_coder(4, line_num, line); // Поле времени пустое
            continue;
        }
        if (*marka_start == '\0') 
        {
            error_coder(4, line_num, line); // Поле марки пустое
            continue;
        }
        if (*number_start == '\0')
        {
            error_coder(4, line_num, line); // Поле номера пустое
            continue;
        }
        if (*point_start == '\0') 
        {
            error_coder(4, line_num, line); // Поле пункта назначения пустое
            continue;
        }

        if (!isValidTime(time_start)) 
        {
            error_coder(2, line_num, line); // Неверный формат времени
            continue;
        }

        if (!isValidBoardNumber(number_start))
        {
            error_coder(3, line_num, line); // Неверный номер борта
            continue;
        }

        // Проверка на повтор времени вылета
        bool duplicateTime = false;
        for (int j = 0; j < count; ++j)
        {
            if (stringsEqual(flights[j].time, time_start))
            {
                error_coder(5, line_num, line); // Повтор времени
                duplicateTime = true;
                break;
            }
        }
        if (duplicateTime)
        {
            continue;
        }
        // Проверка на конфликт марок при одинаковом номере
        bool conflictNumber = false;
        for (int j = 0; j < count; ++j)
        {
            if (stringsEqual(flights[j].number, number_start)) {
                if (!stringsEqual(flights[j].marka, marka_start)) {
                    error_coder(6, line_num, line); // Один и тот же номер у разных марок
                    conflictNumber = true;
                    break;
                }
            }
        }
        if (conflictNumber)
        {
            continue;
        }
        // Расширение массива при нехватке места
        if (count >= capacity)
        {
            capacity *= 2;
            FlightInfo* newArr = new FlightInfo[capacity];
            for (int j = 0; j < count; ++j)
            {
                newArr[j] = flights[j];
            }
            delete[] flights; // Освобождаем старый массив
            flights = newArr;
        }

        // --- Копирование строки в структуру ---
        flights[count].time = copyNewString(time_start);
        flights[count].marka = copyNewString(marka_start);
        flights[count].number = copyNewString(number_start);
        flights[count].point = copyNewString(point_start);
        count++; // Увеличиваем количество записей
    }

    file.close(); // Закрываем файл
}


// Сравнение строк — используется для сортировки по времени
bool lessThan(const char* s1,
    const char* s2) 
{
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] < s2[i])
        {
            return true;
        }
        if (s1[i] > s2[i])
        {
            return false;
        }
        i++;
    }
    return s1[i] == '\0' && s2[i] != '\0';
}

// Индексная сортировка массива FlightInfo по времени посадки 
void indexSort(FlightInfo flights[],//структура
    int indices[],//массив индексов для сортировки 
    int n)//кол-во элементов
{
    // Инициализируем массив индексов
    for (int i = 0; i < n; ++i)
    {
        indices[i] = i;
    }
    int Min, jMin, Temp;

    for (int iSort = 0; iSort < n - 1; iSort++)
    {
        Min = indices[iSort];
        jMin = iSort;

        for (int j = iSort + 1; j < n; j++)
        {
            if (lessThan(flights[indices[j]].time, flights[Min].time)) 
            {
                Min = indices[j];
                jMin = j;
            }
        }

        Temp = indices[iSort];
        indices[iSort] = indices[jMin];
        indices[jMin] = Temp;
    }
}


// Главная функция программы
int main() {
    setlocale(LC_ALL, "Russian");

    FlightInfo* flights = nullptr;
    int count = 0;

    // Загрузка данных из файла
    loadData(filename, flights, count);
    if (!flights)
    {
        return 1;
    }
    // Вывод исходных данных
    cout << "Данные до сортировки:\n";
    printTable(flights, count);

    // Индексная сортировка по времени
    int* indices = new int[count];
    indexSort(flights, indices, count);

    // Копируем отсортированные рейсы в новый массив
    FlightInfo* sortedFlights = new FlightInfo[count];
    for (int i = 0; i < count; ++i)
    {
        sortedFlights[i] = flights[indices[i]];
    }
    // Вывод отсортированных данных
    cout << "\nДанные после сортировки по времени посадки:\n";
    printTable(sortedFlights, count);

    // Очистка динамически выделенной памяти
    for (int i = 0; i < count; ++i) 
    {
        delete[] flights[i].time;
        delete[] flights[i].marka;
        delete[] flights[i].number;
        delete[] flights[i].point;

    }
    delete[] flights;
    delete[] sortedFlights;
    delete[] indices;

    return 0;
}
