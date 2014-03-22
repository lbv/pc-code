#include <cstdio>


typedef unsigned int u32;


struct LineReader {
    char b; LineReader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32 && b != 10) read(); }
    void skip_line() { skip(); if (b == 10) { read(); skip(); } }
    bool has_next() { skip(); return b > 0 && b != 10; }
    bool eof() { skip(); return b == 0; }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};


int sec[32];


int main()
{
    LineReader lr;
    int T = lr.next_u32();
    lr.skip_line();

    while (T--) {
        int n = 0;  // number of sections
        int p = 0;  // people

        sec[n++] = lr.next_int();
        p = sec[0];

        int lo = p;

        while (lr.has_next()) {
            int a = lr.next_int();
            int b = lr.next_int();

            sec[n] = p = p + a + b;
            if (sec[n] < lo) lo = sec[n];
            ++n;
        }
        lr.skip_line();

        bool first = true;
        for (int i = 0; i < n; ++i)
            if (sec[i] == lo) {
                if (first) first = false;
                else       putchar(' ');
                printf("%c", 'A' + i);
            }
        printf(" %d\n", lo);
    }

    return 0;
}
