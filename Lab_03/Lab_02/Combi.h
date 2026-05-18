// Combi.h
#pragma once

namespace combi
{
    //  Генератор подмножеств 
    struct subset
    {
        short n;      // количество элементов исходного множества < 64
        short sn;     // количество элементов текущего подмножества
        short* sset;  // массив индексов текущего подмножества
        unsigned __int64 mask; // битовая маска

        subset(short n = 1);
        void reset();
        short getfirst();
        short getnext();
        short ntx(short i);
        unsigned __int64 count();
    };

    //  Генератор сочетаний  
    struct xcombination
    {
        short n;      // количество элементов исходного множества
        short m;      // количество элементов в сочетаниях
        short* sset;  // массив индексов текущего сочетания
        unsigned __int64 nc; // номер сочетания 0,...,count()-1

        xcombination(short n = 1, short m = 1);
        void reset();
        short getfirst();
        short getnext();
        short ntx(short i);
        unsigned __int64 count() const;
    };

    //  Генератор перестановок  
    struct permutation
    {
        const static bool L = true;
        const static bool R = false;

        short n;
        short* sset;
        bool* dart;
        unsigned __int64 np; // номер перестановки 0,...,count()-1

        permutation(short n = 1);
        void reset();
        __int64 getfirst();
        __int64 getnext();
        short ntx(short i);
        unsigned __int64 count() const;
    };

    //  Генератор размещений (размещения без повторений) 
    // Размещение из n по m: упорядоченный набор m различных элементов из n.
    struct arrangement
    {
        short n;      // количество элементов исходного множества
        short m;      // длина размещения
        short* sset;  // текущий массив индексов
        bool* used;   // какие элементы уже использованы
        bool first;   // флаг первого вызова

        arrangement(short n = 1, short m = 1);
        void reset();
        short getfirst();
        short getnext();
        short ntx(short i);
        unsigned __int64 count() const;
    };
}
