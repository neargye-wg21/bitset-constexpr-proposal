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

#include <algorithm>  // for 'min' and 'max'
#include <array>
#include <cassert>
#include <iterator>
#include <stdexcept>  // for 'invalid_argument'

#include <bitset.hpp>

#include "bitset_test_cases.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// https://github.com/llvm/llvm-project/tree/main/libcxx/test/std/utilities/template.bitset/bitset.cons

template <std::size_t N>
void test_char_pointer_ctor() {
    const char str[] = "1010101010";
    nstd::bitset<N> v(str);
    std::size_t M = std::min<std::size_t>(v.size(), 10);
    for (std::size_t i = 0; i < M; ++i)
        CHECK(v[i] == (str[M - 1 - i] == '1'));
    for (std::size_t i = 10; i < v.size(); ++i)
        CHECK(v[i] == false);
}

TEST_CASE("libcxx_cons_char_pointer") {
    test_char_pointer_ctor<0>();
    test_char_pointer_ctor<1>();
    test_char_pointer_ctor<31>();
    test_char_pointer_ctor<32>();
    test_char_pointer_ctor<33>();
    test_char_pointer_ctor<63>();
    test_char_pointer_ctor<64>();
    test_char_pointer_ctor<65>();
    test_char_pointer_ctor<1000>();
}

template <std::size_t N>
void test_default_ctor() {
    nstd::bitset<N> v1;
    CHECK(v1.size() == N);
    for (std::size_t i = 0; i < v1.size(); ++i)
        CHECK(v1[i] == false);
}

TEST_CASE("libcxx_cons_default_ctor") {
    test_default_ctor<0>();
    test_default_ctor<1>();
    test_default_ctor<31>();
    test_default_ctor<32>();
    test_default_ctor<33>();
    test_default_ctor<63>();
    test_default_ctor<64>();
    test_default_ctor<65>();
    test_default_ctor<1000>();
}

template <std::size_t N>
void test_string_ctor() {
    {
        std::string s("xxx1010101010xxxx");
        nstd::bitset<N> v(s, 3, 10);
        std::size_t M = std::min<std::size_t>(v.size(), 10);
        for (std::size_t i = 0; i < M; ++i)
            CHECK(v[i] == (s[3 + M - 1 - i] == '1'));
        for (std::size_t i = 10; i < v.size(); ++i)
            CHECK(v[i] == false);
    }
    {
        std::string s("xxxbababababaxxxx");
        nstd::bitset<N> v(s, 3, 10, 'a', 'b');
        std::size_t M = std::min<std::size_t>(v.size(), 10);
        for (std::size_t i = 0; i < M; ++i)
            CHECK(v[i] == (s[3 + M - 1 - i] == 'b'));
        for (std::size_t i = 10; i < v.size(); ++i)
            CHECK(v[i] == false);
    }
}

TEST_CASE("libcxx_cons_string_ctor") {
    test_string_ctor<0>();
    test_string_ctor<1>();
    test_string_ctor<31>();
    test_string_ctor<32>();
    test_string_ctor<33>();
    test_string_ctor<63>();
    test_string_ctor<64>();
    test_string_ctor<65>();
    test_string_ctor<1000>();
}

template <std::size_t N>
void test_val_ctor() {
    nstd::bitset<N> v(0xAAAAAAAAAAAAAAAAULL);
    CHECK(v.size() == N);
    std::size_t M = std::min<std::size_t>(v.size(), 64);
    for (std::size_t i = 0; i < M; ++i)
        CHECK(v[i] == ((i & 1) != 0));
    for (std::size_t i = M; i < v.size(); ++i)
        CHECK(v[i] == false);
}

TEST_CASE("libcxx_cons_val_ctor") {
    test_val_ctor<0>();
    test_val_ctor<1>();
    test_val_ctor<31>();
    test_val_ctor<32>();
    test_val_ctor<33>();
    test_val_ctor<63>();
    test_val_ctor<64>();
    test_val_ctor<65>();
    test_val_ctor<1000>();
}