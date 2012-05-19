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

#include <stlencoders/base32.hpp>

#include <cassert>
#include <cstdlib>
#include <locale>
#include <string>

#include "util.hpp"

int main()
{
    typedef stlencoders::base32<char> base32;
    typedef stlencoders::base32<wchar_t> wbase32;

    typedef stlencoders::base32<char, stlencoders::base32hex_traits<char> > base32hex;
    typedef stlencoders::base32<wchar_t, stlencoders::base32hex_traits<wchar_t> > wbase32hex;

    // RFC 4648 test vectors

    assert(strenc<base32>("") == "");
    assert(strenc<base32>("f") == "MY======");
    assert(strenc<base32>("fo") == "MZXQ====");
    assert(strenc<base32>("foo") == "MZXW6===");
    assert(strenc<base32>("foob") == "MZXW6YQ=");
    assert(strenc<base32>("fooba") == "MZXW6YTB");
    assert(strenc<base32>("foobar") == "MZXW6YTBOI======");

    assert(strdec<base32>("") == "");
    assert(strdec<base32>("MY======") == "f");
    assert(strdec<base32>("MZXQ====") == "fo");
    assert(strdec<base32>("MZXW6===") == "foo");
    assert(strdec<base32>("MZXW6YQ=") == "foob");
    assert(strdec<base32>("MZXW6YTB") == "fooba");
    assert(strdec<base32>("MZXW6YTBOI======") == "foobar");

    assert(strenc<base32hex>("") == "");
    assert(strenc<base32hex>("f") == "CO======");
    assert(strenc<base32hex>("fo") == "CPNG====");
    assert(strenc<base32hex>("foo") == "CPNMU===");
    assert(strenc<base32hex>("foob") == "CPNMUOG=");
    assert(strenc<base32hex>("fooba") == "CPNMUOJ1");
    assert(strenc<base32hex>("foobar") == "CPNMUOJ1E8======");

    assert(strdec<base32hex>("") == "");
    assert(strdec<base32hex>("CO======") == "f");
    assert(strdec<base32hex>("CPNG====") == "fo");
    assert(strdec<base32hex>("CPNMU===") == "foo");
    assert(strdec<base32hex>("CPNMUOG=") == "foob");
    assert(strdec<base32hex>("CPNMUOJ1") == "fooba");
    assert(strdec<base32hex>("CPNMUOJ1E8======") == "foobar");

    // RFC 4648 test vectors - wide characters

    assert(strenc<wbase32>("") == L"");
    assert(strenc<wbase32>("f") == L"MY======");
    assert(strenc<wbase32>("fo") == L"MZXQ====");
    assert(strenc<wbase32>("foo") == L"MZXW6===");
    assert(strenc<wbase32>("foob") == L"MZXW6YQ=");
    assert(strenc<wbase32>("fooba") == L"MZXW6YTB");
    assert(strenc<wbase32>("foobar") == L"MZXW6YTBOI======");

    assert(strdec<wbase32>(L"") == "");
    assert(strdec<wbase32>(L"MY======") == "f");
    assert(strdec<wbase32>(L"MZXQ====") == "fo");
    assert(strdec<wbase32>(L"MZXW6===") == "foo");
    assert(strdec<wbase32>(L"MZXW6YQ=") == "foob");
    assert(strdec<wbase32>(L"MZXW6YTB") == "fooba");
    assert(strdec<wbase32>(L"MZXW6YTBOI======") == "foobar");

    assert(strenc<wbase32hex>("") == L"");
    assert(strenc<wbase32hex>("f") == L"CO======");
    assert(strenc<wbase32hex>("fo") == L"CPNG====");
    assert(strenc<wbase32hex>("foo") == L"CPNMU===");
    assert(strenc<wbase32hex>("foob") == L"CPNMUOG=");
    assert(strenc<wbase32hex>("fooba") == L"CPNMUOJ1");
    assert(strenc<wbase32hex>("foobar") == L"CPNMUOJ1E8======");

    assert(strdec<wbase32hex>(L"") == "");
    assert(strdec<wbase32hex>(L"CO======") == "f");
    assert(strdec<wbase32hex>(L"CPNG====") == "fo");
    assert(strdec<wbase32hex>(L"CPNMU===") == "foo");
    assert(strdec<wbase32hex>(L"CPNMUOG=") == "foob");
    assert(strdec<wbase32hex>(L"CPNMUOJ1") == "fooba");
    assert(strdec<wbase32hex>(L"CPNMUOJ1E8======") == "foobar");

    // RFC 4648 test vectors - no padding

    assert(strenc<base32>("", false) == "");
    assert(strenc<base32>("f", false) == "MY");
    assert(strenc<base32>("fo", false) == "MZXQ");
    assert(strenc<base32>("foo", false) == "MZXW6");
    assert(strenc<base32>("foob", false) == "MZXW6YQ");
    assert(strenc<base32>("fooba", false) == "MZXW6YTB");
    assert(strenc<base32>("foobar", false) == "MZXW6YTBOI");

    assert(strdec<base32>("") == "");
    assert(strdec<base32>("MY") == "f");
    assert(strdec<base32>("MZXQ") == "fo");
    assert(strdec<base32>("MZXW6") == "foo");
    assert(strdec<base32>("MZXW6YQ") == "foob");
    assert(strdec<base32>("MZXW6YTB") == "fooba");
    assert(strdec<base32>("MZXW6YTBOI") == "foobar");

    assert(strenc<base32hex>("", false) == "");
    assert(strenc<base32hex>("f", false) == "CO");
    assert(strenc<base32hex>("fo", false) == "CPNG");
    assert(strenc<base32hex>("foo", false) == "CPNMU");
    assert(strenc<base32hex>("foob", false) == "CPNMUOG");
    assert(strenc<base32hex>("fooba", false) == "CPNMUOJ1");
    assert(strenc<base32hex>("foobar", false) == "CPNMUOJ1E8");

    assert(strdec<base32hex>("") == "");
    assert(strdec<base32hex>("CO") == "f");
    assert(strdec<base32hex>("CPNG") == "fo");
    assert(strdec<base32hex>("CPNMU") == "foo");
    assert(strdec<base32hex>("CPNMUOG") == "foob");
    assert(strdec<base32hex>("CPNMUOJ1") == "fooba");
    assert(strdec<base32hex>("CPNMUOJ1E8") == "foobar");

    // RFC 4648 test vectors - decoding predicate

    assert(strdec<base32>("", make_skip("")) == "");
    assert(strdec<base32>("MY======", make_skip("")) == "f");
    assert(strdec<base32>("MZXQ====", make_skip("")) == "fo");
    assert(strdec<base32>("MZXW6===", make_skip("")) == "foo");
    assert(strdec<base32>("MZXW6YQ=", make_skip("")) == "foob");
    assert(strdec<base32>("MZXW6YTB", make_skip("")) == "fooba");
    assert(strdec<base32>("MZXW6YTBOI======", make_skip("")) == "foobar");

    assert(strdec<wbase32>(L"", make_skip(L"")) == "");
    assert(strdec<wbase32>(L"MY======", make_skip(L"")) == "f");
    assert(strdec<wbase32>(L"MZXQ====", make_skip(L"")) == "fo");
    assert(strdec<wbase32>(L"MZXW6===", make_skip(L"")) == "foo");
    assert(strdec<wbase32>(L"MZXW6YQ=", make_skip(L"")) == "foob");
    assert(strdec<wbase32>(L"MZXW6YTB", make_skip(L"")) == "fooba");
    assert(strdec<wbase32>(L"MZXW6YTBOI======", make_skip(L"")) == "foobar");

    assert(strdec<base32hex>("", make_skip("")) == "");
    assert(strdec<base32hex>("CO======", make_skip("")) == "f");
    assert(strdec<base32hex>("CPNG====", make_skip("")) == "fo");
    assert(strdec<base32hex>("CPNMU===", make_skip("")) == "foo");
    assert(strdec<base32hex>("CPNMUOG=", make_skip("")) == "foob");
    assert(strdec<base32hex>("CPNMUOJ1", make_skip("")) == "fooba");
    assert(strdec<base32hex>("CPNMUOJ1E8======", make_skip("")) == "foobar");

    assert(strdec<wbase32hex>(L"", make_skip(L"")) == "");
    assert(strdec<wbase32hex>(L"CO======", make_skip(L"")) == "f");
    assert(strdec<wbase32hex>(L"CPNG====", make_skip(L"")) == "fo");
    assert(strdec<wbase32hex>(L"CPNMU===", make_skip(L"")) == "foo");
    assert(strdec<wbase32hex>(L"CPNMUOG=", make_skip(L"")) == "foob");
    assert(strdec<wbase32hex>(L"CPNMUOJ1", make_skip(L"")) == "fooba");
    assert(strdec<wbase32hex>(L"CPNMUOJ1E8======", make_skip(L"")) == "foobar");

    // test some special bit patterns

    assert(strenc<base32>(std::string(5, '\x00')) == "AAAAAAAA");
    assert(strdec<base32>("AAAAAAAA") == std::string(5, '\x00'));
    assert(strenc<base32>(std::string(5, '\xff')) == "77777777");
    assert(strdec<base32>("77777777") == std::string(5, '\xff'));

    assert(strenc<wbase32>(std::string(5, '\x00')) == L"AAAAAAAA");
    assert(strdec<wbase32>(L"AAAAAAAA") == std::string(5, '\x00'));
    assert(strenc<wbase32>(std::string(5, '\xff')) == L"77777777");
    assert(strdec<wbase32>(L"77777777") == std::string(5, '\xff'));

    assert(strenc<base32hex>(std::string(5, '\x00')) == "00000000");
    assert(strdec<base32hex>("00000000") == std::string(5, '\x00'));
    assert(strenc<base32hex>(std::string(5, '\xff')) == "VVVVVVVV");
    assert(strdec<base32hex>("VVVVVVVV") == std::string(5, '\xff'));

    assert(strenc<wbase32hex>(std::string(5, '\x00')) == L"00000000");
    assert(strdec<wbase32hex>(L"00000000") == std::string(5, '\x00'));
    assert(strenc<wbase32hex>(std::string(5, '\xff')) == L"VVVVVVVV");
    assert(strdec<wbase32hex>(L"VVVVVVVV") == std::string(5, '\xff'));

    // test invalid length

    assert_throw(strdec<base32>("A"), stlencoders::invalid_length);
    assert_throw(strdec<base32>("AAA"), stlencoders::invalid_length);
    assert_throw(strdec<base32>("AAAAAA"), stlencoders::invalid_length);
    assert_throw(strdec<base32>("AAAAAAAAA"), stlencoders::invalid_length);

    assert_throw(strdec<base32>("A======="), stlencoders::invalid_length);
    assert_throw(strdec<base32>("AAA====="), stlencoders::invalid_length);
    assert_throw(strdec<base32>("AAAAAA=="), stlencoders::invalid_length);
    assert_throw(strdec<base32>("AAAAAAAAA======="), stlencoders::invalid_length);

    // test invalid character

    assert_throw(strdec<base32>("?AAAAAAAA"), stlencoders::invalid_character);
    assert_throw(strdec<base32>("A?AAAAAAA"), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AA?AAAAAA"), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAA?AAAAA"), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAA?AAAA"), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAAA?AAA"), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAAAA?AA"), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAAAAA?A"), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAAAAAA?"), stlencoders::invalid_character);

    // skip invalid character

    assert(strdec<base32>("?AAAAAAAA", make_skip("?")) == std::string(5, '\x00'));
    assert(strdec<base32>("A?AAAAAAA", make_skip("?")) == std::string(5, '\x00'));
    assert(strdec<base32>("AA?AAAAAA", make_skip("?")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAA?AAAAA", make_skip("?")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAA?AAAA", make_skip("?")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAAA?AAA", make_skip("?")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAAAA?AA", make_skip("?")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAAAAA?A", make_skip("?")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAAAAAA?", make_skip("?")) == std::string(5, '\x00'));

    // skip padding character

    assert(strdec<base32>("=AAAAAAAA", make_skip("=")) == std::string(5, '\x00'));
    assert(strdec<base32>("A=AAAAAAA", make_skip("=")) == std::string(5, '\x00'));
    assert(strdec<base32>("AA=AAAAAA", make_skip("=")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAA=AAAAA", make_skip("=")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAA=AAAA", make_skip("=")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAAA=AAA", make_skip("=")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAAAA=AA", make_skip("=")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAAAAA=A", make_skip("=")) == std::string(5, '\x00'));
    assert(strdec<base32>("AAAAAAAA=", make_skip("=")) == std::string(5, '\x00'));

    // skip no characters

    assert_throw(strdec<base32>("?AAAAAAAA", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base32>("A?AAAAAAA", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AA?AAAAAA", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAA?AAAAA", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAA?AAAA", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAAA?AAA", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAAAA?AA", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAAAAA?A", make_skip("")), stlencoders::invalid_character);
    assert_throw(strdec<base32>("AAAAAAAA?", make_skip("")), stlencoders::invalid_character);

    // test base32 upper/lower variants
    for (int i = 0; i != 32; ++i) {
        typedef base32::traits_type traits;

        char c = traits::to_char_type(i);
        char uc = traits::to_char_type_upper(i);
        char lc = traits::to_char_type_lower(i);

        assert(traits::eq(uc, std::toupper(c, std::locale::classic())));
        assert(traits::eq(lc, std::tolower(c, std::locale::classic())));
        assert(traits::eq_int_type(traits::to_int_type(lc), traits::to_int_type(uc)));
    }

    // test base32hex upper/lower variants
    for (int i = 0; i != 32; ++i) {
        typedef base32hex::traits_type traits;

        char c = traits::to_char_type(i);
        char uc = traits::to_char_type_upper(i);
        char lc = traits::to_char_type_lower(i);

        assert(traits::eq(uc, std::toupper(c, std::locale::classic())));
        assert(traits::eq(lc, std::tolower(c, std::locale::classic())));
        assert(traits::eq_int_type(traits::to_int_type(lc), traits::to_int_type(uc)));
    }

    return EXIT_SUCCESS;
}
