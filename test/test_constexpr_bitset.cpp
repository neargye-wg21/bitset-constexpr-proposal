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

using namespace std::literals;

TEST_CASE("basic") {
    // https://github.com/microsoft/STL/blob/main/tests/tr1/tests/bitset/test.cpp

    constexpr nstd::bitset<5> x50;
    constexpr nstd::bitset<5> x51(0xf);
    constexpr nstd::bitset<5> x52 = []() constexpr {
#if defined(__cpp_lib_constexpr_string) && __cpp_lib_constexpr_string >= 201907L
        std::string sx52("xx10101ab");
        return nstd::bitset<5>(sx52, 2, 5);
#else
        return nstd::bitset<5>("10101", 5);
#endif  // __cpp_lib_constexpr_string
    }
    ();
    constexpr nstd::bitset<5> x53(x52);

    static_assert(x50.to_ulong() == 0x00);
    static_assert(x51.to_ulong() == 0x0f);
    static_assert(x52.to_ulong() == 0x15);
    static_assert(x53.to_ulong() == 0x15);

    //// test arithmetic
    static_assert([left = nstd::bitset<5>(0x0f), right = nstd::bitset<5>(0xf)]() mutable { return left |= right; }() == 0x0f);
    static_assert([left = nstd::bitset<5>(0x0f), right = nstd::bitset<5>(0x15)]() mutable { return left ^= right; }() == 0x1a);
    static_assert([left = nstd::bitset<5>(0x1a), right = nstd::bitset<5>(0xf)]() mutable { return left &= right; }() == 0x0a);
    static_assert([left = nstd::bitset<5>(0x0a), right = 2]() mutable { return left <<= right; }() == 0x08);
    static_assert([left = nstd::bitset<5>(0x08), right = 3]() mutable { return left >>= right; }() == 0x01);
    static_assert([left = nstd::bitset<5>(0x01)]() mutable { return left.set(2); }() == 0x05);
    static_assert([left = nstd::bitset<5>(0x05)]() mutable { return left.set(0, 0); }() == 0x04);
    static_assert([left = nstd::bitset<5>(0x04)]() mutable { return left.set(); }() == 0x1f);
    static_assert([left = nstd::bitset<5>(0x1f)]() mutable { return left.reset(3); }() == 0x17);
    static_assert([left = nstd::bitset<5>(0x17)]() mutable { return left.reset(); }() == 0x00);
    static_assert([left = nstd::bitset<5>(0x00)]() mutable { return left.flip(2); }() == 0x04);
    static_assert([left = nstd::bitset<5>(0x04)]() mutable { return left.flip(); }() == 0x1b);

#if defined(__cpp_lib_constexpr_string) && __cpp_lib_constexpr_string >= 201907L
    static_assert([&]() constexpr {
        std::string str = x53.to_string<char, std::char_traits<char>, std::allocator<char>>();
        return std::equal(str.begin(), str.end(), "10101");
    }());
#endif  // __cpp_lib_constexpr_string

    constexpr nstd::bitset<5> x54(0x1b);

    static_assert([left = x54]() mutable { return left.count(); }() == 4);
    static_assert([left = x52]() mutable { return left.count(); }() == 3);
    static_assert([left = x54]() mutable { return left.size(); }() == 5);
    static_assert([left = x51]() mutable { return left.size(); }() == 5);
    static_assert([left = x54, right = x54]() mutable { return left == right; }());
    static_assert([left = x54, right = x51]() mutable { return left != right; }());
    static_assert([left = x54]() mutable { return left.test(1); }());
    static_assert([left = x54]() mutable { return !left.test(2); }());
    static_assert([left = x54]() mutable { return left.any(); }());
    static_assert([left = x54]() mutable { return !left.none(); }());
    static_assert([left = x54]() mutable {
        left.reset();
        return !left.any();
    }());
    static_assert([left = x54]() mutable {
        left.reset();
        return left.none();
    }());

    //// test friend arithmetic functions
    constexpr nstd::bitset<5> bx05(0x05);
    constexpr nstd::bitset<5> bx1f(0x1f);
    constexpr nstd::bitset<5> bx1a("11010", 5);

    static_assert((x51 << 2).to_ulong() == 0x1c);
    static_assert((x51 >> 2).to_ulong() == 0x03);
    static_assert((x51 & x52) == bx05);
    static_assert((x51 | x52) == bx1f);
    static_assert((x51 ^ x52) == bx1a);

    constexpr nstd::bitset<5> x55("11111", 5);
    static_assert(!x51.all());
    static_assert(x55.all());
    static_assert((int)x55.to_ullong() == 0x1f);

    static_assert(std::hash<nstd::bitset<5>>{}(x55) == std::hash<nstd::bitset<5>>{}(x55));

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
