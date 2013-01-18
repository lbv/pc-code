//
// I/O
//
struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
    char next_char() { skip(); char c = b; read(); return c; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
    bool has_next() { skip(); return b > 0; }
    void skip_line() {
        for (; b != 10 && b != 13 && b >= 0; read());
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
    void next_line(char *s) {
        for (; b != 10 && b != 13 && b >= 0; read()) *s++ = b; *s = 0;
        while (b == 10 || b == 13) read(); }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b >= 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};
struct LineReader {
    char b; LineReader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32 && b != 10) read(); }
    void skip_line() { skip(); if (b == 10) { read(); skip(); } }
    bool has_next() { skip(); return b > 0 && b != 10; }
    bool eof() { skip(); return b == 0; }
};
