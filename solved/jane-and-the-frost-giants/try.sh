#! /bin/sh

echo "Generating"
./gen

echo "Running"
./jane < f.in > f.sol
./p < f.in > f.tmp

echo "Diff"
diff -urd f.tmp f.sol
