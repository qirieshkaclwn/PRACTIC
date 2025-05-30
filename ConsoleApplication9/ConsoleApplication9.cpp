#include <iostream>
#include <iomanip>
using namespace std;

struct FlightInfo {
    const char* time;//время посадки
    const char* marka;//марка ЛА
    const char* number;//бортовой номер
    const char* point;//пункт отправления
};

void printTableHeader() {
    cout << char(218) << setfill(char(196)) << setw(20) << char(194)
        << setw(20) << char(194) << setw(20) << char(194) << setw(20)
        << char(191) << endl;

    setlocale(LC_ALL, "C");
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
}

void printFlightRow(const FlightInfo& flight) {
    setlocale(LC_ALL, "C");
    cout << char(179) << setfill(' ') << setw(19);
    setlocale(LC_ALL, "Russian");
    cout << flight.time;
    setlocale(LC_ALL, "C");
    cout << char(179) << setw(19);
    setlocale(LC_ALL, "Russian");
    cout << flight.marka;
    setlocale(LC_ALL, "C");
    cout << char(179) << setw(19);
    setlocale(LC_ALL, "Russian");
    cout << flight.number;
    setlocale(LC_ALL, "C");
    cout << char(179) << setw(19);
    setlocale(LC_ALL, "Russian");
    cout << flight.point;
    setlocale(LC_ALL, "C");
    cout << char(179) << endl;
}

void printTableBottom() {
    cout << char(192) << setfill(char(196)) << setw(20) << char(193)
        << setw(20) << char(193) << setw(20) << char(193) << setw(20)
        << char(217) << endl;
}

int main() {
    FlightInfo flights[] = {
        {"10:30", "Ту-154", "RA-85843", "Москва"},
        {"11:15", "Боинг 737", "VP-BNG", "Сочи"},
        {"12:00", "А320", "RA-89123", "Казань"}
    };

    printTableHeader();

    for (const auto& flight : flights) {
        printFlightRow(flight);
    }

    printTableBottom();

    return 0;
}
