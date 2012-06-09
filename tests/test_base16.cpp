/*
 * Copyright (c) 2012 Thomas Kemmer <tkemmer@computer.org>
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

#include "base16.hpp"
#include "util.hpp"

#include <cassert>
#include <cstdlib>
#include <locale>
#include <string>

int main()
{
    typedef stlencoders::base16<char> base16;
    typedef stlencoders::base16<wchar_t> wbase16;

    // RFC 4648 test vectors

    assert(strenc<base16>("") == "");
    assert(strenc<base16>("f") == "66");
    assert(strenc<base16>("fo") == "666F");
    assert(strenc<base16>("foo") == "666F6F");
    assert(strenc<base16>("foob") == "666F6F62");
    assert(strenc<base16>("fooba") == "666F6F6261");
    assert(strenc<base16>("foobar") == "666F6F626172");

    assert(strdec<base16>("") == "");
    assert(strdec<base16>("66") == "f");
    assert(strdec<base16>("666F") == "fo");
    assert(strdec<base16>("666F6F") == "foo");
    assert(strdec<base16>("666F6F62") == "foob");
    assert(strdec<base16>("666F6F6261") == "fooba");
    assert(strdec<base16>("666F6F626172") == "foobar");

    // RFC 4648 test vectors - wide characters

    assert(strenc<wbase16>("") == L"");
    assert(strenc<wbase16>("f") == L"66");
    assert(strenc<wbase16>("fo") == L"666F");
    assert(strenc<wbase16>("foo") == L"666F6F");
    assert(strenc<wbase16>("foob") == L"666F6F62");
    assert(strenc<wbase16>("fooba") == L"666F6F6261");
    assert(strenc<wbase16>("foobar") == L"666F6F626172");

    assert(strdec<wbase16>(L"") == "");
    assert(strdec<wbase16>(L"66") == "f");
    assert(strdec<wbase16>(L"666F") == "fo");
    assert(strdec<wbase16>(L"666F6F") == "foo");
    assert(strdec<wbase16>(L"666F6F62") == "foob");
    assert(strdec<wbase16>(L"666F6F6261") == "fooba");
    assert(strdec<wbase16>(L"666F6F626172") == "foobar");

    // RFC 4648 test vectors - decoding predicate

    assert(strdec<base16>("", make_skip("")) == "");
    assert(strdec<base16>("66", make_skip("")) == "f");
    assert(strdec<base16>("666F", make_skip("")) == "fo");
    assert(strdec<base16>("666F6F", make_skip("")) == "foo");
    assert(strdec<base16>("666F6F62", make_skip("")) == "foob");
    assert(strdec<base16>("666F6F6261", make_skip("")) == "fooba");
    assert(strdec<base16>("666F6F626172", make_skip("")) == "foobar");

    assert(strdec<wbase16>(L"", make_skip(L"")) == "");
    assert(strdec<wbase16>(L"66", make_skip(L"")) == "f");
    assert(strdec<wbase16>(L"666F", make_skip(L"")) == "fo");
    assert(strdec<wbase16>(L"666F6F", make_skip(L"")) == "foo");
    assert(strdec<wbase16>(L"666F6F62", make_skip(L"")) == "foob");
    assert(strdec<wbase16>(L"666F6F6261", make_skip(L"")) == "fooba");
    assert(strdec<wbase16>(L"666F6F626172", make_skip(L"")) == "foobar");

    // test some special bit patterns

    assert(strenc<base16>(std::string(1, '\x00')) == "00");
    assert(strdec<base16>("00") == std::string(1, '\x00'));
    assert(strenc<base16>(std::string(1, '\x01')) == "01");
    assert(strdec<base16>("01") == std::string(1, '\x01'));
    assert(strenc<base16>(std::string(1, '\xfe')) == "FE");
    assert(strdec<base16>("FE") == std::string(1, '\xfe'));
    assert(strenc<base16>(std::string(1, '\xff')) == "FF");
    assert(strdec<base16>("FF") == std::string(1, '\xff'));

    assert(strenc<wbase16>(std::string(1, '\x00')) == L"00");
    assert(strdec<wbase16>(L"00") == std::string(1, '\x00'));
    assert(strenc<wbase16>(std::string(1, '\x01')) == L"01");
    assert(strdec<wbase16>(L"01") == std::string(1, '\x01'));
    assert(strenc<wbase16>(std::string(1, '\xfe')) == L"FE");
    assert(strdec<wbase16>(L"FE") == std::string(1, '\xfe'));
    assert(strenc<wbase16>(std::string(1, '\xff')) == L"FF");
    assert(strdec<wbase16>(L"FF") == std::string(1, '\xff'));

    // test invalid length

    assert_throw(strdec<base16>("0"), stlencoders::invalid_length);
    assert_throw(strdec<base16>("000"), stlencoders::invalid_length);

    // test invalid character

    assert_throw(strdec<base16>("?00"), stlencoders::invalid_character);
    assert_throw(strdec<base16>("0?0"), stlencoders::invalid_character);
    assert_throw(strdec<base16>("0?0"), stlencoders::invalid_character);

    // skip invalid character

    assert(strdec<base16>("?00", make_skip("?")) == std::string(1, '\x00'));
    assert(strdec<base16>("0?0", make_skip("?")) == std::string(1, '\x00'));
    assert(strdec<base16>("00?", make_skip("?")) == std::string(1, '\x00'));

    // skip no characters

    assert_throw(strdec<base16>("?00", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base16>("0?0", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base16>("00?", make_skip("")), stlencoders::invalid_character);

    // test base16 upper/lower variants
    for (base16::int_type i = 0; i != 16; ++i) {
        typedef base16::traits_type traits;

        traits::char_type c = traits::to_char_type(i);
        traits::char_type uc = traits::to_char_type_upper(i);
        traits::char_type lc = traits::to_char_type_lower(i);

        assert(traits::eq(uc, std::toupper(c, std::locale::classic())));
        assert(traits::eq(lc, std::tolower(c, std::locale::classic())));
        assert(traits::eq_int_type(traits::to_int_type(lc), traits::to_int_type(uc)));
    }

    return EXIT_SUCCESS;
}
