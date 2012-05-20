#! /bin/sh

echo "Generating"
./gen

echo "Running"
./TheCrystalMaze < a.in > a.sol
./p < a.in > a.tmp

echo "Diff"
diff -urd a.tmp a.sol
