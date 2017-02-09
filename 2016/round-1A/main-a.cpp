// Copyright (c) 2016 olibre <olibre@Lmap.org>
//
// This file is licensed under the 'Fair License'
// except the function `ostream& operator<<(ostream&,__uint128_t)`
// that is a copy from http://stackoverflow.com/a/25115163/938111
//
// Fair License:   Usage of the works is permitted provided
//                 that this instrument is retained with the works,
//                 so that any entity that uses the works
//                 is notified of this instrument.
//                 DISCLAIMER: THE WORKS ARE WITHOUT WARRANTY.
//
// Possible French translation:
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
#include <iomanip>
#include <vector>
#include <cmath>
#include <iterator> // std::end()

using namespace std;

void process (const std::string& word)
{
    assert( word.size() >= 1 );

    std::string last;

    last.push_back( word[0] );
    for (size_t i=1; i<word.size(); ++i)
    {
        if(word[i] < last[0])
            last.push_back(word[i]);
        else
            last.insert(0, 1, word[i]);
    }

    std::cout << last;
}


int main()
{
    //process ("CAB");
    //return 0;


    int t;  std::cin >> t;
    assert (t >= 0  );
    assert (t <= 100);

    for (int i=1; i<=t; ++i)
    {
        std::cout <<"Case #"<< i <<": ";

        std::string word;
        std::cin >> word;

        process (word);

        std::cout << std::endl;
    }
}
