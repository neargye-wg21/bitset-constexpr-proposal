// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Daniil Goncharov <neargye@gmail.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <array>
#include <cstring>
#include <iterator>

#include <bitset.hpp>

#include "bitset_test_cases.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// https://github.com/llvm/llvm-project/tree/main/libcxx/test/std/utilities/template.bitset/bitset.members

template <std::size_t N>
void test_all() {
    nstd::bitset<N> v;
    v.reset();
    CHECK(v.all() == (N == 0));
    v.set();
    CHECK(v.all() == true);
    if (v.size() > 1) {
        v[N/2] = false;
        CHECK(v.all() == false);
    }
}

TEST_CASE("libcxx_members_all") {
    test_all<0>();
    test_all<1>();
    test_all<31>();
    test_all<32>();
    test_all<33>();
    test_all<63>();
    test_all<64>();
    test_all<65>();
    test_all<1000>();
}

template <std::size_t N>
void test_any() {
    nstd::bitset<N> v;
    v.reset();
    CHECK(v.any() == false);
    v.set();
    CHECK(v.any() == (N != 0));
    if (v.size() > 1) {
        v[N/2] = false;
        CHECK(v.any() == true);
        v.reset();
        v[N/2] = true;
        CHECK(v.any() == true);
    }
}

TEST_CASE("libcxx_members_any") {
    test_any<0>();
    test_any<1>();
    test_any<31>();
    test_any<32>();
    test_any<33>();
    test_any<63>();
    test_any<64>();
    test_any<65>();
    test_any<1000>();
}

template <std::size_t N>
void test_count() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        const nstd::bitset<N> v = cases[c];
        std::size_t c1 = v.count();
        std::size_t c2 = 0;
        for (std::size_t i = 0; i < v.size(); ++i)
            if (v[i])
                ++c2;
        CHECK(c1 == c2);
    }
}

TEST_CASE("libcxx_members_count") {
    test_count<0>();
    test_count<1>();
    test_count<31>();
    test_count<32>();
    test_count<33>();
    test_count<63>();
    test_count<64>();
    test_count<65>();
    test_count<1000>();
}

template <std::size_t N>
void test_flip_all() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        nstd::bitset<N> v1 = cases[c];
        nstd::bitset<N> v2 = v1;
        v2.flip();
        for (std::size_t i = 0; i < v1.size(); ++i)
            CHECK(v2[i] == ~v1[i]);
    }
}

TEST_CASE("libcxx_members_flip_all") {
    test_flip_all<0>();
    test_flip_all<1>();
    test_flip_all<31>();
    test_flip_all<32>();
    test_flip_all<33>();
    test_flip_all<63>();
    test_flip_all<64>();
    test_flip_all<65>();
    test_flip_all<1000>();
}

template <std::size_t N>
void test_flip_one() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        nstd::bitset<N> v = cases[c];
        if (v.size() > 0) {
            std::size_t middle = v.size() / 2;
            v.flip(middle);
            bool b = v[middle];
            CHECK(v[middle] == b);
            v.flip(middle);
            CHECK(v[middle] != b);
            v.flip(middle);
            CHECK(v[middle] == b);
        }
    }
}

TEST_CASE("libcxx_members_flip_one") {
    test_flip_one<0>();
    test_flip_one<1>();
    test_flip_one<31>();
    test_flip_one<32>();
    test_flip_one<33>();
    test_flip_one<63>();
    test_flip_one<64>();
    test_flip_one<65>();
    test_flip_one<1000>();
}

template <std::size_t N>
void test_index() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        nstd::bitset<N> v1 = cases[c];
        if (v1.size() > 0) {
            CHECK(v1[N/2] == v1.test(N/2));
            typename nstd::bitset<N>::reference r = v1[N/2];
            CHECK(r == v1.test(N/2));
            typename nstd::bitset<N>::reference r2 = v1[N/2];
            r = r2;
            CHECK(r == v1.test(N/2));
            r = false;
            CHECK(r == false);
            CHECK(v1.test(N/2) == false);
            r = true;
            CHECK(r == true);
            CHECK(v1.test(N/2) == true);
            bool b = ~r;
            CHECK(r == true);
            CHECK(v1.test(N/2) == true);
            CHECK(b == false);
            r.flip();
            CHECK(r == false);
            CHECK(v1.test(N/2) == false);
        }
    }
}

TEST_CASE("libcxx_members_index") {
    test_index<0>();
    test_index<1>();
    test_index<31>();
    test_index<32>();
    test_index<33>();
    test_index<63>();
    test_index<64>();
    test_index<65>();
    test_index<1000>();
}

template <std::size_t N>
void test_index_const() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        nstd::bitset<N> const v = cases[c];
        if (v.size() > 0) {
            CHECK(v[N/2] == v.test(N/2));
        }
    }
}

TEST_CASE("libcxx_members_index_const") {
    test_index_const<0>();
    test_index_const<1>();
    test_index_const<31>();
    test_index_const<32>();
    test_index_const<33>();
    test_index_const<63>();
    test_index_const<64>();
    test_index_const<65>();
    test_index_const<1000>();
}

template <std::size_t N>
void test_left_shift() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        for (std::size_t s = 0; s <= N+1; ++s) {
            nstd::bitset<N> v1 = cases[c];
            nstd::bitset<N> v2 = v1;
            CHECK((v1 <<= s) == (v2 << s));
        }
    }
}

TEST_CASE("libcxx_members_left_shift") {
    test_left_shift<0>();
    test_left_shift<1>();
    test_left_shift<31>();
    test_left_shift<32>();
    test_left_shift<33>();
    test_left_shift<63>();
    test_left_shift<64>();
    test_left_shift<65>();
    test_left_shift<1000>();
}

template <std::size_t N>
void test_left_shift_eq() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        for (std::size_t s = 0; s <= N+1; ++s) {
            nstd::bitset<N> v1 = cases[c];
            nstd::bitset<N> v2 = v1;
            v1 <<= s;
            for (std::size_t i = 0; i < v1.size(); ++i)
                if (i < s)
                    CHECK(v1[i] == 0);
                else
                    CHECK(v1[i] == v2[i-s]);
        }
    }
}

TEST_CASE("libcxx_members_left_shift_eq") {
    test_left_shift_eq<0>();
    test_left_shift_eq<1>();
    test_left_shift_eq<31>();
    test_left_shift_eq<32>();
    test_left_shift_eq<33>();
    test_left_shift_eq<63>();
    test_left_shift_eq<64>();
    test_left_shift_eq<65>();
    test_left_shift_eq<1000>();
}

template <std::size_t N>
void test_none() {
    nstd::bitset<N> v;
    v.reset();
    CHECK(v.none() == true);
    v.set();
    CHECK(v.none() == (N == 0));
    if (v.size() > 1) {
        v[N/2] = false;
        CHECK(v.none() == false);
        v.reset();
        v[N/2] = true;
        CHECK(v.none() == false);
    }
}

TEST_CASE("libcxx_members_none") {
    test_none<0>();
    test_none<1>();
    test_none<31>();
    test_none<32>();
    test_none<33>();
    test_none<63>();
    test_none<64>();
    test_none<65>();
    test_none<1000>();
}

template <std::size_t N>
void test_not_all() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        nstd::bitset<N> v1 = cases[c];
        nstd::bitset<N> v2 = ~v1;
        for (std::size_t i = 0; i < v1.size(); ++i)
            CHECK(v2[i] == ~v1[i]);
    }
}

TEST_CASE("libcxx_members_not_all") {
    test_not_all<0>();
    test_not_all<1>();
    test_not_all<31>();
    test_not_all<32>();
    test_not_all<33>();
    test_not_all<63>();
    test_not_all<64>();
    test_not_all<65>();
    test_not_all<1000>();
}

template <std::size_t N>
void test_op_and_eq() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c1 = 0; c1 != cases.size(); ++c1) {
        for (std::size_t c2 = 0; c2 != cases.size(); ++c2) {
            nstd::bitset<N> v1 = cases[c1];
            nstd::bitset<N> v2 = cases[c2];
            nstd::bitset<N> v3 = v1;
            v1 &= v2;
            for (std::size_t i = 0; i < v1.size(); ++i)
                CHECK(v1[i] == (v3[i] && v2[i]));
        }
    }
}

TEST_CASE("libcxx_members_op_and_eq") {
    test_op_and_eq<0>();
    test_op_and_eq<1>();
    test_op_and_eq<31>();
    test_op_and_eq<32>();
    test_op_and_eq<33>();
    test_op_and_eq<63>();
    test_op_and_eq<64>();
    test_op_and_eq<65>();
    test_op_and_eq<1000>();
}

template <std::size_t N>
void test_equality() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        nstd::bitset<N> const v1 = cases[c];
        nstd::bitset<N> v2 = v1;
        CHECK(v1 == v2);
        if (v1.size() > 0) {
            v2[N/2].flip();
            CHECK(v1 != v2);
        }
    }
}

TEST_CASE("libcxx_members_equality") {
    test_equality<0>();
    test_equality<1>();
    test_equality<31>();
    test_equality<32>();
    test_equality<33>();
    test_equality<63>();
    test_equality<64>();
    test_equality<65>();
    test_equality<1000>();
}

template <std::size_t N>
void test_op_or_eq() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c1 = 0; c1 != cases.size(); ++c1) {
        for (std::size_t c2 = 0; c2 != cases.size(); ++c2) {
            nstd::bitset<N> v1 = cases[c1];
            nstd::bitset<N> v2 = cases[c2];
            nstd::bitset<N> v3 = v1;
            v1 |= v2;
            for (std::size_t i = 0; i < v1.size(); ++i)
                CHECK(v1[i] == (v3[i] || v2[i]));
        }
    }
}

TEST_CASE("libcxx_members_op_or_eq") {
    test_op_or_eq<0>();
    test_op_or_eq<1>();
    test_op_or_eq<31>();
    test_op_or_eq<32>();
    test_op_or_eq<33>();
    test_op_or_eq<63>();
    test_op_or_eq<64>();
    test_op_or_eq<65>();
    test_op_or_eq<1000>();
}

template <std::size_t N>
void test_op_xor_eq() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c1 = 0; c1 != cases.size(); ++c1) {
        for (std::size_t c2 = 0; c2 != cases.size(); ++c2) {
            nstd::bitset<N> v1 = cases[c1];
            nstd::bitset<N> v2 = cases[c2];
            nstd::bitset<N> v3 = v1;
            v1 ^= v2;
            for (std::size_t i = 0; i < v1.size(); ++i)
                CHECK(v1[i] == (v3[i] != v2[i]));
        }
    }
}

TEST_CASE("libcxx_members_op_xor_eq") {
    test_op_xor_eq<0>();
    test_op_xor_eq<1>();
    test_op_xor_eq<31>();
    test_op_xor_eq<32>();
    test_op_xor_eq<33>();
    test_op_xor_eq<63>();
    test_op_xor_eq<64>();
    test_op_xor_eq<65>();
    test_op_xor_eq<1000>();
}

template <std::size_t N>
void test_reset_all() {
    nstd::bitset<N> v;
    v.set();
    v.reset();
    for (std::size_t i = 0; i < v.size(); ++i)
        CHECK(!v[i]);
}

TEST_CASE("libcxx_members_reset_all") {
    test_reset_all<0>();
    test_reset_all<1>();
    test_reset_all<31>();
    test_reset_all<32>();
    test_reset_all<33>();
    test_reset_all<63>();
    test_reset_all<64>();
    test_reset_all<65>();
    test_reset_all<1000>();
}

#if defined(TEST_COMPILER_C1XX)
#pragma warning(disable: 6294) // Ill-defined for-loop:  initial condition does not satisfy test.  Loop body not executed.
#endif

template <std::size_t N>
void test_reset_one() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        for (std::size_t i = 0; i != N; ++i) {
            nstd::bitset<N> v = cases[c];
            v.reset(i);
            CHECK(v[i] == false);
        }
    }
}

TEST_CASE("libcxx_members_reset_one") {
    test_reset_one<0>();
    test_reset_one<1>();
    test_reset_one<31>();
    test_reset_one<32>();
    test_reset_one<33>();
    test_reset_one<63>();
    test_reset_one<64>();
    test_reset_one<65>();
    test_reset_one<1000>();
}

template <std::size_t N>
void test_right_shift() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        for (std::size_t s = 0; s <= N+1; ++s) {
            nstd::bitset<N> v1 = cases[c];
            nstd::bitset<N> v2 = v1;
            CHECK((v1 >>= s) == (v2 >> s));
        }
    }
}

TEST_CASE("libcxx_members_right_shift") {
    test_right_shift<0>();
    test_right_shift<1>();
    test_right_shift<31>();
    test_right_shift<32>();
    test_right_shift<33>();
    test_right_shift<63>();
    test_right_shift<64>();
    test_right_shift<65>();
    test_right_shift<1000>();
}

template <std::size_t N>
void test_right_shift_eq() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        for (std::size_t s = 0; s <= N+1; ++s) {
            nstd::bitset<N> v1 = cases[c];
            nstd::bitset<N> v2 = v1;
            v1 >>= s;
            for (std::size_t i = 0; i < v1.size(); ++i)
                if (i + s < v1.size())
                    CHECK(v1[i] == v2[i + s]);
                else
                    CHECK(v1[i] == 0);
        }
    }
}

TEST_CASE("libcxx_members_right_shift_eq") {
    test_right_shift_eq<0>();
    test_right_shift_eq<1>();
    test_right_shift_eq<31>();
    test_right_shift_eq<32>();
    test_right_shift_eq<33>();
    test_right_shift_eq<63>();
    test_right_shift_eq<64>();
    test_right_shift_eq<65>();
    test_right_shift_eq<1000>();
}

template <std::size_t N>
void test_set_all() {
    nstd::bitset<N> v;
    v.set();
    for (std::size_t i = 0; i < v.size(); ++i) {
        CHECK(v[i]);
    }
}

TEST_CASE("libcxx_members_set_all") {
    test_set_all<0>();
    test_set_all<1>();
    test_set_all<31>();
    test_set_all<32>();
    test_set_all<33>();
    test_set_all<63>();
    test_set_all<64>();
    test_set_all<65>();
    test_set_all<1000>();
}

template <std::size_t N>
void test_set_one() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        nstd::bitset<N> v = cases[c];
        if (v.size() > 0) {
            std::size_t middle = v.size() / 2;
            v.set(middle);
            CHECK(v[middle] == true);
            v.set(middle, false);
            CHECK(v[middle] == false);
        }
    }
}

TEST_CASE("libcxx_members_set_one") {
    test_set_one<0>();
    test_set_one<1>();
    test_set_one<31>();
    test_set_one<32>();
    test_set_one<33>();
    test_set_one<63>();
    test_set_one<64>();
    test_set_one<65>();
    test_set_one<1000>();
}

template <std::size_t N>
void test_size() {
    const nstd::bitset<N> v;
    CHECK(v.size() == N);
}

TEST_CASE("libcxx_members_size") {
    test_size<0>();
    test_size<1>();
    test_size<31>();
    test_size<32>();
    test_size<33>();
    test_size<63>();
    test_size<64>();
    test_size<65>();
    test_size<1000>();
}

template <std::size_t N>
void test_test() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        nstd::bitset<N> const v = cases[c];
        if (v.size() > 0) {
            std::size_t middle = v.size() / 2;
            bool b = v.test(middle);
            CHECK(b == v[middle]);
        }
    }
}

TEST_CASE("libcxx_members_test") {
    test_test<0>();
    test_test<1>();
    test_test<31>();
    test_test<32>();
    test_test<33>();
    test_test<63>();
    test_test<64>();
    test_test<65>();
    test_test<1000>();
}

template <class CharT, std::size_t N>
void check_equal(std::basic_string<CharT> const& s, nstd::bitset<N> const& b, CharT zero, CharT one) {
    CHECK(s.size() == b.size());
    for (std::size_t i = 0; i < b.size(); ++i) {
        if (b[i]) {
            CHECK(s[b.size() - 1 - i] == one);
        } else {
            CHECK(s[b.size() - 1 - i] == zero);
        }
    }
}

template <std::size_t N>
void test_to_string() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c = 0; c != cases.size(); ++c) {
        nstd::bitset<N> const v = cases[c];
        {
            std::wstring s = v.template to_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >();
            check_equal(s, v, L'0', L'1');
        }
        {
            std::wstring s = v.template to_string<wchar_t, std::char_traits<wchar_t> >();
            check_equal(s, v, L'0', L'1');
        }
        {
            std::string s = v.template to_string<char>();
            check_equal(s, v, '0', '1');
        }
        {
            std::string s = v.to_string();
            check_equal(s, v, '0', '1');
        }
        {
            std::wstring s = v.template to_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >('0');
            check_equal(s, v, L'0', L'1');
        }
        {
            std::wstring s = v.template to_string<wchar_t, std::char_traits<wchar_t> >('0');
            check_equal(s, v, L'0', L'1');
        }
        {
            std::string s = v.template to_string<char>('0');
            check_equal(s, v, '0', '1');
        }
        {
            std::string s = v.to_string('0');
            check_equal(s, v, '0', '1');
        }
        {
            std::wstring s = v.template to_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >('0', '1');
            check_equal(s, v, L'0', L'1');
        }
        {
            std::wstring s = v.template to_string<wchar_t, std::char_traits<wchar_t> >('0', '1');
            check_equal(s, v, L'0', L'1');
        }
        {
            std::string s = v.template to_string<char>('0', '1');
            check_equal(s, v, '0', '1');
        }
        {
            std::string s = v.to_string('0', '1');
            check_equal(s, v, '0', '1');
        }
        {
            std::string s = v.to_string('x', 'y');
            check_equal(s, v, 'x', 'y');
        }
    }
}

TEST_CASE("libcxx_members_to_string") {
    test_to_string<0>();
    test_to_string<1>();
    test_to_string<31>();
    test_to_string<32>();
    test_to_string<33>();
    test_to_string<63>();
    test_to_string<64>();
    test_to_string<65>();
    test_to_string<1000>();
}

template <std::size_t N>
void test_to_ullong() {
    const std::size_t M = sizeof(unsigned long long) * CHAR_BIT < N ? sizeof(unsigned long long) * CHAR_BIT : N;
    const bool is_M_zero = std::integral_constant<bool, M == 0>::value; // avoid compiler warnings
    const std::size_t X = is_M_zero ? sizeof(unsigned long long) * CHAR_BIT - 1 : sizeof(unsigned long long) * CHAR_BIT - M;
    const unsigned long long max = is_M_zero ? 0 : (unsigned long long)(-1) >> X;
    unsigned long long tests[] = {
        0,
        std::min<unsigned long long>(1, max),
        std::min<unsigned long long>(2, max),
        std::min<unsigned long long>(3, max),
        std::min(max, max-3),
        std::min(max, max-2),
        std::min(max, max-1),
        max
    };
    for (std::size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
        unsigned long long j = tests[i];
        nstd::bitset<N> v(j);
        CHECK(j == v.to_ullong());
    }
    { // test values bigger than can fit into the bitset
        const unsigned long long val = 0x55AAAAFFFFAAAA55ULL;
        const bool canFit = N < sizeof(unsigned long long) * CHAR_BIT;
        const unsigned long long mask = canFit ? (1ULL << (canFit ? N : 0)) - 1 : (unsigned long long)(-1); // avoid compiler warnings
        nstd::bitset<N> v(val);
        CHECK(v.to_ullong() == (val & mask)); // we shouldn't return bit patterns from outside the limits of the bitset.
    }
}

TEST_CASE("libcxx_members_to_ullong") {
    test_to_ullong<0>();
    test_to_ullong<1>();
    test_to_ullong<31>();
    test_to_ullong<32>();
    test_to_ullong<33>();
    test_to_ullong<63>();
    test_to_ullong<64>();
    test_to_ullong<65>();
    test_to_ullong<1000>();
}

template <std::size_t N>
void test_to_ulong() {
    const std::size_t M = sizeof(unsigned long) * CHAR_BIT < N ? sizeof(unsigned long) * CHAR_BIT : N;
    const bool is_M_zero = std::integral_constant<bool, M == 0>::value; // avoid compiler warnings
    const std::size_t X = is_M_zero ? sizeof(unsigned long) * CHAR_BIT - 1 : sizeof(unsigned long) * CHAR_BIT - M;
    const std::size_t max = is_M_zero ? 0 : std::size_t(std::numeric_limits<unsigned long>::max()) >> X;
    std::size_t tests[] = {
        0,
        std::min<std::size_t>(1, max),
        std::min<std::size_t>(2, max),
        std::min<std::size_t>(3, max),
        std::min(max, max-3),
        std::min(max, max-2),
        std::min(max, max-1),
        max
    };
    for (std::size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
        std::size_t j = tests[i];
        nstd::bitset<N> v(j);
        CHECK(j == v.to_ulong());
    }

    { // test values bigger than can fit into the bitset
        const unsigned long val = 0x5AFFFFA5UL;
        const bool canFit = N < sizeof(unsigned long) * CHAR_BIT;
        const unsigned long mask = canFit ? (1UL << (canFit ? N : 0)) - 1 : (unsigned long)(-1); // avoid compiler warnings
        nstd::bitset<N> v(val);
        CHECK(v.to_ulong() == (val & mask)); // we shouldn't return bit patterns from outside the limits of the bitset.
    }
}

TEST_CASE("libcxx_members_to_ulong") {
    test_to_ulong<0>();
    test_to_ulong<1>();
    test_to_ulong<31>();
    test_to_ulong<32>();
    test_to_ulong<33>();
    test_to_ulong<63>();
    test_to_ulong<64>();
    test_to_ulong<65>();
    test_to_ulong<1000>();
}