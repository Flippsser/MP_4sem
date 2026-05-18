// Main.cpp
#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

#include "Combi.h"
#include "Tsp.h"

void demo_subset()
{
    char AA[][2] = { "A", "B", "C", "D" };
    std::cout << "\n - Генератор множества всех подмножеств -";
    std::cout << "\nИсходное множество: { ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";

    combi::subset s1(sizeof(AA) / 2);
    int n = s1.getfirst();
    while (n >= 0)
    {
        std::cout << "\n{ ";
        for (int i = 0; i < n; i++)
            std::cout << AA[s1.ntx(i)] << ((i < n - 1) ? ", " : " ");
        std::cout << "}";
        n = s1.getnext();
    }
    std::cout << "\nвсего: " << s1.count() << "\n";
}

void demo_combination()
{
    char AA[][2] = { "A", "B", "C", "D", "E" };
    std::cout << "\n --- Генератор сочетаний ---";
    std::cout << "\nИсходное множество: { ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";

    combi::xcombination xc(sizeof(AA) / 2, 3);
    std::cout << "\nГенерация сочетаний из " << xc.n << " по " << xc.m;
    int n = xc.getfirst();
    while (n >= 0)
    {
        std::cout << "\n" << xc.nc << ": { ";
        for (int i = 0; i < n; i++)
            std::cout << AA[xc.ntx(i)] << ((i < n - 1) ? ", " : " ");
        std::cout << "}";
        n = xc.getnext();
    }
    std::cout << "\nвсего: " << xc.count() << "\n";
}

void demo_permutation()
{
    char AA[][2] = { "A", "B", "C", "D" };
    std::cout << "\n --- Генератор перестановок ---";
    std::cout << "\nИсходное множество: { ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";

    combi::permutation p(sizeof(AA) / 2);
    __int64 n = p.getfirst();
    while (n >= 0)
    {
        std::cout << "\n" << std::setw(4) << p.np << ": { ";
        for (int i = 0; i < p.n; i++)
            std::cout << AA[p.ntx(i)] << ((i < p.n - 1) ? ", " : " ");
        std::cout << "}";
        n = p.getnext();
    }
    std::cout << "\nвсего: " << p.count() << "\n";
}

void demo_arrangement()
{
    char AA[][2] = { "A", "B", "C", "D" };
    std::cout << "\n --- Генератор размещений ---";
    std::cout << "\nИсходное множество: { ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";

    combi::arrangement ar(sizeof(AA) / 2, 3);
    int n = ar.getfirst();
    std::cout << "\nГенерация размещений из " << ar.n << " по " << ar.m;
    while (n >= 0)
    {
        std::cout << "\n{ ";
        for (int i = 0; i < n; i++)
            std::cout << AA[ar.ntx(i)] << ((i < n - 1) ? ", " : " ");
        std::cout << "}";
        n = ar.getnext();
    }
    std::cout << "\nвсего: " << ar.count() << "\n";
}

// генерация случайной матрицы расстояний для TSP
void gen_random_dist(short n, int* dist, int infEdges)
{
    // расстояния 10–300, infEdges ребер делаем "бесконечными"
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i * n + j] = (i == j) ? INF_DIST : (10 + rand() % 291);

    // делаем infEdges случайных "бесконечных" расстояний
    int cnt = 0;
    while (cnt < infEdges)
    {
        int i = rand() % n;
        int j = rand() % n;
        if (i != j && dist[i * n + j] < INF_DIST)
        {
            dist[i * n + j] = INF_DIST;
            cnt++;
        }
    }
}

void solve_tsp_example()
{
    const short N = 10;
    int dist[N * N];
    short bestRoute[N + 1];

    gen_random_dist(N, dist, 3);

    std::cout << "\n--- Задача коммивояжёра (N = 10) ---\n";
    std::cout << "Матрица расстояний (INF = X):\n";
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (dist[i * N + j] >= INF_DIST)
                std::cout << std::setw(4) << "X";
            else
                std::cout << std::setw(4) << dist[i * N + j];
        }
        std::cout << "\n";
    }

    int best = solve_tsp(N, dist, bestRoute);
    if (best >= INF_DIST)
    {
        std::cout << "Маршрут не найден (граф разорван).\n";
    }
    else
    {
        std::cout << "Лучший маршрут: ";
        for (int i = 0; i <= N; ++i)
            std::cout << bestRoute[i] << (i < N ? " -> " : "");
        std::cout << "\nДлина маршрута: " << best << "\n";
    }
}

// исследование зависимости времени от числа городов (6–12)
void tsp_timing()
{
    std::cout << "\n--- Исследование времени решения TSP ---\n";
    std::cout << "N   time (ticks)\n";

    for (short n = 6; n <= 12; ++n)
    {
        int* dist = new int[n * n];
        short* route = new short[n + 1];

        gen_random_dist(n, dist, 3); // 3 бесконечных ребра

        clock_t t1 = clock();
        int best = solve_tsp(n, dist, route);
        clock_t t2 = clock();

        std::cout << std::setw(2) << n << "   " << (t2 - t1) << "\n";

        delete[] dist;
        delete[] route;
    }
}

void verify_tsp_with_permutations()
{
    const short N = 5;  // количество городов
    // Матрица расстояний из лабораторной №3 (вариант 1, n=1)
    int dist[N * N] = {
        INF_DIST, 1, 20, 4, 21,
        2, INF_DIST, 13, 39, 67,
        8, 2, INF_DIST, 72, 38,
        19, 54, 3, INF_DIST, 2,
        84, 33, 45, 13, INF_DIST
    };
    short bestRoute[N + 1];  // для маршрута (с замыканием в 0)

    std::cout << "\n--- Проверка решения для 5 городов (методом перестановок) ---\n";
    std::cout << "Матрица расстояний:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (dist[i * N + j] >= INF_DIST)
                std::cout << std::setw(4) << "INF";
            else
                std::cout << std::setw(4) << dist[i * N + j];
        }
        std::cout << "\n";
    }

    int best = solve_tsp(N, dist, bestRoute);

    if (best >= INF_DIST) {
        std::cout << "Маршрут не найден (граф разорван).\n";
    }
    else {
        std::cout << "Оптимальный маршрут: ";
        for (int i = 0; i <= N; ++i)
            std::cout << bestRoute[i] << (i < N ? " -> " : "");
        std::cout << "\nДлина маршрута: " << best << "\n";
        std::cout << "Совпадает с решением метода ветвей и границ? ";
        if (best == 41)  // подставьте свою длину из лаб.3
            std::cout << "ДА\n";
        else
            std::cout << "НЕТ (проверьте вычисления)\n";
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand((unsigned)time(NULL));
    verify_tsp_with_permutations();

    // Задания 1–4: демонстрация генераторов
    demo_subset();
    demo_combination();
    demo_permutation();
    demo_arrangement();

    // Задание 5: задача коммивояжёра (10 городов)
    solve_tsp_example();

    // Задание 6: исследование времени (6–12 городов)
    tsp_timing();

    std::cout << "\n";
    system("pause");
    return 0;
}
