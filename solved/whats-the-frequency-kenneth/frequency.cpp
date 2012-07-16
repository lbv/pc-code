#include <cctype>
#include <cstdio>
#include <cstring>


#define MAXLEN 1048575

#define Zero(v) memset((v), 0, sizeof(v))


//
// I/O
//
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    bool has_next() { return b > 0; }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};


char line[MAXLEN + 1];
int len;

int upper[26];
int lower[26];


int main()
{
    Reader rr;

    while (rr.has_next()) {
        rr.next_real_line(line, len);

        Zero(upper);
        Zero(lower);

        int hi = 0;

        for (int i = 0; i < len; ++i) {
            if (isupper(line[i])) {
                int idx = line[i] - 'A';
                ++upper[idx];
                if (upper[idx] > hi) hi = upper[idx];
            }
            else if (islower(line[i])) {
                int idx = line[i] - 'a';
                ++lower[idx];
                if (lower[idx] > hi) hi = lower[idx];
            }
        }

        for (int i = 0; i < 26; ++i)
            if (upper[i] == hi)
                putchar('A' + i);
        for (int i = 0; i < 26; ++i)
            if (lower[i] == hi)
                putchar('a' + i);

        printf(" %d\n", hi);
    }

    return 0;
}
