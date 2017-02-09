// Copyright (c) 2016 olibre <olibre@Lmap.org>
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
#include <unordered_map>



void process (const int J, const int P, const int S, const int K)
{
    int days_a = J * P * S;
    int days_b = J * P * K;
    int days = std::min(days_a, days_b);

    std::unordered_map<int,int> combinations_jp;
    std::unordered_map<int,int> combinations_ps;
    std::unordered_map<int,int> combinations_js;

    std::cout << days;

    int j=J, p=P, s=S;
    while (days > 0)
    {
        if (--j == 0)
        {
            j = J;
            if (--p == 0)
            {
                p = P;
                if (--s == 0)
                {
                    s = S;
                }
            }
        }

        if (combinations_jp[(j * 1024) + p] >= K || combinations_ps[(p * 1024) + s] >= K || combinations_js[(j * 1024) + s] >= K)
            std::cout <<'\n'<< j <<' '<< p <<' '<< s <<"\t" "SKIP";

        if (j==J && p==P && s==S)
            break;

        if (combinations_jp[(j * 1024) + p] >= K) continue; // skip
        if (combinations_ps[(p * 1024) + s] >= K) continue; // skip
        if (combinations_js[(j * 1024) + s] >= K) continue; // skip
        ++combinations_jp[(j * 1024) + p];
        ++combinations_ps[(p * 1024) + s];
        ++combinations_js[(j * 1024) + s];

        days--;
        std::cout <<'\n'<< j <<' '<< p <<' '<< s;

    }

    assert(days==0);
}


void verify (const int J, const int P, const int S, const int K)
{
    std::cout <<"JPSK= "<< J <<' '<< P <<' '<< S <<' '<< K <<" => ";
    process (J,P,S,K);
    std::cout <<'\n';
}

int test()
{
    verify (3, 3, 3,  1);
    verify (1, 2, 3,  2);
    verify (3, 3, 3,  2);
    verify (1, 3, 3,  8);
    verify (1, 1, 1, 10);
    verify (1, 1, 3,  2);
    verify (1, 2, 3,  1);
    return 0;
}

int main (int argc, char**)
{
#ifndef NDEBUG
    argc = 3; // Debug
#endif
    if (argc > 2)
        return test();

    int t;
    std::cin >> t;
    assert (t >= 0  );
    assert (t <= 800);

    std::string coders, jammers; // scores

    for (int i=1; i<=t; ++i)
    {

        int j, p, s, k;
        std::cin >> j >> p >> s >> k;

#ifndef NDEBUG
        std::cout <<"JPSK= "<< j <<' '<< p <<' '<< s <<' '<< k <<'\n';
#endif
        std::cout <<"Case #"<< i <<": ";
        process (j, p, s, k);

        std::cout << coders <<' '<< jammers <<'\n';
    }
}
