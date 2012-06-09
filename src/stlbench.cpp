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

#include "base2.hpp"
#include "base16.hpp"
#include "base32.hpp"
#include "base64.hpp"
#include "error.hpp"

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

#ifdef HAVE_BOOST_ARCHIVE_ITERATORS_BASE64_FROM_BINARY_HPP
# include <boost/archive/iterators/base64_from_binary.hpp>
# include <boost/archive/iterators/binary_from_base64.hpp>
# include <boost/archive/iterators/transform_width.hpp>
#endif

#if defined(HAVE_GETOPT_H)
# include <getopt.h>
#elif defined(HAVE_UNISTD_H)
# include <unistd.h>
#else
# include "getopt.hpp"
#endif

#ifdef HAVE_MODP_B2_H
struct modp_b2 {
    typedef char char_type;

    typedef char int_type;

    static char_type* encode(const int_type* first, const int_type* last, char_type* result)
    {
        return result + modp_b2_encode(result, first, last - first);
    }

    static int_type* decode(const char_type* first, const char_type* last, int_type* result)
    {
        int n = modp_b2_decode(result, first, last - first);

        if (n < 0) {
            throw stlencoders::decode_error("modp_b2 error");
        } else {
            return result + n;
        }
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
struct modp_b16 {
    typedef char char_type;

    typedef char int_type;

    static char_type* encode(const int_type* first, const int_type* last, char_type* result)
    {
        return result + modp_b16_encode(result, first, last - first);
    }

    static int_type* decode(const char_type* first, const char_type* last, int_type* result)
    {
        int n = modp_b16_decode(result, first, last - first);

        if (n < 0) {
            throw stlencoders::decode_error("modp_b16 error");
        } else {
            return result + n;
        }
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
struct modp_b64 {
    typedef char char_type;

    typedef char int_type;

    static char_type* encode(const int_type* first, const int_type* last, char_type* result)
    {
        return result + modp_b64_encode(result, first, last - first);
    }

    static int_type* decode(const char_type* first, const char_type* last, int_type* result)
    {
        int n = modp_b64_decode(result, first, last - first);

        if (n < 0) {
            throw stlencoders::decode_error("modp_b64 error");
        } else {
            return result + n;
        }
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
struct modp_b64w {
    typedef char char_type;

    typedef char int_type;

    static char_type* encode(const int_type* first, const int_type* last, char_type* result)
    {
        return result + modp_b64w_encode(result, first, last - first);
    }

    static int_type* decode(const char_type* first, const char_type* last, int_type* result)
    {
        int n = modp_b64w_decode(result, first, last - first);

        if (n < 0) {
            throw stlencoders::decode_error("modp_b64w error");
        } else {
            return result + n;
        }
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
struct apr_base64 {
    typedef char char_type;

    typedef unsigned char int_type;

    static char_type* encode(const int_type* first, const int_type* last, char_type* result)
    {
        return result + apr_base64_encode_binary(result, first, last - first);
    }

    static int_type* decode(const char_type* first, const char_type*, int_type* result)
    {
        // requires zero-terminated input string
        int n = apr_base64_decode_binary(result, first);

        if (n < 0) {
            throw stlencoders::decode_error("apr_base64 error");
        } else {
            return result + n;
        }
    }

    static std::size_t max_encode_size(std::size_t n) {
        return apr_base64_encode_len(n);
    }

    static std::size_t max_decode_size(std::size_t n) {
        // no corresponding apr_base64 function
        return stlencoders::base64<char>::max_decode_size(n);
    }
};
#endif

#ifdef HAVE_BOOST_ARCHIVE_ITERATORS_BASE64_FROM_BINARY_HPP
template<class charT>
struct boost_base64 {
    typedef charT char_type;

    typedef unsigned char int_type;

    template<class InputIterator, class OutputIterator>
    static OutputIterator encode(
        InputIterator first, InputIterator last, OutputIterator result
        )
    {
        using namespace boost::archive::iterators;

        typedef base64_from_binary<transform_width<InputIterator, 6, 8>, char_type> enc;

        // only encode multiples of three bytes
        last -= (last - first) % 3;

        return std::copy(enc(first), enc(last), result);
    }

    template<class InputIterator, class OutputIterator>
    static OutputIterator decode(
        InputIterator first, InputIterator last, OutputIterator result
        )
    {
        using namespace boost::archive::iterators;

        typedef transform_width<binary_from_base64<InputIterator, char_type>, 8, 6> dec;

        // only decode multiples of four characters
        last -= (last - first) % 4;

        return std::copy(dec(first), dec(last), result);
    }

    static std::size_t max_encode_size(std::size_t n) {
        return stlencoders::base64<char_type>::max_encode_size(n);
    }

    static std::size_t max_decode_size(std::size_t n) {
        return stlencoders::base64<char_type>::max_decode_size(n);
    }
};
#endif

template<class charT, int N, class traits = std::char_traits<charT> >
struct chargen {
    typedef charT char_type;

    typedef traits traits_type;

    char_type operator()() const {
        return traits::to_char_type(std::rand() % N);
    }
};

class runner {
public:
    runner(std::ostream& out, int hlen = 29, int tlen = 10)
        : os(out), headlen(hlen), timelen(tlen)
    {
        os << std::fixed;

        for (const std::size_t* p = samples; *p; ++p) {
            maxsize = *p;
        }

        os << std::setw(headlen) << "Input size [bytes]: ";
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

    template<class Codec, class Generator>
    void encode(const char* name, unsigned long minruns, Generator gen) {
        typedef typename Codec::char_type char_type;
        typedef typename Codec::int_type int_type;

        os << std::setw(headlen - 2) << name << ": " << std::flush;

        for (const std::size_t* psize = samples; *psize; ++psize) {
            std::vector<int_type> src(*psize);
            std::vector<char_type> dst(Codec::max_encode_size(*psize));
            unsigned long nruns = minruns * maxsize / *psize;

            std::generate(src.begin(), src.end(), gen);

            std::clock_t t0 = std::clock();
            for (unsigned long i = 0; i != nruns; ++i) {
                Codec::encode(&src[0], &src[0] + src.size(), &dst[0]);
            }
            std::clock_t t1 = std::clock();

            os << std::setw(timelen) << fmtclock(double(t1 - t0) / nruns);
            os << std::flush;
        }
        os << std::endl;
    }

    template<class Codec>
    void encode(const char* name, unsigned long minruns) {
        encode<Codec>(name, minruns, chargen<char, 256>());
    }

    template<class Codec, class Generator>
    void decode(const char* name, unsigned long minruns, Generator gen) {
        typedef typename Codec::char_type char_type;
        typedef typename Codec::int_type int_type;

        os << std::setw(headlen - 2) << name << ": " << std::flush;

        for (const std::size_t* psize = samples; *psize; ++psize) {
            std::vector<char_type> src(*psize);
            std::vector<int_type> dst(Codec::max_decode_size(*psize));
            unsigned long nruns = minruns * maxsize / *psize;

            std::generate(src.begin(), src.end(), gen);
            src.push_back('\0'); // for apr_base64_decode_binary

            std::clock_t t0 = std::clock();
            for (unsigned long i = 0; i != nruns; ++i) {
                Codec::decode(&src[0], &src[0] + *psize, &dst[0]);
            }
            std::clock_t t1 = std::clock();

            os << std::setw(timelen) << fmtclock(double(t1 - t0) / nruns);
            os << std::flush;
        }
        os << std::endl;
    }

private:
    std::string fmtclock(double t, int prec = 2) {
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

private:
    std::ostream& os;
    std::size_t maxsize;
    std::size_t headlen;
    std::size_t timelen;

private:
    static const std::size_t samples[];
};

const std::size_t runner::samples[] = { 16, 256, 4096, 65536, 1048576, 0 };

void usage(std::ostream& os, const char* progname)
{
    os << "Usage: " << progname << " [OPTION]... [ENCODING]...\n"
       << "stlencoders performance test.\n"
       << "\n"
       << "  -a         include alternative implementations\n"
       << "  -l         list supported encoding schemes\n"
       << "  -n NRUNS   number of iterations per test (default 256)\n"
       << "  -w         include wide character encodings\n";
}

int main(int argc, char* argv[])
{
    typedef chargen<char, 2, stlencoders::base2_traits<char> > base2gen;
    typedef chargen<char, 16, stlencoders::base16_traits<char> > base16gen;
    typedef chargen<char, 32, stlencoders::base32_traits<char> > base32gen;
    typedef chargen<char, 64, stlencoders::base64_traits<char> > base64gen;
    typedef chargen<char, 32, stlencoders::base32hex_traits<char> > base32hexgen;
    typedef chargen<char, 64, stlencoders::base64url_traits<char> > base64urlgen;

    typedef chargen<wchar_t, 2, stlencoders::base2_traits<wchar_t> > wbase2gen;
    typedef chargen<wchar_t, 16, stlencoders::base16_traits<wchar_t> > wbase16gen;
    typedef chargen<wchar_t, 32, stlencoders::base32_traits<wchar_t> > wbase32gen;
    typedef chargen<wchar_t, 64, stlencoders::base64_traits<wchar_t> > wbase64gen;
    typedef chargen<wchar_t, 32, stlencoders::base32hex_traits<wchar_t> > wbase32hexgen;
    typedef chargen<wchar_t, 64, stlencoders::base64url_traits<wchar_t> > wbase64urlgen;

    bool all = false;
    bool wchar = false;
    unsigned long nruns = 256;

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
        args.push_back("base2");
        args.push_back("base16");
        args.push_back("base32");
        args.push_back("base64");
    } else {
        args.assign(&argv[optind], &argv[argc]);
    }

    runner run(std::cout);

    if (std::find(args.begin(), args.end(), "base2") != args.end()) {
        typedef stlencoders::base2<char> base2;
        run.encode<base2>("base2<char>::encode", nruns);
        run.decode<base2>("base2<char>::decode", nruns, base2gen());
    }

    if (std::find(args.begin(), args.end(), "base16") != args.end()) {
        typedef stlencoders::base16<char> base16;
        run.encode<base16>("base16<char>::encode", nruns);
        run.decode<base16>("base16<char>::decode", nruns, base16gen());
    }

    if (std::find(args.begin(), args.end(), "base32") != args.end()) {
        typedef stlencoders::base32<char> base32;
        run.encode<base32>("base32<char>::encode", nruns);
        run.decode<base32>("base32<char>::decode", nruns, base32gen());
    }

    if (std::find(args.begin(), args.end(), "base64") != args.end()) {
        typedef stlencoders::base64<char> base64;
        run.encode<base64>("base64<char>::encode", nruns);
        run.decode<base64>("base64<char>::decode", nruns, base64gen());
    }

    if (std::find(args.begin(), args.end(), "base32hex") != args.end()) {
        typedef stlencoders::base32hex_traits<char> traits;
        typedef stlencoders::base32<char, traits> base32hex;
        run.encode<base32hex>("base32hex<char>::encode", nruns);
        run.decode<base32hex>("base32hex<char>::decode", nruns, base32hexgen());
    }

    if (std::find(args.begin(), args.end(), "base64url") != args.end()) {
        typedef stlencoders::base64url_traits<char> traits;
        typedef stlencoders::base64<char, traits> base64url;
        run.encode<base64url>("base64url<char>::encode", nruns);
        run.decode<base64url>("base64url<char>::decode", nruns, base64urlgen());
    }

    if (wchar) {
        if (std::find(args.begin(), args.end(), "base2") != args.end()) {
            typedef stlencoders::base2<wchar_t> wbase2;
            run.encode<wbase2>("base2<wchar_t>::encode", nruns);
            run.decode<wbase2>("base2<wchar_t>::decode", nruns, wbase2gen());
        }

        if (std::find(args.begin(), args.end(), "base16") != args.end()) {
            typedef stlencoders::base16<wchar_t> wbase16;
            run.encode<wbase16>("base16<wchar_t>::encode", nruns);
            run.decode<wbase16>("base16<wchar_t>::decode", nruns, wbase16gen());
        }

        if (std::find(args.begin(), args.end(), "base32") != args.end()) {
            typedef stlencoders::base32<wchar_t> wbase32;
            run.encode<wbase32>("base32<wchar_t>::encode", nruns);
            run.decode<wbase32>("base32<wchar_t>::decode", nruns, wbase32gen());
        }

        if (std::find(args.begin(), args.end(), "base64") != args.end()) {
            typedef stlencoders::base64<wchar_t> wbase64;
            run.encode<wbase64>("base64<wchar_t>::encode", nruns);
            run.decode<wbase64>("base64<wchar_t>::decode", nruns, wbase64gen());
        }

        if (std::find(args.begin(), args.end(), "base32hex") != args.end()) {
            typedef stlencoders::base32hex_traits<wchar_t> traits;
            typedef stlencoders::base32<wchar_t, traits> wbase32hex;
            run.encode<wbase32hex>("base32hex<wchar_t>::encode", nruns);
            run.decode<wbase32hex>("base32hex<wchar_t>::decode", nruns, wbase32hexgen());
        }

        if (std::find(args.begin(), args.end(), "base64url") != args.end()) {
            typedef stlencoders::base64url_traits<wchar_t> traits;
            typedef stlencoders::base64<wchar_t, traits> wbase64url;
            run.encode<wbase64url>("base64url<wchar_t>::encode", nruns);
            run.decode<wbase64url>("base64url<wchar_t>::decode", nruns, wbase64urlgen());
        }
    }

    if (!all) {
        return EXIT_SUCCESS;
    }

#ifdef HAVE_MODP_B2_H
    if (std::find(args.begin(), args.end(), "base2") != args.end()) {
        run.encode<modp_b2>("modp_b2_encode", nruns);
        run.decode<modp_b2>("modp_b2_decode", nruns, base2gen());
    }
#endif

#ifdef HAVE_MODP_B16_H
    if (std::find(args.begin(), args.end(), "base16") != args.end()) {
        run.encode<modp_b16>("modp_b16_encode", nruns);
        run.decode<modp_b16>("modp_b16_decode", nruns, base16gen());
    }
#endif

#ifdef HAVE_MODP_B64_H
    if (std::find(args.begin(), args.end(), "base64") != args.end()) {
        run.encode<modp_b64>("modp_b64_encode", nruns);
        run.decode<modp_b64>("modp_b64_decode", nruns, base64gen());
    }
#endif

#ifdef HAVE_MODP_B64W_H
    if (std::find(args.begin(), args.end(), "base64url") != args.end()) {
        run.encode<modp_b64w>("modp_b64w_encode", nruns);
        run.decode<modp_b64w>("modp_b64w_decode", nruns, base64urlgen());
    }
#endif

#ifdef HAVE_APR_1_APR_BASE64_H
    if (std::find(args.begin(), args.end(), "base64") != args.end()) {
        run.encode<apr_base64>("apr_base64_encode", nruns);
        run.decode<apr_base64>("apr_base64_decode", nruns, base64gen());
    }
#endif

#ifdef HAVE_BOOST_ARCHIVE_ITERATORS_BASE64_FROM_BINARY_HPP
    if (std::find(args.begin(), args.end(), "base64") != args.end()) {
        typedef boost_base64<char> base64;
        run.encode<base64>("base64_from_binary<char>", nruns);
        run.decode<base64>("binary_from_base64<char>", nruns, base64gen());

        if (wchar) {
            typedef boost_base64<wchar_t> wbase64;
            run.encode<wbase64>("base64_from_binary<wchar_t>", nruns);
            run.decode<wbase64>("binary_from_base64<wchar_t>", nruns, wbase64gen());
        }
    }
#endif

    return EXIT_SUCCESS;
}
