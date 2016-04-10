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
#include <iomanip>

using namespace std;

int smallest_number_of_times_to_get_all_pancakes_happy_side_up (const std::string& stack)
{
    int smallest_number_of_flips = 0;
    char last = '+';
    for (int i = stack.size()-1; i >=0; --i )
    {
        char c = stack[i];
        assert (c=='-' || c=='+');
        if (c != last)
        {
            last = c;
            smallest_number_of_flips++;
        }
    }
    return smallest_number_of_flips;

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

        std::string stack_of_pancakes;
        std::cin >> stack_of_pancakes;

        auto n = smallest_number_of_times_to_get_all_pancakes_happy_side_up (stack_of_pancakes);

        std::cout << n << std::endl;
    }
}
