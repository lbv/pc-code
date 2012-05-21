#1 /bin/sh

while [ $? -eq 0 ]
do
    echo "Generating"
    ./gen

    echo "Running original"
    ./positive < a.in > a.out

    echo "Running p"
    ./p < a.in > zz

    echo "Diff"
    diff -urd zz a.out
done
