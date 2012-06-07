#! /bin/sh

#echo "Gen"
#./gen

echo "Running"
./BackToUnderworld < b.in > b.sol
./p                < b.in > b.tmp

echo "Diff"
diff -urd b.tmp b.sol
