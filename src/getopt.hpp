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

#ifndef GETOPT_HPP
#define GETOPT_HPP

#include <cstring>
#include <iostream>

namespace {
    char* optarg = 0;
    int optind = 1;
    int opterr = 1;
    int optopt = 0;

    int getopt(int argc, char* const argv[], const char *opts)
    {
        static char* np = 0;

        if (!np || *np == '\0') {
            np = argv[optind];
            if (!np || *np != '-' || std::strcmp(np, "-") == 0) {
                return -1;
            }
            ++optind;
            if (std::strcmp(np, "--") == 0) {
                return -1;
            }
            ++np;
        }

        const char* cp = std::strchr(opts, (optopt = *np++));

        if (!cp || *cp++ == ':') {
            if (opterr != 0 && *opts != ':') {
                std::cerr << argv[0] << ": invalid option"
                          << " '" << char(optopt) << "'\n";
            }
            return '?';
        }
        if (*cp != ':') {
            return optopt;
        }
        if (*np != '\0') {
            optarg = np;
            np = 0;
            return optopt;
        }
        if (optind < argc) {
            optarg = argv[optind++];
            return optopt;
        }
        if (opterr != 0 && *opts != ':') {
            std::cerr << argv[0] << ": option requires an argument"
                      << " '" << char(optopt) << "'\n";
        }
        return *opts == ':' ? ':' : '?';
    }
}

#endif
