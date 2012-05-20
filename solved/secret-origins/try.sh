#! /bin/sh

while [ $? -eq 0 ]; do
    echo "Generating"
    java gen > data.in

    echo "Running"
    java BinaryWeight < data.in > data.out
    ./p < data.in > data.tmp

    echo "Diff"
    diff -urd data.tmp data.out
done
