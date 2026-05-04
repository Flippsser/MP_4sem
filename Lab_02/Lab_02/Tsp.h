// Tsp.h комивояджер
#pragma once
#include "Combi.h"

const int INF_DIST = 1000000000; // "бесконечность"

int solve_tsp(
    short n,          // [in] количество городов
    const int* dist,  // [in] матрица расстояний n*n (строчно)
    short* bestRoute  // [out] лучший маршрут (последовательность городов)
);
