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
#include <stlencoders/base16.hpp>
#include <stlencoders/base32.hpp>
#include <stlencoders/base64.hpp>

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_MODP_B2_H
# include <modp_b2.h>
#endif

#ifdef HAVE_MODP_B16_H
# include <modp_b16.h>
#endif

#ifdef HAVE_MODP_B64_H
# include <modp_b64.h>
#endif

#ifdef HAVE_MODP_B64W_H
# include <modp_b64w.h>
#endif

#ifdef HAVE_APR_1_APR_BASE64_H
# include <apr-1/apr_base64.h>
#endif

#if defined(HAVE_GETOPT_H)
# include <getopt.h>
#elif defined(HAVE_UNISTD_H)
# include <unistd.h>
#else
# include "getopt.hpp"
#endif

namespace {
    struct base {
        typedef char char_type;

        typedef unsigned char int_type;
    };

#ifdef HAVE_MODP_B2_H
    struct modp_b2 : public base {
        static char_type* encode(const int_type* first, const int_type* last,
                                 char_type* result)
        {
            const char* src = reinterpret_cast<const char*>(first);
            return result + modp_b2_encode(result, src, last - first);
        }

        static int_type* decode(const char_type* first, const char_type* last,
                                int_type* result)
        {
            char* dst = reinterpret_cast<char*>(result);
            return result + modp_b2_decode(dst, first, last - first);
        }

        static std::size_t max_encode_size(std::size_t n) {
            return modp_b2_encode_len(n);
        }

        static std::size_t max_decode_size(std::size_t n) {
            return modp_b2_decode_len(n);
        }
    };
#endif

#ifdef HAVE_MODP_B16_H
    struct modp_b16 : public base {
        static char_type* encode(const int_type* first, const int_type* last,
                                 char_type* result)
        {
            const char* src = reinterpret_cast<const char*>(first);
            return result + modp_b16_encode(result, src, last - first);
        }

        static int_type* decode(const char_type* first, const char_type* last,
                                int_type* result)
        {
            char* dst = reinterpret_cast<char*>(result);
            return result + modp_b16_decode(dst, first, last - first);
        }

        static std::size_t max_encode_size(std::size_t n) {
            return modp_b16_encode_len(n);
        }

        static std::size_t max_decode_size(std::size_t n) {
            return modp_b16_decode_len(n);
        }
    };
#endif

#ifdef HAVE_MODP_B64_H
    struct modp_b64 : public base {
        static char_type* encode(const int_type* first, const int_type* last,
                                 char_type* result)
        {
            const char* src = reinterpret_cast<const char*>(first);
            return result + modp_b64_encode(result, src, last - first);
        }

        static int_type* decode(const char_type* first, const char_type* last,
                                int_type* result)
        {
            char* dst = reinterpret_cast<char*>(result);
            return result + modp_b64_decode(dst, first, last - first);
        }

        static std::size_t max_encode_size(std::size_t n) {
            return modp_b64_encode_len(n);
        }

        static std::size_t max_decode_size(std::size_t n) {
            return modp_b64_decode_len(n);
        }
    };
#endif

#ifdef HAVE_MODP_B64W_H
    struct modp_b64w : public base {
        static char_type* encode(const int_type* first, const int_type* last,
                                 char_type* result)
        {
            const char* src = reinterpret_cast<const char*>(first);
            return result + modp_b64w_encode(result, src, last - first);
        }

        static int_type* decode(const char_type* first, const char_type* last,
                                int_type* result)
        {
            char* dst = reinterpret_cast<char*>(result);
            return result + modp_b64w_decode(dst, first, last - first);
        }

        static std::size_t max_encode_size(std::size_t n) {
            return modp_b64w_encode_len(n);
        }

        static std::size_t max_decode_size(std::size_t n) {
            return modp_b64w_decode_len(n);
        }
    };
#endif

#ifdef HAVE_APR_1_APR_BASE64_H
    struct apr_base64 : public base {
        static char_type* encode(const int_type* first, const int_type* last,
                                 char_type* result)
        {
            return result + apr_base64_encode_binary(result, first, last - first);
        }

        static int_type* decode(const char_type* first, const char_type* last,
                                int_type* result)
        {
            return result + apr_base64_decode_binary(result, first);
        }

        static std::size_t max_encode_size(std::size_t n) {
            return apr_base64_encode_len(n);
        }

        static std::size_t max_decode_size(std::size_t n) {
            // return apr_base64_decode_len(s);
            return stlencoders::base64<char>::max_decode_size(n);
        }
    };
#endif

    std::string fmtclock(double t, int prec = 2)
    {
        static const double clk_tck = CLOCKS_PER_SEC;

        std::ostringstream os;
        os << std::fixed << std::setprecision(prec);

        double secs = t / clk_tck;

        if (secs >= 1.0) {
            os << secs << "s";
        } else if (1e3 * secs >= 1.0) {
            os << 1e3 * secs << "ms";
        } else if (1e6 * secs >= 1.0) {
            os << 1e6 * secs << "us";
        } else {
            os << 1e9 * secs << "ns";
        }
        return os.str();
    }
}

const std::size_t samples[] = { 16, 256, 4096, 65536, 1048576, 0 };

const int maxsize = 1048576;

const int headlen = 25;
const int timelen = 10;

struct chargen {
    chargen(int seed = 0) {
        std::srand(seed);
    }

    char operator()() const {
        return static_cast<char>(std::rand());
    }
};

template<class Codec>
std::clock_t time_encode(
    const std::vector<unsigned char>& src,
    std::vector<typename Codec::char_type>& dst,
    unsigned long n
    )
{
    std::clock_t t0 = std::clock();
    for (unsigned long i = 0; i != n; ++i) {
        Codec::encode(&src[0], &src[0] + src.size(), &dst[0]);
    }
    return std::clock() - t0;
}

template<class Codec>
std::clock_t time_decode(
    const std::vector<typename Codec::char_type>& src,
    std::vector<unsigned char>& dst,
    unsigned long n
    )
{
    std::clock_t t0 = std::clock();
    for (unsigned long i = 0; i != n; ++i) {
        Codec::decode(&src[0], &src[0] + src.size(), &dst[0]);
    }
    return std::clock() - t0;
}

template<class Codec>
void run(std::ostream& os, const char* prefix, unsigned long minruns)
{
    typedef typename Codec::char_type char_type;

    os << std::setw(headlen - 8) << prefix << "encode: " << std::flush;
    for (const std::size_t* psize = samples; *psize; ++psize) {
        std::size_t n = *psize;
        unsigned long nruns = minruns * maxsize / n;

        std::vector<unsigned char> src(n);
        std::generate(src.begin(), src.end(), chargen());

        std::vector<char_type> enc(Codec::max_encode_size(n));
        std::clock_t t = time_encode<Codec>(src, enc, nruns);

        os << std::setw(timelen) << fmtclock(double(t) / nruns) << std::flush;
    }
    os << std::endl;

    os << std::setw(headlen - 8) << prefix << "decode: " << std::flush;
    for (const std::size_t* psize = samples; *psize; ++psize) {
        std::size_t n = *psize;
        unsigned long nruns = minruns * maxsize / n;

        std::vector<unsigned char> src(n);
        std::generate(src.begin(), src.end(), chargen());

        std::vector<char_type> enc(Codec::max_encode_size(n));
        enc.resize(Codec::encode(&src[0], &src[0] + src.size(), &enc[0]) - &enc[0]);

        std::vector<unsigned char> dec(Codec::max_decode_size(enc.size()));
        std::clock_t t = time_decode<Codec>(enc, dec, nruns);

        os << std::setw(timelen) << fmtclock(double(t) / nruns) << std::flush;
    }
    os << std::endl;
}

void header(std::ostream& os, const char* s)
{
    os << std::setw(headlen - 2) << s << ": ";
    for (const std::size_t* psize = samples; *psize; ++psize) {
        os << std::setw(timelen) << *psize;
    }
    os << std::endl;

    os << std::string(headlen, '=');
    for (const std::size_t* psize = samples; *psize; ++psize) {
        os << std::string(timelen, '=');
    }
    os << std::endl;
}

void usage(std::ostream& os, const char* progname)
{
    os << "Usage: " << progname << " [OPTION]... [ENCODING]...\n"
       << "stlencoders performance test.\n"
       << "\n"
#if defined(HAVE_MODP_B64_H) || defined(HAVE_APR_1_APR_BASE64_H)
       << "  -a         include alternative implementations\n"
#endif
       << "  -l         list supported encoding schemes\n"
       << "  -n NRUNS   number of iterations per test (default 100)\n"
       << "  -w         include wide character encodings\n";
}

int main(int argc, char* argv[])
{
    bool all = false;
    bool wchar = false;
    unsigned long nruns = 100;

    for (int c; (c = getopt(argc, argv, ":aln:w")) != -1; ) {
        switch (c) {
        case 'a':
            all = true;
            break;

        case 'l':
            std::cout << "base2 base16 base32 base32hex base64 base64url\n";
            return EXIT_SUCCESS;

        case 'n':
            nruns = std::strtoul(optarg, 0, 0);
            break;

        case 'w':
            wchar = true;
            break;

        default:
            usage(std::cout, argv[0]);
            return EXIT_FAILURE;
        }
    }

    std::vector<std::string> args;
    if (optind == argc) {
        args.push_back("base16");
        args.push_back("base32");
        args.push_back("base64");
    } else {
        args.assign(&argv[optind], &argv[argc]);
    }

    std::cout << std::fixed;

    header(std::cout, "Input size [bytes]");

    using namespace stlencoders;

    if (std::find(args.begin(), args.end(), "base2") != args.end()) {
        typedef stlencoders::base2<char> base2;
    	run<base2>(std::cout, "base2<char>::", nruns);
    }

    if (std::find(args.begin(), args.end(), "base16") != args.end()) {
        typedef stlencoders::base16<char> base16;
    	run<base16>(std::cout, "base16<char>::", nruns);
    }

    if (std::find(args.begin(), args.end(), "base32") != args.end()) {
        typedef stlencoders::base32<char> base32;
    	run<base32>(std::cout, "base32<char>::", nruns);
    }

    if (std::find(args.begin(), args.end(), "base64") != args.end()) {
        typedef stlencoders::base64<char> base64;
    	run<base64>(std::cout, "base64<char>::", nruns);
    }

    if (std::find(args.begin(), args.end(), "base32hex") != args.end()) {
        typedef stlencoders::base32hex_traits<char> traits;
        typedef stlencoders::base32<char, traits> base32hex;
    	run<base32hex>(std::cout, "base32hex<char>::", nruns);
    }

    if (std::find(args.begin(), args.end(), "base64url") != args.end()) {
        typedef stlencoders::base64url_traits<char> traits;
        typedef stlencoders::base64<char, traits> base64url;
    	run<base64url>(std::cout, "base64url<char>::", nruns);
    }

    if (wchar) {
        if (std::find(args.begin(), args.end(), "base2") != args.end()) {
            typedef stlencoders::base2<wchar_t> base2;
            run<base2>(std::cout, "base2<wchar_t>::", nruns);
        }

        if (std::find(args.begin(), args.end(), "base16") != args.end()) {
            typedef stlencoders::base16<wchar_t> base16;
            run<base16>(std::cout, "base16<wchar_t>::", nruns);
        }

        if (std::find(args.begin(), args.end(), "base32") != args.end()) {
            typedef stlencoders::base32<wchar_t> base32;
            run<base32>(std::cout, "base32<wchar_t>::", nruns);
        }

        if (std::find(args.begin(), args.end(), "base64") != args.end()) {
            typedef stlencoders::base64<wchar_t> base64;
            run<base64>(std::cout, "base64<wchar_t>::", nruns);
        }

        if (std::find(args.begin(), args.end(), "base32hex") != args.end()) {
            typedef stlencoders::base32hex_traits<wchar_t> traits;
            typedef stlencoders::base32<wchar_t, traits> base32hex;
            run<base32hex>(std::cout, "base32hex<char>::", nruns);
        }

        if (std::find(args.begin(), args.end(), "base64url") != args.end()) {
            typedef stlencoders::base64url_traits<wchar_t> traits;
            typedef stlencoders::base64<wchar_t, traits> base64url;
            run<base64url>(std::cout, "base64url<char>::", nruns);
        }
    }

    if (all) {
#ifdef HAVE_MODP_B2_H
        if (std::find(args.begin(), args.end(), "base2") != args.end()) {
            run<modp_b2>(std::cout, "modp_b2_", nruns);
        }
#endif

#ifdef HAVE_MODP_B16_H
        if (std::find(args.begin(), args.end(), "base16") != args.end()) {
            run<modp_b16>(std::cout, "modp_b16_", nruns);
        }
#endif

#ifdef HAVE_MODP_B64_H
        if (std::find(args.begin(), args.end(), "base64") != args.end()) {
            run<modp_b64>(std::cout, "modp_b64_", nruns);
        }
#endif

#ifdef HAVE_MODP_B64W_H
        if (std::find(args.begin(), args.end(), "base64url") != args.end()) {
            run<modp_b64w>(std::cout, "modp_b64w_", nruns);
        }
#endif

#ifdef HAVE_APR_1_APR_BASE64_H
        if (std::find(args.begin(), args.end(), "base64") != args.end()) {
            run<apr_base64>(std::cout, "apr_base64_", nruns);
        }
#endif
    }

    return EXIT_SUCCESS;
}
