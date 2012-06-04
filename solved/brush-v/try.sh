#! /bin/sh

while [ $? -eq 0 ]; do

    # echo "Generating"
    # ./gen

    echo "Running"
    ./Brush < ee.in > ee.sol
    ./p     < ee.in > ee.tmp

    echo "Diff"
    diff -urd ee.tmp ee.sol

done
