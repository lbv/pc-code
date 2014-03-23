#! /bin/sh

echo "Generating"
./gen

echo "Running"
./birthday < e.in > e.sol
./p < e.in > e.tmp

echo "Diff"
diff -urd e.tmp e.sol
