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

#ifndef UTIL_HPP
#define UTIL_HPP

#include "xassert.hpp"

#include <cassert>
#include <string>

namespace {
    template<class C>
    std::basic_string<typename C::char_type> strenc(const std::string& src)
    {
        typedef typename C::char_type char_type;
        typedef std::basic_string<char_type> string_type;
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
        typedef std::basic_string<char_type> string_type;
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
        typedef std::string string_type;
        typedef std::string::iterator iterator_type;

        string_type dst(C::max_decode_size(src.size()), '\0');
        iterator_type end = C::decode(src.begin(), src.end(), dst.begin());
        assert(end - dst.begin() <= dst.end() - dst.begin());
        dst.resize(end - dst.begin());
        return dst;
    }

    template<class C, class Predicate>
    std::string strdec(const std::basic_string<typename C::char_type>& src, Predicate pred)
    {
        typedef std::string string_type;
        typedef std::string::iterator iterator_type;

        string_type dst(C::max_decode_size(src.size()), '\0');
        iterator_type end = C::decode(src.begin(), src.end(), dst.begin(), pred);
        assert(end - dst.begin() <= dst.end() - dst.begin());
        dst.resize(end - dst.begin());
        return dst;
    }

    template<class charT>
    class skip {
    public:
        typedef charT char_type;
        typedef std::basic_string<charT> string_type;

    public:
        skip(const charT* s) : skipped(s) { }

        bool operator()(const charT& c) {
            return skipped.find(c) != string_type::npos;
        }

    private:
        string_type skipped;
    };

    template<class charT>
    inline skip<charT> make_skip(const charT* s)
    {
        return skip<charT>(s);
    }
}

#endif
