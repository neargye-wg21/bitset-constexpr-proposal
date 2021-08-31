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

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("basic") {
    // https://github.com/microsoft/STL/blob/main/tests/tr1/tests/bitset/test.cpp

    constexpr nstd::bitset<5> x50;
    constexpr nstd::bitset<5> x51(0xf);
    constexpr nstd::bitset<5> x52("10101", 5);
    constexpr nstd::bitset<5> x53(x52);

    static_assert(x50.to_ulong() == 0x00);
    static_assert(x51.to_ulong() == 0x0f);
    static_assert(x52.to_ulong() == 0x15);
    static_assert(x53.to_ulong() == 0x15);

    //// test arithmetic
    //x50 |= x51;
    //CHECK(x50.to_ulong() == 0x0f);
    //x50 ^= x52;
    //CHECK(x50.to_ulong() == 0x1a);
    //x50 &= x51;
    //CHECK(x50.to_ulong() == 0x0a);
    //x50 <<= 2;
    //CHECK(x50.to_ulong() == 0x08);
    //x50 >>= 3;
    //CHECK(x50.to_ulong() == 0x01);
    //x50.set(2);
    //CHECK(x50.to_ulong() == 0x05);
    //x50.set(0, 0);
    //CHECK(x50.to_ulong() == 0x04);
    //x50.set();
    //CHECK(x50.to_ulong() == 0x1f);
    //x50.reset(3);
    //CHECK(x50.to_ulong() == 0x17);
    //x50.reset();
    //CHECK(x50.to_ulong() == 0x00);
    //x50.flip(2);
    //CHECK(x50.to_ulong() == 0x04);
    //x50.flip();
    //CHECK(x50.to_ulong() == 0x1b);


    // constexpr std::string str = x52.to_string<char, std::char_traits<char>, std::allocator<char>>();
    // static_assert(str == "10101");

    //CHECK(x50.count() == 4);
    //CHECK(x52.count() == 3);
    //CHECK(x50.size() == 5);
    //CHECK(x51.size() == 5);
    //CHECK(x50 == x50);
    //CHECK(x50 != x51);
    //CHECK(x50.test(1));
    //CHECK(!x50.test(2));
    //CHECK(x50.any());
    //CHECK(!x50.none());
    //x50.reset();
    //CHECK(!x50.any());
    //CHECK(x50.none());

    //// test friend arithmetic functions
    constexpr nstd::bitset<5> bx05(0x05);
    constexpr nstd::bitset<5> bx1f(0x1f);
    constexpr nstd::bitset<5> bx1a("11010", 5);

    static_assert((x51 << 2).to_ulong() == 0x1c);
    static_assert((x51 >> 2).to_ulong() == 0x03);
    static_assert((x51 & x52) == bx05);
    static_assert((x51 | x52) == bx1f);
    static_assert((x51 ^ x52) == bx1a);

    constexpr nstd::bitset<5> x54("11111", 5);
    static_assert(!x51.all());
    static_assert(x54.all());
    static_assert((int)x54.to_ullong() == 0x1f);

    static_assert(std::hash<nstd::bitset<5>>{}(x54) == std::hash<nstd::bitset<5>>{}(x54));

    //// test larger bitset
    constexpr nstd::bitset<153> x153a = []() { return (nstd::bitset<153>{}.set(100) >>= 99) <<= 1; }();
    constexpr nstd::bitset<153> x153b = []() { return nstd::bitset<153>{}.set(121); }();

    static_assert(x153a.to_ulong() == 0x04);
    static_assert(x153b.any());
    static_assert(!x153b.test(105));
    static_assert(x153b.test(121));
    static_assert(x153b.count() == 1);
    static_assert(((x153a | x153b) ^ x153b) == x153a);
}
