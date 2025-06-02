#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//не корректные тесты
//const char* filename = "ASY_WD_1.1.txt";//Не удалось открыть файл: ASY_WD_1.1.txt
//const char* filename = "ASY_WD_1.2.txt";//[ОШИБКА] Строка 2: недостаточно данных для обработки. > 07:20  RA - 89005 Новосибирск
//const char* filename = "ASY_WD_1.3.txt";//[ОШИБКА] Строка 3: недостаточно данных для обработки. > 15:50 Ту - 214  Самара
//const char* filename = "ASY_WD_1.4.txt";//[ОШИБКА] Строка 7: конфликт бортового номера с разными марками. > 17:00 Су - 34 RA - 85843 Новосибирск
//const char* filename = "ASY_WD_1.5.txt";//много различных ошибок
//корректные тесты
const char* filename = "ASY_WD_2.1.txt";

// Структура с информацией о рейсе
struct FlightInfo 
{
    char* time;   // Время посадки в формате "HH:MM"
    char* marka;  // Марка воздушного судна (ЛА)
    char* number; // Бортовой номер
    char* point;  // Пункт отправления
};

//прототипы ф-ций

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
    while (s[len] != '\0')
    {
        len++;
    }
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
    return true;
}

// Загрузка и валидация данных из файла
void loadData(const char* filename, FlightInfo*& flights, int& count)
{
    // Открытие входного файла для чтения
    ifstream file(filename);

    // Максимальный размер строки, читаемой из файла
    const int LINE_SIZE = 256;

    // Буфер для хранения текущей строки из файла
    char line[LINE_SIZE];

    // Буфер для хранения оригинальной (неизменённой) строки
    char original_line[LINE_SIZE];

    // Проверка, открылся ли файл
    if (!file)
    {
        error_coder(1); // Вызов обработчика ошибок: ошибка открытия файла
        return; // Прерывание выполнения функции
    }

    // Начальная вместимость массива полётов
    int capacity = 10;

    // Выделение памяти под массив полётов
    flights = new FlightInfo[capacity];

    // Счётчик прочитанных и успешно обработанных строк
    int line_num = 0;

    // Чтение файла построчно
    while (file.getline(line, LINE_SIZE))
    {
        // Очистка оставшейся части буфера после считанной строки
        for (int i = file.gcount(); i < LINE_SIZE; ++i)
        {
            line[i] = '\0'; // Заполняем остаток строки нулями
        }

        // Копирование строки в оригинальный буфер
        int i = 0;
        for (; i < LINE_SIZE - 1 && line[i] != '\0'; i++)
        {
            original_line[i] = line[i]; // Посимвольное копирование
        }
        original_line[i] = '\0'; // Завершение строки нулевым символом

        line_num++; // Увеличение номера строки

        // Пропускаем пустые строки
        if (line[0] == '\0')
        {
            continue;
        }

        int pos = 0; // Позиция для парсинга строки

        // Указатель на начало времени
        char* time_start = line + pos;

        // Поиск пробела или конца строки
        while (line[pos] != ' ' && line[pos] != '\0')
        {
            ++pos;
        }

        // Отделение времени от остального текста
        if (line[pos] != '\0')
        {
            line[pos++] = '\0'; // Заменяем пробел на конец строки и двигаемся дальше
        }

        // Пропуск пробелов между полями
        while (line[pos] == ' ')
        {
            ++pos;
        }


        // Указатель на начало марки
        char* marka_start = line + pos;

        // Поиск конца марки
        while (line[pos] != ' ' && line[pos] != '\0')
        {
            ++pos;
        }

        // Отделение марки от остального текста
        if (line[pos] != '\0')
        {
            line[pos++] = '\0';
        }

        // Пропуск пробелов перед следующим полем
        while (line[pos] == ' ')
        {
            ++pos;
        }


        // Указатель на начало номера
        char* number_start = line + pos;

        // Поиск конца номера
        while (line[pos] != ' ' && line[pos] != '\0')
        {
            ++pos;
        }

        // Отделение номера от остального текста
        if (line[pos] != '\0') 
        {
            line[pos++] = '\0';
        }
        // Пропуск пробелов перед следующей частью
        while (line[pos] == ' ')
        {
            ++pos;
        }


        // Указатель на начало пункта отправления
        char* point_start = line + pos;

        // Проверка, что поле отправления не пустое
        if (*point_start == '\0')
        {
            error_coder(4, line_num, original_line); // Ошибка: отсутствует поле
            continue; // Пропуск строки
        }

        //  Валидация 
        // Проверка, что поле времени заполнено
        if (*time_start == '\0')
        {
            error_coder(4, line_num, original_line); // Ошибка: отсутствует поле
            continue;
        }

        // Проверка, что поле марки заполнено
        if (*marka_start == '\0')
        {
            error_coder(4, line_num, original_line);
            continue;
        }

        // Проверка, что поле номера заполнено
        if (*number_start == '\0')
        {
            error_coder(4, line_num, original_line);
            continue;
        }

        // Проверка правильности формата времени
        if (!isValidTime(time_start))
        {
            error_coder(2, line_num, original_line); // Ошибка: неверный формат времени
            continue;
        }

        // Проверка правильности формата номера
        if (!isValidBoardNumber(number_start))
        {
            error_coder(3, line_num, original_line); // Ошибка: неверный формат номера
            continue;
        }

        // Проверка на дублирование времени
        bool duplicateTime = false;
        for (int j = 0; j < count; ++j)
        {
            if (stringsEqual(flights[j].time, time_start))
            {
                error_coder(5, line_num, original_line); // Ошибка: дублирующееся время
                duplicateTime = true;
                break;
            }
        }

        // Если найден дубликат времени, пропускаем строку
        if (duplicateTime)
        {
            continue;
        }
        // Проверка на конфликт марки с одинаковым номером
        bool conflictNumber = false;
        for (int j = 0; j < count; ++j)
        {
            if (stringsEqual(flights[j].number, number_start))
            {
                if (!stringsEqual(flights[j].marka, marka_start))
                {
                    error_coder(6, line_num, original_line); // Ошибка: конфликт номера и марки
                    conflictNumber = true;
                    break;
                }
            }
        }

        // Если найден конфликт, пропускаем строку
        if (conflictNumber)
        {
            continue;
        }

        //  Расширение массива при необходимости 
        if (count >= capacity)
        {
            capacity *= 2; // Увеличиваем вместимость вдвое
            FlightInfo* newArr = new FlightInfo[capacity]; // Новый массив
            for (int j = 0; j < count; ++j)
            {
                newArr[j] = flights[j]; // Копируем старые данные
            }
            delete[] flights; // Освобождаем старую память
            flights = newArr; // Переназначаем указатель
        }

        //Копирование данных в структуру 
        flights[count].time = copyNewString(time_start); // Копируем время
        flights[count].marka = copyNewString(marka_start); // Копируем марку
        flights[count].number = copyNewString(number_start); // Копируем номер
        flights[count].point = copyNewString(point_start); // Копируем пункт отправления

        count++; // Увеличиваем счётчик добавленных записей
    }

    // Закрытие файла
    file.close();
    return;
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
