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
#include <map>
#include <cassert>

using namespace std;

std::string process (const std::string& word)
{
    int letter['Z']{};
    int result['9']{};

    for (char e: word)
    {
        assert (e >= 'A');
        assert (e <  'Z');

        switch (e)
        {
        case 'Z':
            ++result['0'];
            --letter['O'];
            break;

        case 'W':
            ++result['2'];
            --letter['O'];
            break;

        case 'U':
            ++result['4'];
            --letter['F'];
            --letter['O'];
            break;

        case 'X':
            ++result['6'];
            --letter['S'];
            break;

        case 'G':
            ++result['8'];
            --letter['H'];
            break;

        default:
            ++letter[e];
        }
    }

    result['3'] += letter['H'];
    result['5'] += letter['F'];
    result['7'] += letter['S'];
    letter['N'] -= letter['S'];
    result['1'] += letter['O'];
    letter['N'] -= letter['O'];

    std::string phone_number;

    for (char i = '0'; i < '8'; ++i)
    {
        if (result[i])
        {
            phone_number += std::string (result[i], i);
        }
    }

    // rest of letters 'N' => NINE
    int count = letter['N'];
    if (count)
    {
        assert(count%2 == 0);
        phone_number += std::string (count/2, '9');
    }

    return phone_number;
}

bool verify (const std::string & in,
             const std::string & expected)
{
    std::string out = process (in);

    if (out != expected) {
        std::cout << in       <<"\t" "Input"          "\n"
                  << expected <<"\t" "Expected ouput" "\n"
                  << out      <<"\t" "Actual   ouput" "\n";
        return false;
    }

    return true;
}

int test()
{
    int count = 0; // number of failed tests

    count += ! verify(""                    ,""      );
    count += ! verify("ETHER"               ,"3"     );
    count += ! verify("ETTHEOWR"            ,"23"    );
    count += ! verify("NNNNIEIE"            ,"99"    );
    count += ! verify("NNETTHEOOWRNNNIEEIE" ,"12399" );

    return count;
}

int main (int argc, char**) // argv)  // not used
{
    //argc = 3;
    if (argc > 2)
        return test();

    int t;  std::cin >> t;
    assert (t >= 0  );
    assert (t <= 100);

    for (int i=1; i<=t; ++i)
    {
        std::cout <<"Case #"<< i <<": ";

        std::string word;
        std::cin >> word;

        std::string phone_number = process (word);

        std::cout << phone_number;

        std::cout << std::endl;
    }
}
