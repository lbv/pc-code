#include <cstdio>
#include <map>
#include <string>
using namespace std;


#define MAXLEN 30

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef unsigned int u32;

typedef map<string, int> SIM;


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
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void skip_line() {
        for (; b != 10 && b != 13 && b != 0; read());
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};


SIM trees;

char line[MAXLEN + 1];
int len;


int main()
{
    Reader rr;
    int T = rr.next_u32();
    rr.skip_line();
    rr.skip_line();

    bool first = true;
    while (T--) {
        trees.clear();

        int total = 0;
        while (true) {
            rr.next_real_line(line, len);
            if (len == 0) break;

            ++trees[line];
            ++total;
        }

        if (first) first = false;
        else putchar('\n');

        cFor (SIM, t, trees)
            printf("%s %.4lf\n", t->first.c_str(), 100.0 * t->second / total);
    }

    return 0;
}
