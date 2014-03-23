#include <cctype>
#include <cstdio>


#define MAXLEN 1048575


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
    void skip() { while (b > 0 && b <= 32) read(); }
    bool has_next() { return b > 0; }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

char line[MAXLEN + 1];
int len;

int main()
{
    Reader rr;
    while (rr.has_next()) {
        rr.next_real_line(line, len);

        int cnt = 0;
        for (int i = 0; i < len; ++i) {
            if (isdigit(line[i])) {
                cnt += line[i] - '0';
                continue;
            }
            if (line[i] == '!') {
                putchar('\n');
                continue;
            }
            if (line[i] == 'b') line[i] = ' ';

            while (cnt--)
                putchar(line[i]);
            cnt = 0;
        }

        putchar('\n');
    }

    return 0;
}
