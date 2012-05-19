#! /bin/sh

echo "Generating"
java gen > data.in

echo "Running"
./trail < data.in > data.sol
./p < data.in > data.tmp

echo "Grepping"
fgrep PUNK data.tmp

echo "Diff"
diff -urd data.tmp data.sol
