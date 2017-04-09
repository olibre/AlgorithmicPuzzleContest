// Copyright (c) 2017 olibre <olibre@Lmap.org>
//
// This file is licensed under the "Fair License":
//     Usage of the works is permitted provided
//     that this instrument is retained with the works,
//     so that any entity that uses the works
//     is notified of this instrument.
//     DISCLAIMER: THE WORKS ARE WITHOUT WARRANTY.
//
// Possible French translation:
//     Les oeuvres peuvent etre reutilisees
//     a condition d'etre accompagnees du texte de cette licence,
//     afin que tout utilisateur en soit informe'.
//     AVERTISSEMENT : LES OEUVRES N'ONT AUCUNE GARANTIE.
//
// Extract of the GOOGLE CODE JAM TERMS AND CONDITIONS
// accepted by the author (olibre) in order to participate to the contest:
//     8.  Ownership; Rights in Your Submissions; Privacy.
//     8.3 License to Submissions.
//     For any submission you make to the Contest,
//     you grant Google a non-exclusive, worldwide, perpetual, irrevocable,
//     free license (with the right to sublicense) to reproduce,
//     prepare derivative works of, distribute, publicly perform,
//     publicly display, and otherwise use such submission for the purpose
//     of administering and promoting the Contest.
//     Your submitted source code may be made available for anyone
//     to view on the Internet and download and use at the end of the Contest.

#include <iostream>
#include <stdint.h> // uint64_t
#include <string>
#include <cassert>
#include <limits>
#include <iomanip>
#include <vector>
#include <cmath>
#include <iterator> // std::end()
#include <deque>
#include <cstdlib>
#include <map>
#include <tuple>

// Inspired from function Copyright nulleight 2016 CC BY-SA 3.0
// http://stackoverflow.com/a/39944307/938111
constexpr uint64_t nextPowerOfTwo64 (uint64_t x)
{
    return 1ULL << (sizeof(uint64_t) * 8 - __builtin_clzll(x));
}

struct MinMax {
    uint64_t max = 0;
    uint64_t min = 0;
};

constexpr MinMax process (uint64_t n, uint64_t k)
{
    MinMax result;
    uint64_t nextPow2fromK = nextPowerOfTwo64(k);

    result.min = n -  k;
    result.max = n - (k&1);

    // weird trick
    if (k&1 && k!=3) result.max += ((result.min % nextPow2fromK)&1);

//  std::cout <<" nextPow2fromK="<< nextPow2fromK;
//  std::cout <<" isKodd="<< (k&1);
//  std::cout <<" reste="<< (result.min % nextPow2fromK);

    result.min /= nextPow2fromK;
    result.max /= nextPow2fromK;
    return result;
}

void test (uint64_t n, uint64_t k, uint64_t max=0, uint64_t min=0)
{
    std::cout << n <<' '<< k <<" =>";
    auto r = process (n, k);
    std::cout <<' '<< r.max; if (r.max!=max)  std::cout <<'('<< max <<')';
    std::cout <<' '<< r.min; if (r.min!=min)  std::cout <<'('<< min <<')';
    std::cout << '\n';
}

int testall()
{
    test (1, 1);
    test (2, 1, 1);
    test (2, 2);
    test (3, 2);
    test (4, 2, 1);
    test (5, 2, 1);
    test (6, 2, 1, 1);
    test (3, 1, 1, 1);
    test (4, 1, 2, 1);
    test (5, 1, 2, 2);
    test (6, 1, 3, 2);
    test (7, 1, 3, 3);
    test (7, 2, 1, 1);
    test (7, 3, 1, 1);
    test (7, 4);
    test (7, 5);
    test (7, 6);
    test (7, 7);
    test (8,	2,	2,	1);
    test (9,	2,	2,	1);
    test (10,	2,	2,	2);
    test (11,	2,	2,	2);
    test (12,	2,	3,	2);
    test (13,	2,	3,	2);
    test (14,	2,	3,	3);
    test (15,	2,	3,	3);
    test (16,	2,	4,	3);
    test (34,	2,	8,	8);
    test (4,	3,	0,	0);
    test (5,	3,	1,	0);
    test (6,	3,	1,	0);
    test (7,	3,	1,	1);
    test (8,	3,	1,	1);
    test (9,	3,	2,	1);
    test (10,	3,	2,	1);
    test (11,	3,	2,	2);
    test (12,	3,	2,	2);
    test (13,	3,	3,	2);
    test (14,	3,	3,	2);
    test (15,	3,	3,	3);
    test (16,	3,	3,	3);
    test (34,	3,	8,	7);
    test (4,	4,	0,	0);
    test (5,	4,	0,	0);
    test (6,	4,	0,	0);
    test (7,	4,	0,	0);
    test (8,	4,	1,	0);
    test (9,	4,	1,	0);
    test (10,	4,	1,	0);
    test (11,	4,	1,	0);
    test (12,	4,	1,	1);
    test (13,	4,	1,	1);
    test (14,	4,	1,	1);
    test (15,	4,	1,	1);
    test (16,	4,	2,	1);
    test (17,	4,	2,	1);
    test (18,	4,	2,	1);
    test (19,	4,	2,	1);
    test (20,	4,	2,	2);
    test (21,	4,	2,	2);
    test (22,	4,	2,	2);
    test (23,	4,	2,	2);
    test (24,	4,	3,	2);
    test (25,	4,	3,	2);
    test (26,	4,	3,	2);
    test (27,	4,	3,	2);
    test (28,	4,	3,	3);
    test (29,	4,	3,	3);
    test (30,	4,	3,	3);
    test (31,	4,	3,	3);
    test (32,	4,	4,	3);
    test (33,	4,	4,	3);
    test (34,	4,	4,	3);
    test (1000,  999);
    test (1000, 1000);
    test (1000, 1, 500, 499);
    test (1001, 1, 500, 500);
    test (1002, 1, 501, 500);
    test (1000'000'0,  999'000'0);
    test (1000'000'0, 1000'000'0);
    test (1000'000'0, 1, 500'000'0, 500'000'0-1);
    test (1000'000'1, 1, 500'000'0, 500'000'0);
    test (1000'000'2, 1, 500'000'1, 500'000'0);
    test (123456789012345678, 1, 123456789012345678/2, 123456789012345678/2-1);
    test (123456789012345679, 1, 123456789012345679/2, 123456789012345679/2);
    test (123456789012345678, 123456789012345678/2+123456789012345678/4-123456789012345678/7);
    test (123456789012345678, 123456789012345678-1);
    test (123456789012345678, 123456789012345678);
    return 0;
}

int main (int, char**)
{    
    //return testall();

    int t;
    std::cin >> t;

    for (int c=1; c<=t; ++c)
    {
        std::cout <<"Case #"<< c <<": ";

        uint64_t    n;
        std::cin >> n;

        uint64_t    k;
        std::cin >> k;

        MinMax result = process (n, k);

        std::cout << result.max <<' '<< result.min <<'\n';
    }
}
