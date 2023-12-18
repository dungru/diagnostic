#!/usr/bin/env bash

SOURCES=$(find "$(git rev-parse --show-toplevel)" -type f \( -name "*.cpp" -o -name "*.cc" -o -name "*.c" -o -name "*.h" \) -not -path "$(git rev-parse --show-toplevel)/redis/*")

CLANG_FORMAT=$(which clang-format-12)
if [ $? -ne 0 ]; then
    CLANG_FORMAT=$(which clang-format)
    if [ $? -ne 0 ]; then
        echo "[!] clang-format not installed. Unable to check source file format policy." >&2
        exit 1
    fi
fi

set -x

for file in ${SOURCES};
do
    $CLANG_FORMAT ${file} > expected-format
    $CLANG_FORMAT -i ${file}
    diff -u -p --label="${file}" --label="expected coding style" ${file} expected-format
done
exit $($CLANG_FORMAT --output-replacements-xml ${SOURCES} | egrep -c "</replacement>")