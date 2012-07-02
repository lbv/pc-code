#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXLEN 1023

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void process() {
        char w[MAXLEN + 1];
        int i = 0;

        for (; b != 0; read()) {
            if (b > 32) {
                w[i++] = b;
                continue;
            }

            for (int j = i - 1; j >= 0; --j)
                putchar(w[j]);
            i = 0;
            putchar(b);
        }
        for (int j = i - 1; j >= 0; --j)
            putchar(w[j]);
    }
};

int main()
{
    Reader rr;
    rr.process();

    return 0;
}
