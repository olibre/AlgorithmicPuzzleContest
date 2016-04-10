// Copyright (c) 2016 olibre <olibre@Lmap.org>
//
// Fair License:   Usage of the works is permitted provided
//                 that this instrument is retained with the works,
//                 so that any entity that uses the works
//                 is notified of this instrument.
//                 DISCLAIMER: THE WORKS ARE WITHOUT WARRANTY.
//
// Possible French Translation:
//
//                 Les oeuvres peuvent etre reutilisees
//                 a condition d'etre accompagnees du texte de cette licence,
//                 afin que tout utilisateur en soit informe'.
//                 AVERTISSEMENT : LES OEUVRES N'ONT AUCUNE GARANTIE.
//
// Extract of the GOOGLE CODE JAM TERMS AND CONDITIONS
// accepted by olibre in order to participate to the contest:
//
// 8. Ownership; Rights in Your Submissions; Privacy.
//  8.3 License to Submissions.
//      For any submission you make to the Contest,
//      you grant Google a non-exclusive, worldwide, perpetual, irrevocable,
//      free license (with the right to sublicense) to reproduce,
//      prepare derivative works of, distribute, publicly perform,
//      publicly display, and otherwise use such submission for the purpose
//      of administering and promoting the Contest.
//      Your submitted source code may be made available for anyone
//      to view on the Internet and download and use at the end of the Contest.

#include <iostream>
#include <stdint.h> // uint_fast64_t
#include <string>
#include <cassert>
#include <limits>

using namespace std;

constexpr uint_fast8_t count (const bool (&ten_digits)[10])
{
    int c = 0;
    for (auto d: ten_digits)
        c += d ? 1 : 0;
    return c;
}

void sheep (uint_fast64_t n)
{
    bool ten_digits[10] = {0};
    auto last_count = count(ten_digits);

    for (uint_fast64_t m=1; ; ++m)
    {
        if (m > 10000000000000000000ULL)
        {
            std::cout << "INSOMNIA";
            return;
        }

        for (uint_fast64_t xxxx = m * n; xxxx > 0; xxxx /= 10)
        {
            uint_fast8_t digit = xxxx % 10;

            if (ten_digits[digit] == false)
            {
                auto c = count(ten_digits);
                if (c == 9)
                {
                    std::cout << (m * n);
                    return;
                }

                ten_digits[digit] = true;
            }
        }

        if ((m % 100) == 0)
        {
            auto c = count(ten_digits);
            if ( c == last_count )
            {
                std::cout << "INSOMNIA";
                return;
            }
            last_count = c;
        }
    }
}

int main()
{
    int t;
    std::cin >> t;
    assert(1 <= t);
    assert(     t <= 100);

    for (int i=1; i<=t; ++i)
    {
        std::cout <<"Case #"<< i <<": ";

        uint_fast64_t n;
        std::cin >> n;
//      assert(0 <= n);
        assert(     n <= 1'000'000);

        sheep (n);

        std::cout << std::endl;
    }
}

