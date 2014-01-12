/*
 * Copyright (c) 2014 Thomas Kemmer <tkemmer@computer.org>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "codecvt_base16.hpp"
#include "util.hpp"

#include <cassert>
#include <cstdlib>
#include <locale>
#include <string>

void test_codecvt_base16()
{
    //const stlencoders::codecvt_base16& f =
    //    std::use_facet<stlencoders::codecvt_base16>(std::locale());
    stlencoders::codecvt_base16 cvt;

    //stlencoders::base16_state_t mb = stlencoders::base16_state_t(); // initial shift state
    std::mbstate_t mb = std::mbstate_t(); // initial shift state
    std::string internal = "0123";
    std::string external(internal.size() * cvt.max_length(), '\0');
    const char* from_next;
    char* to_next;
    cvt.out(mb, &internal[0], &internal[internal.size()], from_next,
            &external[0], &external[external.size()], to_next);

    // error checking skipped for brevity
    external.resize(to_next - &external[0]);

    std::cerr << "The string in base16 encoding: " << external << '\n';
}

#ifndef UNITTEST
int main()
{
    test_codecvt_base16();
    return EXIT_SUCCESS;
}
#endif
