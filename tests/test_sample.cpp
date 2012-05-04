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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stlencoders/base16.hpp>
#include <stlencoders/base32.hpp>
#include <stlencoders/base64.hpp>
#include <stlencoders/iterator.hpp>
#include <stlencoders/traits.hpp>

#include <functional>
#include <iostream>
#include <iterator>
#include <locale>
#include <string>
#include <vector>

#ifdef STDCXX_TR1_HEADERS
# include <tr1/functional>
#endif

void pipe_sample()
{
    std::istreambuf_iterator<char> in(std::cin);
    std::istreambuf_iterator<char> end;
    std::ostreambuf_iterator<char> out(std::cout);

    stlencoders::base64<char>::encode(in, end, out);
}

void mime_sample()
{
    std::istreambuf_iterator<char> in(std::cin);
    std::istreambuf_iterator<char> end;
    std::ostreambuf_iterator<char> out(std::cout);

    stlencoders::base64<char>::encode(in, end, stlencoders::line_wrapper(out, 76, "\r\n"));
}

void skip_sample()
{
    std::istreambuf_iterator<char> in(std::cin);
    std::istreambuf_iterator<char> end;
    std::ostreambuf_iterator<char> out(std::cout);

#ifdef STDCXX_TR1_HEADERS
    using namespace std::tr1::placeholders;
    stlencoders::base64<char>::decode(in, end, out, std::tr1::bind(std::isspace<char>, _1, std::locale()));
#else
    stlencoders::base64<char>::decode(in, end, out, std::bind2nd(std::ptr_fun(std::isspace<char>), std::locale()));
#endif
}

void wstring_sample()
{
    typedef unsigned char uint8_t;

    std::wstring s(L"Zm9vYmFy");
    std::vector<uint8_t> v;

    stlencoders::base64<char>::decode(s.begin(), s.end(), std::back_inserter(v));
}


int main()
{
    // checks compilation only
    return 0;
}
