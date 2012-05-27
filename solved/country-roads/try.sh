#! /bin/sh

echo "Generating"
java gen > data.in

echo "Running"
./CountryRoads < data.in > data.out
./p < data.in > data.tmp

echo "Diff"
diff -urd data.tmp data.out
