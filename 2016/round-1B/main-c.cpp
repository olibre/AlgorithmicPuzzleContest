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


using namespace std;

bool process (size_t n, const vector< vector<int>* >& v)
{
    deque< vector<int>* > lines;
    deque< vector<int>* > rows;

    assert(!v.empty());
    lines.push_back(v[0]);

    for (size_t i=1; i<v.size(); ++i)
    {
        vector<int>* paper = v[i];
        assert(paper);
        assert(paper->size() == n);

        bool increasing = true;

        if (lines.size() < n)
        {
            for (size_t j=0; j<n; ++j)
            {
                if (paper->at(j) <= lines.back()->at(j))
                    increasing = false;
            }
            if (increasing)
            {
                lines.push_back(paper);
                continue;
            }

            increasing = true;
            for (size_t j=0; j<n; ++j)
            {
                if (paper->at(j) >= lines.front()->at(j))
                    increasing = false;
            }
            if (increasing)
            {
                lines.push_front(paper);
                continue;
            }
        }

        if (rows.empty())
        {
            rows.push_back(paper);
            continue;
        }

        increasing = true;
        for (size_t j=0; j<n; ++j)
        {
            if (paper->at(j) <= rows.back()->at(j))
                increasing = false;
        }
        if (increasing)
        {
            rows.push_back(paper);
            continue;
        }

        increasing = true;
        for (size_t j=0; j<n; ++j)
        {
            if (paper->at(j) >= rows.front()->at(j))
                increasing = false;
        }
        if (increasing)
        {
            rows.push_front(paper);
            continue;
        }

        return false;
    }

    assert(lines.size() != rows.size());
    if( lines.size() > rows.size() )
    {
        assert(lines.size() == n);
        std::swap(lines,rows);
    }
    assert(lines.size() < rows.size());

    vector<int>* paper = rows.front();
    size_t missing = n-1;
    for (size_t j=0, i=0; j<n-1; ++j)
    {
        if(paper->at(j) != lines[i]->at(0))
        {
            missing = j;
        }
        else
        {
            for (size_t m=0; m<n; ++m)
            {
                if (rows[m]->at(j) != lines[i]->at(m))
                {
                    return false;
                }
            }
            i++;
        }
    }

    for (size_t i=0; i<n; ++i)
    {
        vector<int>* paper = rows[i];
        std::cout <<' '<< paper->at(missing);
    }
    return true;
}

void wind (size_t n, vector< vector<int>* >& v)
{
    for(;;)
    {
        size_t i = rand() % v.size();
        size_t j = rand() % v.size();
        if( i == j )
            continue;

        if (process (n, v))
            return;

        vector<int>* paper = v[i];
        v[i] = v[j];
        v[j] = paper;
    }
}


void print_missing_paper (size_t n, const std::multimap< int, vector<int>* >& mm)
{
    vector< vector<int>* > rows;
    vector< vector<int>* > lines;

    bool insert_to_rows = true;
    for (auto &e: mm)
    {
        if (insert_to_rows)
            rows.push_back(e.second);
        else
            lines.push_back(e.second);
        insert_to_rows = ! insert_to_rows;
    }
    assert(rows.size() == lines.size()+1);

    vector<int>* paper = rows.front();
    size_t missing = 0;
    for (; missing<n-1; ++missing)
    {
        if ( (*paper)[missing] != (*lines[missing])[0] )
        {
            break;
        }
    }

    for (size_t i=0; i<n; ++i)
    {
        vector<int>* paper = rows[i];
        std::cout <<' '<< (*paper)[missing];
    }
}



int main()
{
    /*
    vector<int> paper[5] = {{1,2,3}, {2,3,5}, {3,5,6}, {2,3,4}, {1,2,3}};
    vector< vector<int>* > v = {&paper[0], &paper[1], &paper[2], &paper[3], &paper[4]};
    doit (3,v);
    return 0;
*/
    int t;  std::cin >> t;
    assert (t >= 0  );
    assert (t <= 100);

    for (int i=1; i<=t; ++i)
    {
        std::cout <<"Case #"<< i <<':';

        size_t      n;
        std::cin >> n;
        assert(n >= 1);

        size_t k = n + (n-1);

#ifdef BRUTE_DE_FORCE
        vector< vector<int>* > v(k);
        for (size_t i=0; i<k; ++i)
        {
            vector<int>* paper = new vector<int>();
            for (size_t j=0; j<n; ++j)
            {
                int h;
                std::cin >>   h;
                paper->push_back(h);
            }
            v[i] = paper;
        }
        wind (n,v);
#elif SUM_PAPER_NUMBERS
        std::multimap< int, vector<int>* > mm;
        for (size_t i=0; i<k; ++i)
        {
            int sum = 0;
            vector<int>* paper = new vector<int>(n);
            for (size_t j=0; j<n; ++j)
            {
                int h;
                std::cin >> h;
                sum += h;
                (*paper)[j] = h;
            }
            mm.insert({sum,paper});
        }
        print_missing_paper (n,mm);
#else
        size_t count = k * n;
        std::map<int,int> occurences;
        for (size_t i=0; i<count; ++i)
        {
            int          height;
            std::cin >>  height;
            ++occurences[height];
        }
        for (auto& e: occurences)
            if (e.second % 2)
                std::cout <<' '<< e.first;
#endif
        std::cout << std::endl;
    }
}
