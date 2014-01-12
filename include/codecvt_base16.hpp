/*
 * Copyright (c) 2014 Thomas Kemmer <tkemmer@computer.org>
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

#ifndef STLENCODERS_CODECVT_BASE16_HPP
#define STLENCODERS_CODECVT_BASE16_HPP

#include "base16.hpp"

#include <locale>

/**
 * @file
 *
 * Implementation of the Base16 std::codecvt facet.
 */
namespace stlencoders {
    /**
     * Base16 state type.
     */
    typedef struct {
        unsigned char f;
        unsigned char buf;
    } base16_state_t;

    /**
     * Base16 std::codecvt facet.
     */
    class codecvt_base16 : public std::codecvt<char, char, mbstate_t> {
        typedef typename std::codecvt<char, char, mbstate_t> base_type;
        typedef typename base_type::result result;
        typedef typename base_type::state_type state_type;
        typedef typename base_type::intern_type intern_type;
        typedef typename base_type::extern_type extern_type;

    public:
        /**
         * Constructs a new codecvt_base16 facet, passes the initial
         * reference counter refs to the base class.
         */
        explicit codecvt_base16(std::size_t refs = 0) : base_type(refs) { }

        /**
         * Destroys the facet. Unlike the locale-managed facets, this
         * facet's destructor is public.
         */
        virtual ~codecvt_base16() { }

    protected:
        /**
         * converts a string from internT to externT, such as when
         * writing to file
         */
        virtual result do_out(
            state_type& state,
            const intern_type* from,
            const intern_type* from_end,
            const intern_type*& from_next,
            extern_type* to,
            extern_type* to_end,
            extern_type*& to_next) const
        {
            if ((to_end - to) / 2 < (from_end - from))
                from_end = from + (to_end - to) / 2;
            to_next = base16<extern_type>::encode(from, from_end, to);
            from_next = from_end;
            return ok;
        }

        /**
         * converts a string from externT to internT, such as when
         * reading from file
         */
        result do_in(
            state_type& state,
            const extern_type* from,
            const extern_type* from_end,
            const extern_type*& from_next,
            intern_type* to,
            intern_type* to_end,
            intern_type*& to_next) const
        {
            return ok;
        }

        /**
         * generates the termination character sequence of externT
         * characters for incomplete conversion
         */
        result do_unshift(
            state_type& state,
            extern_type* to,
            extern_type* to_end,
            extern_type*& to_next) const
        {
            return error;
        }

        /**
         * returns the number of externT characters necessary to
         * produce one internT character, if constant
         */
        int do_encoding() const throw() {
            return 2;
        }

        /**
         * tests if the facet encodes an identity conversion for all
         * valid argument values
         */
        bool do_always_noconv() const throw() {
            return false;
        }

        /**
         * calculates the length of the externT string that would be
         * consumed by conversion into given internT buffer
         */
        int do_length(
            state_type& state,
            const extern_type* from,
            const extern_type* from_end,
            std::size_t max) const
        {
            // FIXME: handle state
            std::size_t n = from_end - from;
            return n < max * 2 ? n : max * 2;
        }

        /**
         * returns the maximum number of externT characters that could
         * be converted into a single internT character
         */
        int do_max_length() const throw() {
            return 2;
        }
    };
}

#endif
