#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

string sozdatStroku(int dlina) {
    string stroka = "";

    for (int i = 0; i < dlina; i++) {
        stroka += char('A' + rand() % 26);
    }

    return stroka;
}

int rasstoyanieRekursiya(const string& pervaya, const string& vtoraya, int i, int j) {
    if (i == 0) return j;
    if (j == 0) return i;

    int cena;

    if (pervaya[i - 1] == vtoraya[j - 1]) {
        cena = 0;
    }
    else {
        cena = 1;
    }

    return min({
        rasstoyanieRekursiya(pervaya, vtoraya, i - 1, j) + 1, //удаление
        rasstoyanieRekursiya(pervaya, vtoraya, i, j - 1) + 1,//вставка 
        rasstoyanieRekursiya(pervaya, vtoraya, i - 1, j - 1) + cena //замена
        });
}

int rasstoyanieDP(const string& pervaya, const string& vtoraya) {
    int dlina1 = pervaya.size();
    int dlina2 = vtoraya.size();

    vector<vector<int>> tablitsa(dlina1 + 1, vector<int>(dlina2 + 1));

    for (int i = 0; i <= dlina1; i++) {
        tablitsa[i][0] = i;
    }

    for (int j = 0; j <= dlina2; j++) {
        tablitsa[0][j] = j;
    }

    for (int i = 1; i <= dlina1; i++) {
        for (int j = 1; j <= dlina2; j++) {
            int cena;

            if (pervaya[i - 1] == vtoraya[j - 1]) {
                cena = 0;
            }
            else {
                cena = 1;
            }

            tablitsa[i][j] = min({
                tablitsa[i - 1][j] + 1,
                tablitsa[i][j - 1] + 1,
                tablitsa[i - 1][j - 1] + cena
                });
        }
    }

    return tablitsa[dlina1][dlina2];
}

int nopRekursiya(const string& pervaya, const string& vtoraya, int i, int j) {
    if (i == 0 || j == 0) {
        return 0;
    }

    if (pervaya[i - 1] == vtoraya[j - 1]) {
        return 1 + nopRekursiya(pervaya, vtoraya, i - 1, j - 1);
    }

    return max(
        nopRekursiya(pervaya, vtoraya, i - 1, j),
        nopRekursiya(pervaya, vtoraya, i, j - 1)
    );
}

int nopDP(const string& pervaya, const string& vtoraya, string& otvet) {
    int dlina1 = pervaya.size();
    int dlina2 = vtoraya.size();

    vector<vector<int>> tablitsa(dlina1 + 1, vector<int>(dlina2 + 1));

    for (int i = 1; i <= dlina1; i++) {
        for (int j = 1; j <= dlina2; j++) {
            if (pervaya[i - 1] == vtoraya[j - 1]) {
                tablitsa[i][j] = tablitsa[i - 1][j - 1] + 1;
            }
            else {
                tablitsa[i][j] = max(tablitsa[i - 1][j], tablitsa[i][j - 1]);
            }
        }
    }

    otvet = "";

    int i = dlina1;
    int j = dlina2;

    while (i > 0 && j > 0) {
        if (pervaya[i - 1] == vtoraya[j - 1]) {
            otvet += pervaya[i - 1];
            i--;
            j--;
        }
        else if (tablitsa[i - 1][j] > tablitsa[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    reverse(otvet.begin(), otvet.end());

    return tablitsa[dlina1][dlina2];
}

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    string s1 = sozdatStroku(300);
    string s2 = sozdatStroku(200);


    cout << "Задание 1. Генерация строк" << endl;
    cout << "Длина S1 = " << s1.size() << endl;
    cout << "S1 = " << s1 << endl;
    cout << "Длина S2 = " << s2.size() << endl;
    cout << "S2 = " << s2 << endl << endl;

    cout << "Задания 2-3. Дистанция Левенштейна" << endl;
    cout << "n | дистанция | рекурсия, мкс | ДП, мкс" << endl;

    for (int n = 1; n <= 8; n++) {
        string pervaya = s1.substr(0, n);
        string vtoraya = s2.substr(0, n);

        auto nachalo1 = high_resolution_clock::now();
        int otvetRekursiya = rasstoyanieRekursiya(pervaya, vtoraya, pervaya.size(), vtoraya.size());
        auto konets1 = high_resolution_clock::now();

        auto nachalo2 = high_resolution_clock::now();
        int otvetDP = rasstoyanieDP(pervaya, vtoraya);
        auto konets2 = high_resolution_clock::now();

        double vremyaRekursiya = duration<double, micro>(konets1 - nachalo1).count();
        double vremyaDP = duration<double, micro>(konets2 - nachalo2).count();

        cout << n << " | "
            << otvetDP << " | "
            << fixed << setprecision(3) << vremyaRekursiya << " | "
            << fixed << setprecision(3) << vremyaDP << endl;
    }

    cout << endl;
    cout << "Дистанция Левенштейна для полных строк S1 и S2 методом ДП: ";
    cout << rasstoyanieDP(s1, s2) << endl << endl;

    cout << "Задание 4" << endl;
    cout << "Слова: град и город" << endl;
    cout << "Дистанция Левенштейна = " <<rasstoyanieDP("град", "город") << endl << endl;

    string x = "ABCDEFG";
    string y = "BMDRFI";
    string otvetNop;

    cout << "Задание 5. Наибольшая общая подпоследовательность" << endl;
    cout << "X = " << x << endl;
    cout << "Y = " << y << endl;

    int dlinaNop = nopDP(x, y, otvetNop);

    cout << "НОП = " << otvetNop << endl;
    cout << "Длина НОП = " << dlinaNop << endl << endl;

    cout << "Сравнение времени для НОП" << endl;
    cout << "n | длина НОП | рекурсия, мкс | ДП, мкс" << endl;

    for (int n = 1; n <= 6; n++) {
        string pervaya = x.substr(0, n);
        string vtoraya = y.substr(0, n);
        string vremennayaStroka;

        auto nachalo1 = high_resolution_clock::now();
        int otvetRekursiya = nopRekursiya(pervaya, vtoraya, pervaya.size(), vtoraya.size());
        auto konets1 = high_resolution_clock::now();

        auto nachalo2 = high_resolution_clock::now();
        int otvetDP = nopDP(pervaya, vtoraya, vremennayaStroka);
        auto konets2 = high_resolution_clock::now();

        double vremyaRekursiya = duration<double, micro>(konets1 - nachalo1).count();
        double vremyaDP = duration<double, micro>(konets2 - nachalo2).count();

        cout << n << " | "
            << otvetDP << " | "
             << setprecision(3) << vremyaRekursiya << " | "
            << setprecision(3) << vremyaDP << endl;
    }

    return 0;
}