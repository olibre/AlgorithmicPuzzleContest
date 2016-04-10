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


/// return 0       => The number is *probably* prime
/// return divisor => The number is *NOT* prime
constexpr int divisor (__uint128_t number) noexcept
{
    if (number      <  0) number = -number;  // support negative numbers
    if (number      <  2) return  1;         // 0,  1       => not prime
    if (number %  2 == 0) return  2;         // 4,  6,  8.. => not prime
    if (number %  3 == 0) return  3;         // 6,  9, 12.. => not prime
    if (number %  5 == 0) return  5;         // 5, 10, 15.. => not prime
    if (number %  7 == 0) return  7;         // 5, 10, 15.. => not prime
#define SEARCH_MORE_NON_PRIME_NUMBERS_
#ifdef  SEARCH_MORE_NON_PRIME_NUMBERS_
    if (number % 11 == 0) return 11;
    if (number % 13 == 0) return 13;
    if (number % 17 == 0) return 17;
    if (number % 19 == 0) return 19;
    if (number % 23 == 0) return 23;
    if (number % 29 == 0) return 29;
    if (number % 31 == 0) return 31;
    if (number % 37 == 0) return 37;
    if (number % 41 == 0) return 41;
    if (number % 53 == 0) return 53;
    if (number % 59 == 0) return 59;
    if (number % 61 == 0) return 61;
    if (number % 67 == 0) return 67;
    if (number % 71 == 0) return 71;
    if (number % 73 == 0) return 73;
    if (number % 79 == 0) return 79;
    if (number % 83 == 0) return 83;
    if (number % 89 == 0) return 89;
    if (number % 97 == 0) return 97;
#endif
    return 0; // *probably* prime
}

/// Convert base2 -> baseX
constexpr auto convert_into_baseX (size_t baseX, uint_fast64_t value_base2)
{
    __uint128_t value_baseX = 0;
    __uint128_t multiplier  = 1;

    for (auto x = value_base2; x; x>>=1, multiplier*=baseX)
        if (x&1) value_baseX += multiplier;

    return value_baseX;
}

/// Convert base2 -> baseX
constexpr auto convert_digitscount_to_base2 (int digitscount)
{
    uint_fast64_t value_base2 = std::pow(2,digitscount-1) + 1;
    return value_base2;
}

struct Jamcoin
{
    static constexpr size_t NUMBER_OF_DIVISORS = 9;

    constexpr Jamcoin () {}

    constexpr Jamcoin (uint_fast64_t val_b2)
    {
        set (val_b2);
    }

    constexpr auto get() const noexcept
    {
        return value_base2;
    }

    constexpr auto getDivisor (size_t index) const noexcept
    {
        return divisors[index];
    }

    /// If cannot be sure value if legitimate
    /// => Set a legitamte one (search from given value)
    constexpr void set (uint_fast64_t val_b2) noexcept
    {
        //FIXME assert (val_b2 % 2); //only odd numbers
        value_base2 = val_b2;
        while (! compute_divisors())
            value_base2 += 2; // try next one until all divisors are computed
    }

    constexpr void go_to_another_legitimate_jamcoin (uint_fast64_t val_b2) noexcept
    {
        set (val_b2 + 2);
    }

private:

    /// return true  if legitimate (all divisors could be computed)
    /// return false if probably not legitimate
    constexpr bool compute_divisors() noexcept
    {
        for (size_t index=0; index < NUMBER_OF_DIVISORS; ++index)
            if (! compute_divisor(index))
                return false;
        return true;
    }

    /// return true  if legitimate (divisor could be computed)
    /// return false if probably not legitimate
    constexpr bool compute_divisor (size_t index) noexcept
    {
        // index 0 => base 2 (index 8 => base 10)
        auto value_baseX = convert_into_baseX (index+2, value_base2);
        divisors[index] = divisor (value_baseX);
        return divisors[index];
    }

    uint_fast64_t   value_base2                  =  0;
    int             divisors[NUMBER_OF_DIVISORS] = {0};
};

template <size_t J>
struct JamcoinCollection
{
    /// J distinct jamcoins of length N
    constexpr JamcoinCollection (int n) : collection{Jamcoin( convert_digitscount_to_base2(n) )}
    {
        for (size_t i=1; i<J; ++i)
            collection[i].go_to_another_legitimate_jamcoin (collection[i-1].get());
    }

    static constexpr size_t NUMBER_OF_JAMCOINS = J;
    Jamcoin collection[J];
};

template <>
struct JamcoinCollection<0>
{
    /// It is guaranteed that at least J distinct jamcoins of length N exist.
    JamcoinCollection (int n, size_t j)
        : collection(j)
        , NUMBER_OF_JAMCOINS(j)
    {
        auto value_base2 = convert_digitscount_to_base2(n);
        collection[0].set (value_base2);
        for (size_t i=1; i<NUMBER_OF_JAMCOINS; ++i)
            collection[i].go_to_another_legitimate_jamcoin (collection[i-1].get());
    }

    size_t NUMBER_OF_JAMCOINS;
    std::vector<Jamcoin> collection;
};

// This below function is a copy from http://stackoverflow.com/a/25115163/938111
// Copyright (c) 2014-2015 James Kanze, Paebbels, 0x499602D2, Charlestone
// CC-BY-SA 3.0
std::ostream& operator<<( std::ostream& dest, __uint128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        char buffer[ 40 ]; // 128-bits integer requires 39 digits in base 10
        char* d = std::end( buffer );
        do {
            -- d;
            *d = "0123456789"[ value % 10 ];
            value /= 10;
        } while ( value != 0 );
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}

std::ostream& operator<< (std::ostream& os, const Jamcoin& obj)
{
    std::string str_base2;
    auto  value_base2 = obj.get();
    for (auto x = value_base2; x; x>>=1)
        str_base2.insert (0,1, (x&1 ? '1' : '0') );
    os << str_base2;
    for (size_t i = 0; i < obj.NUMBER_OF_DIVISORS; ++i)
    {
//      os << " | ";
//      size_t base = i + 2;
//      __uint128_t value_baseX=0;
//      for (__uint128_t x = value_base2, m=1; x; x>>=1, m*=base)
//          value_baseX += m * (x&1);
//      os << value_baseX;
        os << ' ' << obj.getDivisor(i);
//      os << ' ' << value_baseX % obj.getDivisor(i);
//      assert( value_baseX % obj.getDivisor(i) == 0 );
    }
    return os;
}

template <size_t J>
std::ostream& operator<< (std::ostream& os, const JamcoinCollection<J>& obj)
{
    for (size_t i = 0; i < obj.NUMBER_OF_JAMCOINS; ++i)
        os << obj.collection[i] << std::endl;
    return os;
}

int main()
{
//  constexpr JamcoinCollection<1>      tiny(3);
//  std::cout << "TINY" "\n";
//  std::cout << tiny;
//
//  constexpr JamcoinCollection<3>      sample(6);
//  std::cout << "SAMPLE" "\n";
//  std::cout << sample;
//
    constexpr JamcoinCollection<50>     small(16);
//  std::cout << "SMALL" "\n";
//  std::cout << small;
//
    constexpr JamcoinCollection<500>    big  (32);
//  std::cout << "BIG" "\n";
//  std::cout << big;

    int t;  std::cin >> t;
    assert (t >= 0  );
    assert (t <= 100);

    for (int i=1; i<=t; ++i)
    {
        std::cout <<"Case #"<< i <<':'<< std::endl;

        int    n;  std::cin >> n;
        size_t j;  std::cin >> j;

        if (n==16 && j==50)
        {
            std::cout << small;
        }
        else if (n==32 && j==500)
        {
            std::cout << big;
        }
        else
        {
            const JamcoinCollection<0> jamcoins (n, j);
            std::cout << jamcoins;
        }

        std::cout << std::endl;
    }
}
