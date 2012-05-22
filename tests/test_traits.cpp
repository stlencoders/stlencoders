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

#include <stlencoders/traits.hpp>

#include <cassert>
#include <cstdlib>
#include <string>

template<class charT> struct identity_traits;

template<>
struct identity_traits<char>
: public std::char_traits<char> {
    static int_type inv() {
        return eof();
    }
};

template<>
struct identity_traits<wchar_t>
: public stlencoders::portable_wchar_encoding_traits<identity_traits<char> > {
};

int main()
{
    typedef identity_traits<wchar_t> traits;

    assert(traits::eq(L'A', traits::to_char_type(traits::to_int_type(L'A'))));
    assert(traits::eq(L'B', traits::to_char_type(traits::to_int_type(L'B'))));
    assert(traits::eq(L'C', traits::to_char_type(traits::to_int_type(L'C'))));
    assert(traits::eq(L'D', traits::to_char_type(traits::to_int_type(L'D'))));
    assert(traits::eq(L'E', traits::to_char_type(traits::to_int_type(L'E'))));
    assert(traits::eq(L'F', traits::to_char_type(traits::to_int_type(L'F'))));
    assert(traits::eq(L'G', traits::to_char_type(traits::to_int_type(L'G'))));
    assert(traits::eq(L'H', traits::to_char_type(traits::to_int_type(L'H'))));
    assert(traits::eq(L'I', traits::to_char_type(traits::to_int_type(L'I'))));
    assert(traits::eq(L'J', traits::to_char_type(traits::to_int_type(L'J'))));
    assert(traits::eq(L'K', traits::to_char_type(traits::to_int_type(L'K'))));
    assert(traits::eq(L'L', traits::to_char_type(traits::to_int_type(L'L'))));
    assert(traits::eq(L'M', traits::to_char_type(traits::to_int_type(L'M'))));
    assert(traits::eq(L'N', traits::to_char_type(traits::to_int_type(L'N'))));
    assert(traits::eq(L'O', traits::to_char_type(traits::to_int_type(L'O'))));
    assert(traits::eq(L'P', traits::to_char_type(traits::to_int_type(L'P'))));
    assert(traits::eq(L'Q', traits::to_char_type(traits::to_int_type(L'Q'))));
    assert(traits::eq(L'R', traits::to_char_type(traits::to_int_type(L'R'))));
    assert(traits::eq(L'S', traits::to_char_type(traits::to_int_type(L'S'))));
    assert(traits::eq(L'T', traits::to_char_type(traits::to_int_type(L'T'))));
    assert(traits::eq(L'U', traits::to_char_type(traits::to_int_type(L'U'))));
    assert(traits::eq(L'V', traits::to_char_type(traits::to_int_type(L'V'))));
    assert(traits::eq(L'W', traits::to_char_type(traits::to_int_type(L'W'))));
    assert(traits::eq(L'X', traits::to_char_type(traits::to_int_type(L'X'))));
    assert(traits::eq(L'Y', traits::to_char_type(traits::to_int_type(L'Y'))));
    assert(traits::eq(L'Z', traits::to_char_type(traits::to_int_type(L'Z'))));
    assert(traits::eq(L'a', traits::to_char_type(traits::to_int_type(L'a'))));
    assert(traits::eq(L'b', traits::to_char_type(traits::to_int_type(L'b'))));
    assert(traits::eq(L'c', traits::to_char_type(traits::to_int_type(L'c'))));
    assert(traits::eq(L'd', traits::to_char_type(traits::to_int_type(L'd'))));
    assert(traits::eq(L'e', traits::to_char_type(traits::to_int_type(L'e'))));
    assert(traits::eq(L'f', traits::to_char_type(traits::to_int_type(L'f'))));
    assert(traits::eq(L'g', traits::to_char_type(traits::to_int_type(L'g'))));
    assert(traits::eq(L'h', traits::to_char_type(traits::to_int_type(L'h'))));
    assert(traits::eq(L'i', traits::to_char_type(traits::to_int_type(L'i'))));
    assert(traits::eq(L'j', traits::to_char_type(traits::to_int_type(L'j'))));
    assert(traits::eq(L'k', traits::to_char_type(traits::to_int_type(L'k'))));
    assert(traits::eq(L'l', traits::to_char_type(traits::to_int_type(L'l'))));
    assert(traits::eq(L'm', traits::to_char_type(traits::to_int_type(L'm'))));
    assert(traits::eq(L'n', traits::to_char_type(traits::to_int_type(L'n'))));
    assert(traits::eq(L'o', traits::to_char_type(traits::to_int_type(L'o'))));
    assert(traits::eq(L'p', traits::to_char_type(traits::to_int_type(L'p'))));
    assert(traits::eq(L'q', traits::to_char_type(traits::to_int_type(L'q'))));
    assert(traits::eq(L'r', traits::to_char_type(traits::to_int_type(L'r'))));
    assert(traits::eq(L's', traits::to_char_type(traits::to_int_type(L's'))));
    assert(traits::eq(L't', traits::to_char_type(traits::to_int_type(L't'))));
    assert(traits::eq(L'u', traits::to_char_type(traits::to_int_type(L'u'))));
    assert(traits::eq(L'v', traits::to_char_type(traits::to_int_type(L'v'))));
    assert(traits::eq(L'w', traits::to_char_type(traits::to_int_type(L'w'))));
    assert(traits::eq(L'x', traits::to_char_type(traits::to_int_type(L'x'))));
    assert(traits::eq(L'y', traits::to_char_type(traits::to_int_type(L'y'))));
    assert(traits::eq(L'z', traits::to_char_type(traits::to_int_type(L'z'))));
    assert(traits::eq(L'0', traits::to_char_type(traits::to_int_type(L'0'))));
    assert(traits::eq(L'1', traits::to_char_type(traits::to_int_type(L'1'))));
    assert(traits::eq(L'2', traits::to_char_type(traits::to_int_type(L'2'))));
    assert(traits::eq(L'3', traits::to_char_type(traits::to_int_type(L'3'))));
    assert(traits::eq(L'4', traits::to_char_type(traits::to_int_type(L'4'))));
    assert(traits::eq(L'5', traits::to_char_type(traits::to_int_type(L'5'))));
    assert(traits::eq(L'6', traits::to_char_type(traits::to_int_type(L'6'))));
    assert(traits::eq(L'7', traits::to_char_type(traits::to_int_type(L'7'))));
    assert(traits::eq(L'8', traits::to_char_type(traits::to_int_type(L'8'))));
    assert(traits::eq(L'9', traits::to_char_type(traits::to_int_type(L'9'))));
    assert(traits::eq(L'!', traits::to_char_type(traits::to_int_type(L'!'))));
    assert(traits::eq(L'\"', traits::to_char_type(traits::to_int_type(L'\"'))));
    assert(traits::eq(L'#', traits::to_char_type(traits::to_int_type(L'#'))));
    assert(traits::eq(L'%', traits::to_char_type(traits::to_int_type(L'%'))));
    assert(traits::eq(L'&', traits::to_char_type(traits::to_int_type(L'&'))));
    assert(traits::eq(L'\'', traits::to_char_type(traits::to_int_type(L'\''))));
    assert(traits::eq(L'(', traits::to_char_type(traits::to_int_type(L'('))));
    assert(traits::eq(L')', traits::to_char_type(traits::to_int_type(L')'))));
    assert(traits::eq(L'*', traits::to_char_type(traits::to_int_type(L'*'))));
    assert(traits::eq(L'+', traits::to_char_type(traits::to_int_type(L'+'))));
    assert(traits::eq(L',', traits::to_char_type(traits::to_int_type(L','))));
    assert(traits::eq(L'-', traits::to_char_type(traits::to_int_type(L'-'))));
    assert(traits::eq(L'.', traits::to_char_type(traits::to_int_type(L'.'))));
    assert(traits::eq(L'/', traits::to_char_type(traits::to_int_type(L'/'))));
    assert(traits::eq(L':', traits::to_char_type(traits::to_int_type(L':'))));
    assert(traits::eq(L';', traits::to_char_type(traits::to_int_type(L';'))));
    assert(traits::eq(L'<', traits::to_char_type(traits::to_int_type(L'<'))));
    assert(traits::eq(L'=', traits::to_char_type(traits::to_int_type(L'='))));
    assert(traits::eq(L'>', traits::to_char_type(traits::to_int_type(L'>'))));
    assert(traits::eq(L'?', traits::to_char_type(traits::to_int_type(L'?'))));
    assert(traits::eq(L'[', traits::to_char_type(traits::to_int_type(L'['))));
    assert(traits::eq(L'\\', traits::to_char_type(traits::to_int_type(L'\\'))));
    assert(traits::eq(L']', traits::to_char_type(traits::to_int_type(L']'))));
    assert(traits::eq(L'^', traits::to_char_type(traits::to_int_type(L'^'))));
    assert(traits::eq(L'_', traits::to_char_type(traits::to_int_type(L'_'))));
    assert(traits::eq(L'{', traits::to_char_type(traits::to_int_type(L'{'))));
    assert(traits::eq(L'|', traits::to_char_type(traits::to_int_type(L'|'))));
    assert(traits::eq(L'}', traits::to_char_type(traits::to_int_type(L'}'))));
    assert(traits::eq(L'~', traits::to_char_type(traits::to_int_type(L'~'))));

    return EXIT_SUCCESS;
}
