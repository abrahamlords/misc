#!/bin/bash

# create the executable

echo Creating the encode executable.

rm -f ./encodeTest
make encodeTest

find encodeTest
if [[ $? -ne 0 ]]
then
    echo \"make encodeTest\" could not create the \"encodeTest\" executable.
    echo Please ensure source files and makefile are in the same folder as this script.
    exit 1
fi

# tests

echo "Preparing test folder."

rm -rf ./encoded
mkdir encoded

echo "Running tests."

PATH_REGEX="\.\/inputs\/(.+)\.txt"
FILES="./inputs/*.txt"
DIFFERENCES=0

trydiff() {
    diff -q -Z "$1" "$2"

    if [[ $? -ne 0 ]]
    then
        ((DIFFERENCES=DIFFERENCES+1))
    fi
}

for INPUT in $FILES
do
    if [[ $INPUT =~ $PATH_REGEX ]]
    then
        NAME=${BASH_REMATCH[1]}
        ENCPATH="./encoded/$NAME.txt"
        COMPARED="./remote/$NAME.txt"

        rm -f "$ENCPATH"
        ./encodeTest insertion <"$INPUT" >"$ENCPATH"
        trydiff "$ENCPATH" "$COMPARED"
    fi
done

echo $DIFFERENCES failing output\(s\).
