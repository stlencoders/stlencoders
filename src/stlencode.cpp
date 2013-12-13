/*
 * Copyright (c) 2012, 2013 Thomas Kemmer <tkemmer@computer.org>
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

#include "base2.hpp"
#include "base16.hpp"
#include "base32.hpp"
#include "base64.hpp"
#include "iterator.hpp"
#include "traits.hpp"

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#if defined(HAVE_GETOPT_H)
# include <getopt.h>
#elif defined(HAVE_UNISTD_H)
# include <unistd.h>
#else
# include "getopt.hpp"
#endif

template<class Codec, class OutputIterator>
OutputIterator encode(std::istream& is, OutputIterator out)
{
    std::istreambuf_iterator<char> in(is);
    std::istreambuf_iterator<char> end;
    return Codec::encode(in, end, out);
}

template<class Codec, class OutputIterator>
OutputIterator encode(std::istream& is, OutputIterator out, bool pad)
{
    std::istreambuf_iterator<char> in(is);
    std::istreambuf_iterator<char> end;
    return Codec::encode(in, end, out, pad);
}

template<class Codec, class OutputIterator>
OutputIterator fencode(const char* filename, OutputIterator out)
{
    if (!filename || std::strcmp(filename, "-") == 0) {
        return encode<Codec>(std::cin, out);
    }

    std::ifstream is(filename);
    if (!is) {
        throw std::runtime_error("cannot open file");
    }
    return encode<Codec>(is, out);
}

template<class Codec, class OutputIterator>
OutputIterator fencode(const char* filename, OutputIterator out, bool pad)
{
    if (!filename || std::strcmp(filename, "-") == 0) {
        return encode<Codec>(std::cin, out, pad);
    }

    std::ifstream is(filename);
    if (!is) {
        throw std::runtime_error("cannot open file");
    }
    return encode<Codec>(is, out, pad);
}

template<template<class T> class encoding_traits, class OutputIterator>
OutputIterator encode(const std::string& codec, const char* filename,
                      OutputIterator out, bool pad)
{
    using namespace stlencoders;

    if (codec == "base2") {
        typedef base2_traits<char> traits;
        return fencode<base2<char, traits> >(filename, out);
    } else if (codec == "base16") {
        typedef encoding_traits<base16_traits<char> > traits;
        return fencode<base16<char, traits> >(filename, out);
    } else if (codec == "base32") {
        typedef encoding_traits<base32_traits<char> > traits;
        return fencode<base32<char, traits> >(filename, out, pad);
    } else if (codec == "base32hex") {
        typedef encoding_traits<base32hex_traits<char> > traits;
        return fencode<base32<char, traits> >(filename, out, pad);
    } else if (codec == "base64") {
        typedef base64_traits<char> traits;
        return fencode<base64<char, traits> >(filename, out, pad);
    } else if (codec == "base64url") {
        typedef base64url_traits<char> traits;
        return fencode<base64<char, traits> >(filename, out, pad);
    } else {
        throw std::runtime_error("unknown encoding: '" + codec + "'");
    }
}

void usage(std::ostream& os, const char* progname)
{
    os << "Usage: " << progname << " [OPTION]... [FILE]\n"
       << "Encode FILE, or standard input, to standard output.\n"
       << "\n"
       << "  -c NAME    output encoding (default 'base64')\n"
       << "  -l         list supported encoding schemes\n"
       << "  -m         use MIME line breaks (CRLF)\n"
       << "  -n         no padding at the end of encoded data\n"
       << "  -u         use uppercase characters in encoding\n"
       << "  -w COLS    wrap output lines after COLS characters (default 76);\n"
       << "             use 0 to disable line wrapping\n"
       << "\n"
       << "With no FILE, or when FILE is -, read standard input.\n";
}

int main(int argc, char* argv[])
{
    std::string codec = "base64";
    unsigned long wrap = 76;
    const char* endl = "\n";
    bool uppercase = false;
    bool padding = true;

    for (int c; (c = getopt(argc, argv, ":c:lmnuw:")) != -1; ) {
        switch (c) {
        case 'c':
            codec = optarg;
            break;

        case 'l':
            std::cout << "base2 base16 base32 base32hex base64 base64url\n";
            return EXIT_SUCCESS;

        case 'm':
            endl = "\r\n";
            break;

        case 'n':
            padding = false;
            break;

        case 'u':
            uppercase = true;
            break;

        case 'w':
            wrap = std::strtoul(optarg, 0, 0);
            break;

        default:
            usage(std::cout, argv[0]);
            return EXIT_FAILURE;
        }
    }

    const char* filename = optind != argc ? argv[optind] : "-";

    std::ostreambuf_iterator<char> out(std::cout);

    try {
        using namespace stlencoders;

        if (uppercase) {
            encode<upper_char_encoding_traits>(
                codec, filename, line_wrapper(out, wrap, endl), padding
                );
        } else {
            encode<lower_char_encoding_traits>(
                codec, filename, line_wrapper(out, wrap, endl), padding
                );
        }

        if (wrap != 0) {
            std::cout << endl;
        }
    } catch (std::exception& e) {
        std::cerr << argv[0] << ": " << filename << ": " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
