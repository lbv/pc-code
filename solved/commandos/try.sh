#! /bin/sh

echo "Generating"
./gen

echo "Running"
./commandos < e.in > e.sol
./p < e.in > e.tmp

echo "Diff"
diff -urd e.tmp e.sol
