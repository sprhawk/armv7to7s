#! /bin/bash

set -o nounset
set -o errexit

if [ $# -lt 2 ]; then
    me=$(basename $0);
    echo "usage: $me old_universal_binary new_universal_binary";
    exit 1;
fi

set -v

oldbinary=$1
newbinary=$2

TMP="tmp"

ARMV7_ARCHIVE="armv7.a"
ARMV7S_ARCHIVE="armv7s.a"

LIPO=lipo
AR=ar

if [ -d $TMP ]; then
    rm -rf $TMP;
fi

mkdir $TMP
cp $1 $TMP/
cd $TMP

$LIPO -thin armv7 "$oldbinary" -output "$ARMV7_ARCHIVE"
ar -x "$ARMV7_ARCHIVE"
find . -name "*.o" -exec ../armv7to7s {} {}7s \;
ar -r "$ARMV7S_ARCHIVE" *.o7s
lipo "$ARMV7S_ARCHIVE" "$oldbinary" -create -output "$newbinary"

cd ../
mv "$TMP/$newbinary" .
rm -rf $TMP


