#include <cstdio>
#include <cstring>

#define Sc(t,v) static_cast<t>(v)

char map[256];

void add_map(const char *str)
{
    int len = strlen(str);

    for (int i = 1; i < len; ++i)
        map[Sc(int, str[i])] = str[i - 1];
}

void prepare()
{
    add_map("`1234567890-=");
    add_map("QWERTYUIOP[]\\");
    add_map("ASDFGHJKL;'");
    add_map("ZXCVBNM,./");
}

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    void process() {
        for (; b != 0; read()) {
            if (b > 32)
                putchar(map[Sc(int, b)]);
            else
                putchar(b);
        }
    }
    void next_real_line(char *s) {
        for (; b != 10 && b != 13 && b != 0; read()) *s++ = b; *s = 0;
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

int main()
{
    prepare();

    Reader rr;
    rr.process();

    return 0;
}
