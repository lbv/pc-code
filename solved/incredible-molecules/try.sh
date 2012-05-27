#! /bin/sh

echo "Generating"
java gen > data.in

echo "Running"
./IncredibleMolecules < data.in > data.out
./p                   < data.in > data.tmp

echo "Cat"
echo "----"
cat data.tmp
echo "----"
cat data.out
#echo "Diff"
#diff -urd data.tmp data.out
