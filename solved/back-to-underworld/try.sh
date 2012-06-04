#! /bin/sh

echo "Gen"
./gen

echo "Running"
./BackToUnderworld < b.in > b.sol
./p < b.in > zz

echo "Diff"
diff -urd zz b.sol
