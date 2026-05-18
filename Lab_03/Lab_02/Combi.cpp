// Combi.cpp
#include "Combi.h"
#include <algorithm>

namespace combi
{
    // subset 
    subset::subset(short n)
    {
        this->n = n;
        this->sset = new short[n];
        this->reset();
    }

    void subset::reset()
    {
        this->sn = 0;
        this->mask = 0;
    }

    short subset::getfirst()
    {
        __int64 buf = this->mask;
        this->sn = 0;
        for (short i = 0; i < n; i++)
        {
            if (buf & 0x1) this->sset[this->sn++] = i;
            buf >>= 1;
        }
        return this->sn;
    }

    short subset::getnext()
    {
        int rc = -1;
        this->sn = 0;
        if (++this->mask < this->count()) rc = getfirst();
        return rc;
    }

    short subset::ntx(short i) { return this->sset[i]; }

    unsigned __int64 subset::count()
    {
        return (unsigned __int64)(1ULL << this->n);
    }

    // xcombination 
    xcombination::xcombination(short n, short m)
    {
        this->n = n;
        this->m = m;
        this->sset = new short[m + 2];
        this->reset();
    }

    void xcombination::reset()
    {
        this->nc = 0;
        for (int i = 0; i < this->m; i++) this->sset[i] = i;
        this->sset[m] = this->n;
        this->sset[m + 1] = 0;
    }

    short xcombination::getfirst()
    {
        return (this->n >= this->m) ? this->m : -1;
    }

    short xcombination::getnext()
    {
        short rc = getfirst();
        if (rc > 0)
        {
            short j;
            for (j = 0; this->sset[j] + 1 == this->sset[j + 1]; ++j)
                this->sset[j] = j;
            if (j >= this->m) rc = -1;
            else
            {
                this->sset[j]++;
                this->nc++;
            }
        }
        return rc;
    }

    short xcombination::ntx(short i) { return this->sset[i]; }

    static unsigned __int64 fact(unsigned __int64 x)
    {
        return (x == 0) ? 1 : (x * fact(x - 1));
    }

    unsigned __int64 xcombination::count() const
    {
        return (this->n >= this->m)
            ? fact(this->n) / (fact(this->n - this->m) * fact(this->m))
            : 0;
    }

    // permutation 
#define NINF ((short)0x8000)

    permutation::permutation(short n)
    {
        this->n = n;
        this->sset = new short[n];
        this->dart = new bool[n];
        this->reset();
    }

    void permutation::reset()
    {
        this->getfirst();
    }

    __int64 permutation::getfirst()
    {
        this->np = 0;
        for (int i = 0; i < this->n; i++)
        {
            this->sset[i] = i;
            this->dart[i] = L;
        }
        return (this->n > 0) ? this->np : -1;
    }

    __int64 permutation::getnext()
    {
        __int64 rc = -1;
        short maxm = NINF, idx = -1;

        for (int i = 0; i < this->n; i++)
        {
            if (i > 0 &&
                this->dart[i] == L &&
                this->sset[i] > this->sset[i - 1] &&
                maxm < this->sset[i]) maxm = this->sset[idx = i];

            if (i < (this->n - 1) &&
                this->dart[i] == R &&
                this->sset[i] > this->sset[i + 1] &&
                maxm < this->sset[i]) maxm = this->sset[idx = i];
        }

        if (idx >= 0)
        {
            std::swap(this->sset[idx],
                this->sset[idx + (this->dart[idx] == L ? -1 : 1)]);
            std::swap(this->dart[idx],
                this->dart[idx + (this->dart[idx] == L ? -1 : 1)]);

            for (int i = 0; i < this->n; i++)
                if (this->sset[i] > maxm) this->dart[i] = !this->dart[i];

            rc = ++this->np;
        }
        return rc;
    }

    short permutation::ntx(short i) { return this->sset[i]; }

    unsigned __int64 permutation::count() const
    {
        return fact(this->n);
    }

    // arrangement (размещения без повторений)
    arrangement::arrangement(short n, short m)
    {
        this->n = n;
        this->m = m;
        this->sset = new short[m];
        this->used = new bool[n];
        this->reset();
    }

    void arrangement::reset()
    {
        for (int i = 0; i < n; ++i) used[i] = false;
        first = true;
    }

    short arrangement::getfirst()
    {
        if (n < m || m <= 0) return -1;
        for (int i = 0; i < n; ++i) used[i] = false;
        for (int i = 0; i < m; ++i)
        {
            sset[i] = i;
            used[i] = true;
        }
        first = false;
        return m;
    }

    // простой лексикографический перебор размещений:
    // перебираем как m-значное число в системе "n без повторений"
    short arrangement::getnext()
    {
        if (first) return getfirst();
        if (n < m || m <= 0) return -1;

        // ищем позицию справа, которую можно увеличить
        for (int pos = m - 1; pos >= 0; --pos)
        {
            used[sset[pos]] = false;
            for (int val = sset[pos] + 1; val < n; ++val)
            {
                if (!used[val])
                {
                    sset[pos] = val;
                    used[val] = true;
                    // заполнить справа минимально возможными
                    int idx = pos + 1;
                    for (int v = 0; v < n && idx < m; ++v)
                    {
                        if (!used[v])
                        {
                            sset[idx++] = v;
                            used[v] = true;
                        }
                    }
                    return m;
                }
            }
        }
        return -1;
    }

    short arrangement::ntx(short i) { return sset[i]; }

    unsigned __int64 arrangement::count() const
    {
        if (m > n || m < 0) return 0;
        unsigned __int64 res = 1;
        for (int i = 0; i < m; ++i)
            res *= (n - i);
        return res;
    }
}
