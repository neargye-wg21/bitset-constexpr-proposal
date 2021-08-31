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

    nstd::bitset<5> x50;
    nstd::bitset<5> x51(0xf);
    nstd::bitset<5> x52("10101", 5);
    nstd::bitset<5> x53(x52);

    CHECK(x50.to_ulong() == 0x00);
    CHECK(x51.to_ulong() == 0x0f);
    CHECK(x52.to_ulong() == 0x15);
    CHECK(x53.to_ulong() == 0x15);

    // test arithmetic
    x50 |= x51;
    CHECK(x50.to_ulong() == 0x0f);
    x50 ^= x52;
    CHECK(x50.to_ulong() == 0x1a);
    x50 &= x51;
    CHECK(x50.to_ulong() == 0x0a);
    x50 <<= 2;
    CHECK(x50.to_ulong() == 0x08);
    x50 >>= 3;
    CHECK(x50.to_ulong() == 0x01);
    x50.set(2);
    CHECK(x50.to_ulong() == 0x05);
    x50.set(0, 0);
    CHECK(x50.to_ulong() == 0x04);
    x50.set();
    CHECK(x50.to_ulong() == 0x1f);
    x50.reset(3);
    CHECK(x50.to_ulong() == 0x17);
    x50.reset();
    CHECK(x50.to_ulong() == 0x00);
    x50.flip(2);
    CHECK(x50.to_ulong() == 0x04);
    x50.flip();
    CHECK(x50.to_ulong() == 0x1b);

    std::string str = x50.to_string<char, std::char_traits<char>, std::allocator<char>>();
    CHECK(str == "11011");

    CHECK(x50.count() == 4);
    CHECK(x52.count() == 3);
    CHECK(x50.size() == 5);
    CHECK(x51.size() == 5);
    CHECK(x50 == x50);
    CHECK(x50 != x51);
    CHECK(x50.test(1));
    CHECK(!x50.test(2));
    CHECK(x50.any());
    CHECK(!x50.none());
    x50.reset();
    CHECK(!x50.any());
    CHECK(x50.none());

    // test friend arithmetic functions
    std::string sx1a("11010");
    nstd::bitset<5> bx05(0x05);
    nstd::bitset<5> bx1f(0x1f);
    nstd::bitset<5> bx1a(sx1a);

    x50 = x51;
    CHECK((x50 << 2).to_ulong() == 0x1c);
    CHECK((x50 >> 2).to_ulong() == 0x03);
    CHECK((x50 & x52) == bx05);
    CHECK((x50 | x52) == bx1f);
    CHECK((x50 ^ x52) == bx1a);

    nstd::bitset<5> x54("11111");
    CHECK(!x51.all());
    CHECK(x54.all());
    CHECK((int)x54.to_ullong() == 0x1f);

    std::hash<nstd::bitset<5>> hasher;
    CHECK(hasher(x54) == hasher(x54));

    // test larger bitset
    nstd::bitset<153> x153a;
    nstd::bitset<153> x153b;

    (x153a.set(100) >>= 99) <<= 1;
    CHECK(x153a.to_ulong() == 0x04);
    x153b.set(121);
    CHECK(x153b.any());
    CHECK(!x153b.test(105));
    CHECK(x153b.test(121));
    CHECK(x153b.count() == 1);
    CHECK(((x153a | x153b) ^ x153b) == x153a);
}
