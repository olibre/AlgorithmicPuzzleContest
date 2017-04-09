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



void process (std::string& number)
{
    char next = '9';
    for (auto it = number.rbegin(); it != number.rend(); ++it) {
        if (*it > next)
        {
            *it = char((*it) - 1);
            for (auto jt = it.base(); jt < number.end(); ++jt)
                *jt = '9';
        }
        next = *it;
    }
}

void test (const std::string& number)
{
    std::string n = number;
    std::cout << n <<'\n';
    process (n);
    std::cout << n <<'\n';
}

int testall()
{
    test("1654392");
    test("123");
    test("123456780912034506789012304560789");
    test("111111111");
    test("132");
    test("7");
    test("1");
    test("111111111111111111111111111111111111111111111111111111111111111111111110");
    return 0;
}

int main (int, char**)
{
    //return testall();

    int t;
    std::cin >> t;

    for (int i=1; i<=t; ++i)
    {
        std::cout <<"Case #"<< i <<": ";

        std::string number;
        std::cin >> number;

        process (number);

        if (number[0] == '0')
            std::cout << number.data()+1;
        else
            std::cout << number;

        std::cout <<'\n';
    }
}
