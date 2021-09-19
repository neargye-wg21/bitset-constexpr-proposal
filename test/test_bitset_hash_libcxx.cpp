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

#include "poisoned_hash_helper.h"

// https://github.com/llvm/llvm-project/tree/main/libcxx/test/std/utilities/template.bitset/bitset.hash

template <std::size_t N>
void test()
{
    typedef nstd::bitset<N> T;
    typedef std::hash<T> H;
    //static_assert((std::is_same<typename H::argument_type, T>::value), "" );
    //static_assert((std::is_same<typename H::result_type, std::size_t>::value), "" );
    static_assert((std::is_same_v<decltype(std::declval<H>()(std::declval<T>())), std::size_t>));
    CHECK_NOTHROW(H()(T()));

    H h;
    T bs(static_cast<unsigned long long>(N));
    const std::size_t result = h(bs);
    CHECK(result == N);
    ((void)result); // Prevent unused warning
}

TEST_CASE("libcxx_hash_test") {
    test<0>();
    test<10>();
    test<100>();
    test<1000>();
}

TEST_CASE("libcxx_hash_specializations_available") {
    //test_library_hash_specializations_available();
    {
        test_hash_enabled_for_type<nstd::bitset<0> >();
        test_hash_enabled_for_type<nstd::bitset<1> >();
        test_hash_enabled_for_type<nstd::bitset<1024> >();
        test_hash_enabled_for_type<nstd::bitset<100000> >();
    }
}