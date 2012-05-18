/*
 * Copyright (c) 2012 Thomas Kemmer <tkemmer@computer.org>
 *
 * http://code.google.com/p/stlencoders/
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

#include <stlencoders/base2.hpp>

#include <cassert>
#include <cstdlib>
#include <string>

#include "util.hpp"

int main()
{
    typedef stlencoders::base2<char> base2;
    typedef stlencoders::base2<wchar_t> wbase2;

    assert(strenc<base2>("") == "");
    assert(strenc<base2>("f") == "01100110");
    assert(strenc<base2>("fo") == "0110011001101111");
    assert(strenc<base2>("foo") == "011001100110111101101111");

    assert(strdec<base2>("") == "");
    assert(strdec<base2>("01100110") == "f");
    assert(strdec<base2>("0110011001101111") == "fo");
    assert(strdec<base2>("011001100110111101101111") == "foo");

    assert(strenc<wbase2>("") == L"");
    assert(strenc<wbase2>("f") == L"01100110");
    assert(strenc<wbase2>("fo") == L"0110011001101111");
    assert(strenc<wbase2>("foo") == L"011001100110111101101111");

    assert(strdec<wbase2>(L"") == "");
    assert(strdec<wbase2>(L"01100110") == "f");
    assert(strdec<wbase2>(L"0110011001101111") == "fo");
    assert(strdec<wbase2>(L"011001100110111101101111") == "foo");

    // test some special bit patterns

    assert(strenc<base2>(std::string(1, '\x00')) == "00000000");
    assert(strdec<base2>("00000000") == std::string(1, '\x00'));
    assert(strenc<base2>(std::string(1, '\x01')) == "00000001");
    assert(strdec<base2>("00000001") == std::string(1, '\x01'));
    assert(strenc<base2>(std::string(1, '\xfe')) == "11111110");
    assert(strdec<base2>("11111110") == std::string(1, '\xfe'));
    assert(strenc<base2>(std::string(1, '\xff')) == "11111111");
    assert(strdec<base2>("11111111") == std::string(1, '\xff'));

    assert(strenc<wbase2>(std::string(1, '\x00')) == L"00000000");
    assert(strdec<wbase2>(L"00000000") == std::string(1, '\x00'));
    assert(strenc<wbase2>(std::string(1, '\x01')) == L"00000001");
    assert(strdec<wbase2>(L"00000001") == std::string(1, '\x01'));
    assert(strenc<wbase2>(std::string(1, '\xfe')) == L"11111110");
    assert(strdec<wbase2>(L"11111110") == std::string(1, '\xfe'));
    assert(strenc<wbase2>(std::string(1, '\xff')) == L"11111111");
    assert(strdec<wbase2>(L"11111111") == std::string(1, '\xff'));

    // error handling

    assert_throw(strdec<base2>("?0"), stlencoders::invalid_character);
    assert_throw(strdec<base2>("0?"), stlencoders::invalid_character);

    assert_throw(strdec<base2>("0"), stlencoders::invalid_length);
    assert_throw(strdec<base2>("00"), stlencoders::invalid_length);
    assert_throw(strdec<base2>("000"), stlencoders::invalid_length);
    assert_throw(strdec<base2>("0000"), stlencoders::invalid_length);
    assert_throw(strdec<base2>("00000"), stlencoders::invalid_length);
    assert_throw(strdec<base2>("000000"), stlencoders::invalid_length);
    assert_throw(strdec<base2>("0000000"), stlencoders::invalid_length);

    return EXIT_SUCCESS;
}
