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

// https://github.com/llvm/llvm-project/tree/main/libcxx/test/std/utilities/template.bitset/bitset.operators

template <std::size_t N>
void test_op_and() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c1 = 0; c1 != cases.size(); ++c1) {
        for (std::size_t c2 = 0; c2 != cases.size(); ++c2) {
            nstd::bitset<N> v1 = cases[c1];
            nstd::bitset<N> v2 = cases[c2];
            nstd::bitset<N> v3 = v1;
            CHECK((v1 & v2) == (v3 &= v2));
        }
    }
}

TEST_CASE("libcxx_operators_and") {
    test_op_and<0>();
    test_op_and<1>();
    test_op_and<31>();
    test_op_and<32>();
    test_op_and<33>();
    test_op_and<63>();
    test_op_and<64>();
    test_op_and<65>();
    test_op_and<1000>();
}

template <std::size_t N>
void test_op_not() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c1 = 0; c1 != cases.size(); ++c1) {
        for (std::size_t c2 = 0; c2 != cases.size(); ++c2) {
            nstd::bitset<N> v1 = cases[c1];
            nstd::bitset<N> v2 = cases[c2];
            nstd::bitset<N> v3 = v1;
            CHECK((v1 ^ v2) == (v3 ^= v2));
        }
    }
}

TEST_CASE("libcxx_operators_not") {
    test_op_not<0>();
    test_op_not<1>();
    test_op_not<31>();
    test_op_not<32>();
    test_op_not<33>();
    test_op_not<63>();
    test_op_not<64>();
    test_op_not<65>();
    test_op_not<1000>();
}

template <std::size_t N>
void test_op_or() {
    std::vector<nstd::bitset<N> > const cases = get_test_cases<N>();
    for (std::size_t c1 = 0; c1 != cases.size(); ++c1) {
        for (std::size_t c2 = 0; c2 != cases.size(); ++c2) {
            nstd::bitset<N> v1 = cases[c1];
            nstd::bitset<N> v2 = cases[c2];
            nstd::bitset<N> v3 = v1;
            CHECK((v1 | v2) == (v3 |= v2));
        }
    }
}

TEST_CASE("libcxx_operators_or") {
    test_op_or<0>();
    test_op_or<1>();
    test_op_or<31>();
    test_op_or<32>();
    test_op_or<33>();
    test_op_or<63>();
    test_op_or<64>();
    test_op_or<65>();
    test_op_or<1000>();
}