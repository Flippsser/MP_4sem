// Tsp.cpp комивояджер
#include "Tsp.h"
#include <limits>

int solve_tsp(short n, const int* dist, short* bestRoute)
{
    if (n <= 1) return 0;

    combi::permutation p(n - 1);
    // будем фиксировать город 0 стартовым,
    // а переставлять города 1..n-1

    __int64 k = p.getfirst();
    int best = INF_DIST;

    while (k >= 0)
    {
        int cur = 0;
        int prev = 0; // стартуем из города 0
        bool bad = false;

        // проход по маршруту 0 -> perm[0] -> ... -> perm[n-2] -> 0
        for (int i = 0; i < p.n; ++i)
        {
            int to = p.ntx(i) + 1; // города 1..n-1
            int d = dist[prev * n + to];
            if (d >= INF_DIST) { bad = true; break; }
            cur += d;
            prev = to;
        }
        if (!bad)
        {
            int d = dist[prev * n + 0];
            if (d >= INF_DIST) bad = true;
            else cur += d;
        }

        if (!bad && cur < best)
        {
            best = cur;
            bestRoute[0] = 0;
            for (int i = 0; i < p.n; ++i)
                bestRoute[i + 1] = p.ntx(i) + 1;
            bestRoute[n] = 0; // возврат
        }

        k = p.getnext();
    }

    return best;
}
