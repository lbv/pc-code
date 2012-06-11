#! /bin/sh

#echo "Generating"
#./gen > data.in

echo "Running"
./get < data.in > data.out
./p   < data.in > data.tmp

echo "Diff"
diff -urd data.tmp data.out
