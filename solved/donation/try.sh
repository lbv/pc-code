#! /bin/sh

echo "Generating"
java gen > data.in

echo "Running"
java Donation < data.in > data.sol
./p < data.in > zz

echo "Diff"
diff -urd zz data.sol
