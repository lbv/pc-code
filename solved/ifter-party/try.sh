#! /bin/sh

echo "Generating"
java gen > data.in

echo "Running"
./ifter < data.in > data.sol
./p < data.in > data.tmp

echo "Diff"
diff -urd data.tmp data.sol
