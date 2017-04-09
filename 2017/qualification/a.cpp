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



int process (std::string& pancakes, unsigned k)
{
    int count = 0;

    for(unsigned i=0; i<pancakes.size(); ++i)
    {
        if(pancakes[i] == '-')
        {
            if(i+k > pancakes.size())
                return -1;

            for (unsigned j=i; j<i+k; ++j)
                pancakes[j] = pancakes[j]=='-' ? '+' : '-';

            ++count;
        }
    }

    return count;
}

void test (const std::string& pancakes, unsigned k)
{
    std::string p = pancakes;
    std::cout << p <<' '<< k << '\n';
    auto result = process (p, k);
    std::cout << p <<' '<< result << '\n';
}

int testall()
{
    test( "---+-++-", 3 );
    test( "-+-+-+-+----+-", 3);
    test( "-+-+-+-+----+-", 2);
    test( "++++++++++", 3);
    test( "++++++++++", 80);
    test( "++++-+++++", 3);
    test( "++++-+++++", 80);
    return 0;
}

int main (int argc, char**)
{
    // Debug
    //return testall();

    int t;
    std::cin >> t;

    for (int i=1; i<=t; ++i)
    {
        std::cout <<"Case #"<< i <<": ";

        std::string pancakes;
        std::cin >> pancakes;

        unsigned    k;
        std::cin >> k;

        auto result = process( pancakes, k );

        if (result < 0 )
            std::cout << "IMPOSSIBLE\n";
        else
            std::cout << result <<'\n';
    }
}
