#! /bin/sh

#echo "Generating"
#./gen

echo "Code 1"
java ExtendedTraffic < e.in > e.out
echo "Code 2"
./p < e.in > zz
echo "Diff"
diff -urd zz e.out
