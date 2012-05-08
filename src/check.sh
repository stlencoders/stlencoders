#!/bin/sh

[ -x stlencode ] && STLENCODE="./stlencode" || STLENCODE="$(dirname $0)/stlencode"
[ -x stldecode ] && STLDECODE="./stldecode" || STLDECODE="$(dirname $0)/stldecode"

CMP=cmp

BASE64=/usr/bin/base64
XXD=/usr/bin/xxd

die () {
    echo "$0: $@" >&2
    exit 1
}

for file in "${@:-$0}"; do
    echo "$0: checking '$file'" >&2
    for base in base2 base16 base32 base32hex base64 base64url; do
        $STLENCODE -c $base "$file" | $STLDECODE -c $base | $CMP "$file" \
            || die "$file: $base error"
    done

    if [ -x "$BASE64" ]; then
        $BASE64 "$file" | $STLDECODE -c base64 | $CMP "$file" \
            || die "$file: base64 decode error"
        $STLENCODE -c base64 "$file" | $BASE64 -d | $CMP "$file" \
            || die "$file: base64 encode error"
    fi

    if [ -x "$XXD" ]; then
        $XXD -p "$file" | $STLDECODE -c base16 | $CMP "$file" \
            || die "$file: base16 decode error"
        $STLENCODE -c base16 "$file" | $XXD -p -r | $CMP "$file" \
            || die "$file: base16 encode error"
    fi
done

exit 0
