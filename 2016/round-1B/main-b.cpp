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


/// If there is no '?' => Nothing to do
bool nothing (const std::string& u, const std::string& v)
{
    assert(u.size() == v.size());

    for (size_t i = 0; i < u.size(); ++i)
        if (u[i] == '?' || v[i] == '?')
            return false;

    return true; // Nothing to do :-)
}

void equalize_begin (size_t n, std::string& u, std::string& v)
{
    assert(n <= u.size());
    for (size_t i = 0; i < n; ++i)
    {
        if (u[i] == '?')  if (v[i] == '?') u[i] =  v[i] = '0';
                          else             u[i] =  v[i];
        else              if (v[i] == '?') v[i] =  u[i];
        //                else      assert(u[i] == v[i]);
    }
}

bool equalize (std::string& u, std::string& v)
{
    assert(u.size() == v.size());

    for (size_t i = 0; i < u.size(); ++i)
        if (u[i] != v[i] && u[i] != '?' && v[i] != '?')
            return false;

    equalize_begin (u.size(), u, v);
    return true;
}

/// Replace u='?' by '9', and v='?' by '0'
void fill_end (size_t n, std::string& u, std::string& v)
{
    for (size_t i = n; i < u.size(); ++i)
    {
        if (u[i] == '?') if (v[i] == '?') u[i]='9', v[i]='0';
                         else             u[i]='9';
        else             if (v[i] == '?')           v[i]='0';
    }
}

/// Basic case where first left digit is same position for both
bool fill_basic (std::string& u, std::string& v)
{
    size_t i;
    for (i = 0; i < u.size(); ++i)
    {
        if (u[i] == v[i])
            continue;

        if (u[i] == '?' || v[i] == '?')
            return false;

        break;
    }

    bool greater = u[i] > v[i];
    bool retenue = false;

    if (i > 0) {
        // if  u="?8"  =>  u="08"   (u is not greater than v)
        //     v="?2"      v="12"
        if (u[i] - 5 > v[i])  greater = false,  retenue = true;
        // if  u="?2"  =>  u="02"   (u is greater than v)
        //     v="?8"      v="18"
        if (v[i] - 5 > u[i])  greater = true,  retenue = true;
    }

    if (greater)  std::swap(u,v);

    if (retenue){
        assert(u[i-1] == '?');
        assert(v[i-1] == '?');
        u[i-1] = '0';
        v[i-1] = '1';
        equalize_begin (i-1, u, v);
    } else {
        equalize_begin (i, u, v);
    }

    fill_end (i+1, u, v);

    if (greater)  std::swap(u,v);

    return true;
}

/// Manage cases like u="??8" v="202"
/// - 208 ??2 -> 208 212 (already implemented by fill_complex)
/// - 298 ??2 -> 298 302
/// - 998 ??2 -> 998 992
/// - 202 ??8 -> 202 198
/// - 002 ??8 -> 002 008
void fill_retenue (size_t n, std::string& u, std::string& v)
{
    assert(n > 0);
    assert(v[n-1] == '?');
    assert(u[n-1] == '9' || u[n-1] == '0');

    const char find_u = u[n-1];
    assert(find_u == (u[n] > v[n] ? '9' : '0'));

    // Look backward first successive '9' or '0' in u[]
    // => Go back until u[i] is not 'find_u'
    // Stop if v[i] is no more '?'
    int i;
    for (i = int(n)-1; i >= 0; --i) {
        if (u[i] == find_u && v[i] == '?')
            continue;
        break;
    }


    if (i<0 || v[i]!='?')
    {
        // Two cases:
        // - u[0] is '9' or '0' -> fill with same digit
        // - "?9998" "?9??2"    -> "09998" "09992"
        return; // => will continue with equalize_begin(n,u,v)
    }

    // Use trick 299998-300002 or 200002-199998

    assert(v[i] == '?');
    if (u[i]=='?')
    {
        if (find_u=='0') u[i]='1', v[i]='0';
        else             u[i]='0', v[i]='1';
        equalize_begin (i, u, v);
    }
    else
    {
        equalize_begin (i+1, u, v);
        assert(v[i] == u[i]);
        assert(v[i] != '?');
        assert(u[n] != '?');
        assert(v[n] != '?');

        if (find_u=='0') { if (v[i]=='0') return; --v[i]; }
        else             { if (v[i]=='9') return; ++v[i]; }
    }

    char set_v;
    if (find_u=='0') { set_v='9'; }
    else             { set_v='0'; }
    for (size_t j=i+1; j<n; ++j) {
        assert(v[j] == '?');
        v[j] = set_v;
    }
}

/// Manage cases like u="?8" v="22"
/// Cases like u="??8" v="202" are managed by sub-function fill_retenue()
bool fill_complex (std::string& u, std::string& v)
{
    size_t n;
    for (n = 0; n < u.size(); ++n)
    {
        if (u[n] == v[n])
            continue;

        if (u[n] == '?' || v[n] == '?')
            continue;

        break;
    }

    assert(n > 0);
    assert(u[n-1]=='?' || v[n-1]=='?');

    // if u[i-1] contains a single question mark but not v[i-1]
    bool qmark_u = u[n-1]=='?' && v[n-1]!='?';
    if  (qmark_u)  std::swap(u,v); // v[] becomes the string having the question mark
    assert(v[n-1] == '?');

    bool retenue = false;
    if (u[n] - 5 >  v[n])  retenue = true; // Do not increment when equal to 5
    if (v[n] - 5 >= u[n])  retenue = true;
    if (retenue)
    {
        if (u[n-1] == '?')
            return false;

        if (u[n] > v[n]) if  (u[n-1] == '9') fill_retenue(n,u,v);
                         else v[n-1] = u[n-1], ++v[n-1];
        else             if  (u[n-1] == '0') fill_retenue(n,u,v);
                         else v[n-1] = u[n-1], --v[n-1];
    }

    equalize_begin (n, u, v);

    for (size_t i=0; i<u.size(); ++i)
    {
        assert (u[i] != '?');
        assert (v[i] != '?');

        if (u[i] == v[i])
            continue;

        bool greater = u[i] > v[i];
        if  (greater) fill_end (n+1, v, u);
        else          fill_end (n+1, u, v);
        break;
    }

    if (qmark_u) std::swap(u,v); // restore

    // Assumes
    assert(u.size() == v.size());
    for (size_t i = 0; i < u.size(); ++i)
    {
        assert('0' <= u[i]); assert(u[i] <= '9');
        assert('0' <= v[i]); assert(v[i] <= '9');
    }

    return true;
}

bool attempt_in_TDD_mode_with_raffinements (std::string& u, std::string& v)
{
    if (nothing     (u,v))  return true;
    if (equalize    (u,v))  return true;
    if (fill_basic  (u,v))  return true;
    if (fill_complex(u,v))  return true;
    return false;
}

bool attempt_during_context (std::string& u, std::string& v)
{
    assert(u.size() == v.size());

    char fill_u = '0';
    char fill_v = '0';

    char next_u = '0';
    char next_v = '0';

    for (size_t i = 0; i < u.size(); ++i)
    {
        if (u[i] == '?' && v[i] == '?') continue;
        if (u[i] == '?' || v[i] == '?') break;

        if (u[i] + 5 < v[i]) fill_u = '1', next_v = '9';
        if (u[i] > 5 + v[i]) fill_v = '1', next_u = '9';

        break;
    }

    for (size_t i = 0; i < u.size(); ++i)
    {
        if (u[i] == '?')
            if (v[i] == '?')
                u[i]=fill_u, v[i]=fill_v;
            else
                if (fill_u=='0' && fill_v=='0')
                {
                    u[i] = v[i];
                    if (u[i] < v[i])
                        fill_u = next_u = '9';
                    else
                        fill_v = next_v = '9';
                }
                else
                    u[i] = fill_u;
        else if (v[i] == u[i])
                ;
        else if (fill_u=='0' && fill_v=='0')
            if (v[i] == '?')
                v[i] = u[i];
            else
                if (u[i] < v[i])
                    fill_u = '9', fill_v = '0';
                else
                    fill_v = '9', fill_u = '0';
        else
        {
            fill_u = next_u;
            fill_v = next_v;
            if (v[i] == '?')
                v[i] = next_v;
        }
    }

    return true;
}

/// Backward until pattern and apply u[i]=v[i]-1 or v[i]=u[i]+1
void retenue_minus (size_t n, std::string& u, std::string& v, bool nine)
{
    for (ssize_t i = n-1; i >= 0; --i)
    {
        if (u[i] == '?')
        {
            switch (v[i])
            {
            case '0':
                u[i] = '9';
                break;

            case '?':
                if (nine && i) {
                    u[i] = '9';
                    v[i] = '0';
                } else {
                    u[i] = '0';
                    v[i] = '1';
                    return; // Stop
                }
                break;

            default:
                u[i] = v[i];
                u[i]--;
                return; // Stop
            }
        }
        else if (v[i] == '?')
        {
            switch (u[i])
            {
            case '9':
                v[i] = '0';
                break;

            default:
                v[i] = u[i];
                v[i]++;
                return; // Stop
            }
        }
        else
        {
            assert(u[i] == v[i]);
        }
    }
}

/// Try different possibilities: u greater than v, and the inverse.
/// Use different algo to minimize one number and maximize the other.
/// Compare and select the minimal delta and minimal scores.
bool attempt_in_try_and_compare_mode (std::string& u, std::string& v)
{
    constexpr size_t NB_ALGO = 10;
    std::string uu[NB_ALGO];
    std::string vv[NB_ALGO];

    for (size_t i = 0; i < NB_ALGO; ++i) {
        uu[i] = u;
        vv[i] = v;
    }

    // Find most relevant digit
    size_t n;
    for (n = 0; n < u.size(); ++n)
    {
        if (u[n] == v[n]) continue;
        if (u[n] == '?')  continue;
        if (v[n] == '?')  continue;

        break;
    }

    // Basic fill
    equalize_begin (n,   uu[0], vv[0]); // 1?2 ??7 -> 102 107
    fill_end       (n+1, uu[0], vv[0]); // make v greater than u

    equalize_begin (n,   uu[1], vv[1]); // 1?2 ??7 -> 102 107
    fill_end       (n+1, vv[1], uu[1]); // make u greater than v

    retenue_minus  (n,   uu[2], vv[2], true);
    equalize_begin (n,   uu[2], vv[2]); // 1?2 ??7 -> 192 207
    fill_end       (n+1, uu[2], vv[2]); // make v greater than u

    // This fourth one seems unnecessary
    retenue_minus  (n,   uu[3], vv[3], true);
    equalize_begin (n,   uu[3], vv[3]); // 1?2 ??7 -> 192 207
    fill_end       (n+1, vv[3], uu[3]); // make u greater than v

    retenue_minus  (n,   vv[4], uu[4], true);
    equalize_begin (n,   uu[4], vv[4]); // 1?2 ??7 -> 102 097
    fill_end       (n+1, uu[4], vv[4]); // make v greater than u

    retenue_minus  (n,   vv[5], uu[5], true);
    equalize_begin (n,   uu[5], vv[5]); // 1?2 ??7 -> 102 097
    fill_end       (n+1, vv[5], uu[5]); // make u greater than v

    retenue_minus  (n,   uu[6], vv[6], false);
    equalize_begin (n,   uu[6], vv[6]); // 1?2 ??7 -> 102 117
    fill_end       (n+1, uu[6], vv[6]); // make v greater than u

    // This fourth one seems unnecessary
    retenue_minus  (n,   uu[7], vv[7], false);
    equalize_begin (n,   uu[7], vv[7]); // 1?2 ??7 -> 102 117
    fill_end       (n+1, vv[7], uu[7]); // make u greater than v

    retenue_minus  (n,   vv[8], uu[8], false);
    equalize_begin (n,   uu[8], vv[8]); // 1?2 ??7 -> 112 107
    fill_end       (n+1, uu[8], vv[8]); // make v greater than u

    retenue_minus  (n,   vv[9], uu[9], false);
    equalize_begin (n,   uu[9], vv[9]); // 1?2 ??7 -> 112 107
    fill_end       (n+1, vv[9], uu[9]); // make u greater than v

    __uint128_t su[NB_ALGO]{}; // numeral score
    __uint128_t sv[NB_ALGO]{};

    for (n = 0; n < u.size(); ++n)
    {
        for (size_t i = 0; i < NB_ALGO; ++i)
        {
            assert('0' <= uu[i][n]); assert(uu[i][n] <= '9');
            assert('0' <= vv[i][n]); assert(vv[i][n] <= '9');
            su[i] = 10*su[i] + uu[i][n] - '0';
            sv[i] = 10*sv[i] + vv[i][n] - '0';
        }

        int count = 1; // number of best solutions
        size_t index       =    0;
        __uint128_t min_su = su[0];
        __uint128_t min_sv = sv[0];
        __uint128_t min_delta = su[0] > sv[0] ? su[0] - sv[0] : sv[0] - su[0];

        for (size_t i = 1; i < NB_ALGO; ++i)
        {
            __uint128_t delta = su[i] > sv[i] ? su[i] - sv[i] : sv[i] - su[i];

            if (delta == min_delta && su[i] == min_su && sv[i] == min_sv)
            {
                count++;
                continue;
            }

            if ((delta <  min_delta) ||
                (delta == min_delta && su[i] <  min_su) ||
                (delta == min_delta && su[i] == min_su && sv[i] < min_sv))
            {
                count = 1;
                index = i;
                min_delta = delta;
                min_su    = su[i];
                min_sv    = sv[i];
            }
        }

        if (count == 1) // the best solution is already found => Stop
        {
            assert(uu[index].size() == u        .size());
            assert(uu[index].size() == vv[index].size());
            for (size_t j = 0; j < u.size(); ++j)
            {
                assert('0' <= uu[index][j]); assert(uu[index][j] <= '9');
                assert('0' <= vv[index][j]); assert(vv[index][j] <= '9');
            }
            u = uu[index];
            v = vv[index];
            return true;
        }
    }

    size_t      index  =    0;
    __uint128_t min_su = su[0];
    __uint128_t min_sv = sv[0];
    __uint128_t min_delta = su[0] > sv[0] ? su[0] - sv[0] : sv[0] - su[0];

    for (size_t i = 1; i < NB_ALGO; ++i)
    {
        __uint128_t delta = su[i] > sv[i] ? su[i] - sv[i] : sv[i] - su[i];
        if (delta == min_delta && su[i] == min_su && sv[i] == min_sv)
        {
            continue;
        }

        if ((delta <  min_delta) ||
                 (delta == min_delta && su[i] <  min_su) ||
                 (delta == min_delta && su[i] == min_su && sv[i] < min_sv))
        {
            assert(uu[i].size() == u    .size());
            assert(uu[i].size() == vv[i].size());
            for (size_t j = 0; j < u.size(); ++j)
            {
                assert('0' <= uu[i][j]); assert(uu[i][j] <= '9');
                assert('0' <= vv[i][j]); assert(vv[i][j] <= '9');
            }
            index     =    i;
            min_su    = su[i];
            min_sv    = sv[i];
            min_delta = delta;
        }
    }

    u = uu[index];
    v = vv[index];
    return true;
}

#define SELECT_ALGO 3
bool process_oneside (std::string& u, std::string& v)
{
#if (SELECT_ALGO == 1)
    attempt_during_context (u,v);
    return true;
#elif (SELECT_ALGO == 2)
    return attempt_in_TDD_mode_with_raffinements (u,v);
#else
    return attempt_in_try_and_compare_mode (u,v);
#endif
}

bool process (std::string& u, std::string& v)
{
    // Expects
    assert(u.size() == v.size());
    for (size_t i = 0; i < u.size(); ++i)
    {
        if (u[i] != '?') { assert('0' <= u[i]); assert(u[i] <= '9'); }
        if (v[i] != '?') { assert('0' <= v[i]); assert(v[i] <= '9'); }
    }

    std::string u_copy (u);
    std::string v_copy (v);

    if (process_oneside (u, v))
        goto succes;

    if (process_oneside (v_copy, u_copy)) // swap
    {
        u = u_copy;
        v = v_copy;
        goto succes;
    }

    return false;

succes:
    // Assumes
    assert(u.size() == v.size());
    for (size_t i = 0; i < u.size(); ++i)
    {
        assert('0' <= u[i]); assert(u[i] <= '9');
        assert('0' <= v[i]); assert(v[i] <= '9');
    }
    return true;
}

bool verify_oneside (const std::string & u_in,
                     const std::string & v_in,
                     const std::string & u_out,
                     const std::string & v_out)
{
    std::string u(u_in), v(v_in);

    bool ok = process (u, v);
    if (!ok) {
        std::cout << u_in <<' '<< v_in <<"\t" "Not yet implemented (should be "
                  << u_out<<' '<< v_out<<")" "\n";
        return false;
    }
    if (u_out != u || v_out != v) {
        std::cout << u_in <<' '<< v_in <<"\t" "Input"          "\n"
                  << u_out<<'-'<< v_out<<"\t" "Expected ouput" "\n"
                  << u    <<'-'<< v    <<"\t" "Actual   ouput" "\n";
        return false;
    }
    return true;
}

bool verify (const std::string & u_in,
             const std::string & v_in,
             const std::string & u_out,
             const std::string & v_out)
{
    bool v1 = verify_oneside (u_in, v_in, u_out, v_out);
    bool v2 = verify_oneside (v_in, u_in, v_out, u_out);
    return v1 && v2;
}

int test()
{
    int count = 0; // count failed tests

    count += ! verify("1?2"      ,"??7"      ,"102"      ,"097"      );
    count += ! verify("0??7"     ,"0?02"     ,"0007"     ,"0002"     );
    count += ! verify("0??8"     ,"0?02"     ,"0098"     ,"0102"     );
    count += ! verify("?21"      ,"??9"      ,"021"      ,"019"      );
    count += ! verify("00?7"     ,"0052"     ,"0047"     ,"0052"     );
    count += ! verify("00?8"     ,"00?2"     ,"0008"     ,"0012"     );
    count += ! verify("?5?8"     ,"?5?2"     ,"0508"     ,"0512"     );
    count += ! verify("00?2"     ,"0058"     ,"0062"     ,"0058"     );
    count += ! verify("00?2"     ,"00?8"     ,"0012"     ,"0008"     );
    count += ! verify("0?02"     ,"0??8"     ,"0102"     ,"0098"     );
    count += ! verify("?5?2"     ,"?5?8"     ,"0512"     ,"0508"     );
    count += ! verify("12"       ,"?7"       ,"12"       ,"07"       );
    count += ! verify("17"       ,"?2"       ,"17"       ,"12"       );
    count += ! verify("102"      ,"??7"      ,"102"      ,"097"      );
    count += ! verify("107"      ,"??2"      ,"107"      ,"102"      );
    count += ! verify("1?7"      ,"??2"      ,"107"      ,"102"      );
    count += ! verify("??????7"  ,"9001002"  ,"9000997"  ,"9001002"  );
    count += ! verify("??????7"  ,"90?1002"  ,"9000997"  ,"9001002"  );
    count += ! verify("??????7"  ,"90??002"  ,"8999997"  ,"9000002"  );
    count += ! verify("??????7??","90??002??","899999799","900000200");
    count += ! verify("???0??2??","90??007??","900000299","900000700");
    count += ! verify("3??0??2??","40??007??","399099299","400000700");
    count += ! verify("?9?8?7?61","1?2?3?4?1","192837461","192837461");
    count += ! verify("?9?8?7?61","1?2?3?4?1","192837461","192837461");
    count += ! verify("?89"      ,"??1"      ,"089"      ,"091"      );
    count += ! verify("?12?"     ,"?13?"     ,"0129"     ,"0130"     );
    count += ! verify("??7"      ,"?02"      ,"007"      ,"002"      );
    count += ! verify("??8"      ,"202"      ,"198"      ,"202"      );
    count += ! verify("?5"       ,"21"       ,"25"       ,"21"       );
    count += ! verify("208"      ,"202"      ,"208"      ,"202"      );
    count += ! verify("??8"      ,"002"      ,"008"      ,"002"      );
    count += ! verify("??2"      ,"208"      ,"212"      ,"208"      );
    count += ! verify("??2"      ,"298"      ,"302"      ,"298"      );
    count += ! verify("??2"      ,"998"      ,"992"      ,"998"      );
    count += ! verify("??8??8??8","202202202","198998998","202202202");
    count += ! verify("??8??8??8","002002002","008008008","002002002");
    count += ! verify("??2??2??2","208208208","212002002","208208208");
    count += ! verify("??2??2??2","298298298","302002002","298298298");
    count += ! verify("??2??2??2","998998998","992992992","998998998");
    count += ! verify("??5??8??" ,"??5202??" ,"00519899" ,"00520200" );
    count += ! verify("??5??2??" ,"??5208??" ,"00521200" ,"00520899" );
    count += ! verify("?8"       ,"21"       ,"18"       ,"21"       );
    count += ! verify("?"        ,"2"        ,"2"        ,"2"        );
    count += ! verify("?8"       ,"29"       ,"28"       ,"29"       );
    count += ! verify("?9"       ,"56"       ,"59"       ,"56"       );
    count += ! verify("?9"       ,"54"       ,"49"       ,"54"       );
    count += ! verify("?9"       ,"55"       ,"59"       ,"55"       );
    count += ! verify("99"       ,"55"       ,"99"       ,"55"       );
    count += ! verify("?7"       ,"82"       ,"77"       ,"82"       );
    count += ! verify("?7"       ,"02"       ,"07"       ,"02"       );
    count += ! verify("??7"      ,"502"      ,"497"      ,"502"      );
    count += ! verify("??7"      ,"002"      ,"007"      ,"002"      );
    count += ! verify("??????7"  ,"0000002"  ,"0000007"  ,"0000002"  );
    count += ! verify("??????2"  ,"0000007"  ,"0000002"  ,"0000007"  );
    count += ! verify("???1??7"  ,"0001002"  ,"0001007"  ,"0001002"  );
    count += ! verify("?12?"     ,"?83?"     ,"1120"     ,"0839"     );
    count += ! verify("??9?"     ,"?10?"     ,"0099"     ,"0100"     );
    count += ! verify("??1?"     ,"?90?"     ,"0910"     ,"0909"     );
    count += ! verify("??8?"     ,"?3??"     ,"0380"     ,"0380"     );
    count += ! verify("??8?"     ,"?30?"     ,"0289"     ,"0300"     );
    count += ! verify("??8?"     ,"300?"     ,"2989"     ,"3000"     );
    count += ! verify("??8?"     ,"3?0?"     ,"2989"     ,"3000"     );
    count += ! verify("?9"       ,"?1"       ,"09"       ,"11"       );
    count += ! verify("9?"       ,"1?"       ,"90"       ,"19"       );
    count += ! verify("??1"      ,"?99"      ,"101"      ,"099"      );
    count += ! verify("??1"      ,"?49"      ,"051"      ,"049"      );
    count += ! verify("??1"      ,"?89"      ,"091"      ,"089"      );
    count += ! verify("?91"      ,"??9"      ,"091"      ,"089"      );
    count += ! verify("??1"      ,"??9"      ,"011"      ,"009"      );
    count += ! verify("1?1?"     ,"1?9?"     ,"1110"     ,"1099"     );
    count += ! verify("1?1?"     ,"2?9?"     ,"1919"     ,"2090"     );
    count += ! verify("?3?1"     ,"33?8"     ,"3311"     ,"3308"     );
    count += ! verify("3??1"     ,"3??8"     ,"3011"     ,"3008"     );
    count += ! verify("?3?1"     ,"???8"     ,"0301"     ,"0298"     );
    count += ! verify("?3?5"     ,"???4"     ,"0305"     ,"0304"     );
    count += ! verify("??3?"     ,"?9?4"     ,"0934"     ,"0934"     );
    count += ! verify("??3?"     ,"?3?4"     ,"0334"     ,"0334"     );
    count += ! verify("2?3?"     ,"73?4"     ,"2939"     ,"7304"     );
    count += ! verify("4??"      ,"91?"      ,"499"      ,"910"      );
    count += ! verify("91?"      ,"4??"      ,"910"      ,"499"      );
    count += ! verify("?0?"      ,"?7?"      ,"100"      ,"079"      );
    count += ! verify("?7?"      ,"?1?"      ,"079"      ,"110"      );
    count += ! verify("?7?"      ,"?2?"      ,"070"      ,"029"      );
    count += ! verify("?8?"      ,"?2?"      ,"089"      ,"120"      );
    count += ! verify("?3?"      ,"?8?"      ,"039"      ,"080"      );
    count += ! verify("?3?"      ,"?9?"      ,"130"      ,"099"      );
    count += ! verify("1?"       ,"2?"       ,"19"       ,"20"       );
    count += ! verify("?2?"      ,"??3"      ,"023"      ,"023"      );
    count += ! verify("?"        ,"?"        ,"0"        ,"0"        );
    count += ! verify("?5"       ,"?0"       ,"05"       ,"00"       );
    count += ! verify("?5?"      ,"?0?"      ,"050"      ,"009"      );

    return count;
}


int main (int argc, char**) // argv)  // not used
{
    //argc = 3; // Debug
    if (argc > 2)
        return test();

    int t;
    std::cin >> t;
    assert (t >= 0  );
    assert (t <= 200);

    std::string coders, jammers; // scores

    for (int i=1; i<=t; ++i)
    {
        std::cout <<"Case #"<< i <<": ";

        std::cin >> coders;
        std::cin >> jammers;

        process (coders, jammers);

        std::cout << coders <<' '<< jammers <<'\n';
    }
}
