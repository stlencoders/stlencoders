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

#ifndef UTIL_HPP
#define UTIL_HPP

#include "xassert.hpp"

#include <cassert>
#include <string>

namespace {
    template<bool F>
    struct predicate {
        template<class T> bool operator()(const T&) { return F; }
    };

    template<class C>
    std::basic_string<typename C::char_type> strenc(const std::string& src)
    {
        typedef typename C::char_type char_type;
        typedef typename std::basic_string<char_type> string_type;
        typedef typename string_type::iterator iterator_type;

        string_type dst(C::max_encode_size(src.size()), '\0');
        iterator_type end = C::encode(src.begin(), src.end(), dst.begin());
        assert(end - dst.begin() <= dst.end() - dst.begin());
        dst.resize(end - dst.begin());
        return dst;
    }

    template<class C>
    std::basic_string<typename C::char_type> strenc(const std::string& src, bool pad)
    {
        typedef typename C::char_type char_type;
        typedef typename std::basic_string<char_type> string_type;
        typedef typename string_type::iterator iterator_type;

        string_type dst(C::max_encode_size(src.size()), '\0');
        iterator_type end = C::encode(src.begin(), src.end(), dst.begin(), pad);
        assert(end - dst.begin() <= dst.end() - dst.begin());
        dst.resize(end - dst.begin());
        return dst;
    }

    template<class C>
    std::string strdec(const std::basic_string<typename C::char_type>& src)
    {
        typedef typename std::string string_type;
        typedef typename std::string::iterator iterator_type;

        string_type dst(C::max_decode_size(src.size()), '\0');
        iterator_type end = C::decode(src.begin(), src.end(), dst.begin());
        assert(end - dst.begin() <= dst.end() - dst.begin());
        dst.resize(end - dst.begin());
        return dst;
    }
}

#endif
