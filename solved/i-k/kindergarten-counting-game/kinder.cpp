#include <cstdio>
#include <cctype>

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    bool has_next() { skip(); return b > 0; }
    void next_line(char *s, int &len) {
        for (len=0; b != 10 && b != 13; read()) *s++ = b, ++len; *s = 0;
        while (b == 10 || b == 13) read(); }
};

char line[100000];
int len;

int main()
{
    Reader rr;

    while (rr.has_next()) {
        rr.next_line(line, len);

        int cnt = 0;
        for (int i = 0; i < len; ++i) {
            if (! isalpha(line[i])) continue;

            ++cnt;
            do {
                ++i;
            } while(i < len && isalpha(line[i]));
        }

        printf("%d\n", cnt);
    }

    return 0;
}
