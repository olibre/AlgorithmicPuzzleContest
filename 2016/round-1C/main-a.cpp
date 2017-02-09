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



std::string process (std::vector<int>&& v)
{
    std::string result;

    for(;;)
    {
        result += ' ';

        std::multimap<int,char> m;
        for (size_t i = 0; i < v.size(); ++i)
            if(v[i])
                m.insert( {v[i], char('A'+i)} );

        if (m.empty())
            return result;

        auto b = m.end();
        b--;

        int  nb    = b->first;
        char party = b->second;

        result += party;
        assert(v[party - 'A'] > 0);
        v[party - 'A']--; nb--;

        auto b2 = b;
        b2--;

        int  nb2    = b2->first;
        char party2 = b2->second;

        assert(nb2 > 0);

        if (nb > nb2)
        {
            result += party;
            assert(v[party - 'A'] > 0);
            v[party - 'A']--;
        }
        else
        {
            if (nb==0 && nb2==1 && m.size() == 3)
                continue;

            result += party2;
            assert(v[party2 - 'A'] > 0);
            v[party2 - 'A']--;
        }

    }

    return result;
}

void verify (std::vector<int>&& v)
{
    for (size_t i = 0; i < v.size(); ++i)
        std::cout <<char('A'+i)<<'='<< v[i] <<' ';
    auto s = process (std::move(v));
    std::cout << s <<std::endl;
}

int test()
{
    verify( std::move(std::vector<int>{3,2,2} ));
    verify( std::move(std::vector<int>{2,2}   ));
    verify( std::move(std::vector<int>{1,1,2} ));
    verify( std::move(std::vector<int>{2,3,1} ));
    return 0;
}

int main (int argc, char**)
{
    //argc = 3; // Debug
    if (argc > 2)
        return test();

    int t;
    std::cin >> t;
    assert (t >= 0  );
    assert (t <= 800);

    for (int i=1; i<=t; ++i)
    {
        std::cout <<"Case #"<< i <<':';

        size_t n;
        std::cin >> n;
        assert(n <= 26 );

        std::vector<int> v;
        for (size_t m=0; m<n; ++m)
        {
            int in;
            std::cin >> in;
            v.push_back(in);
        }
        assert(n == v.size());

        auto result = process (std::move(v));

        std::cout << result <<'\n';
    }
}
