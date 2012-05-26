#! /bin/sh

echo "Generating data .."
java gen > data.in

echo "Running program 1"
./efficient < data.in > data.out

echo "Running program 2"
./p < data.in > zz

echo "Diff"
diff -urd zz data.out
