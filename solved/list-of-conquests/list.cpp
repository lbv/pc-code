#include <cstdio>
#include <map>
#include <string>
using namespace std;

#define MAXLEN 75

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef unsigned int u32;

typedef pair<string, int> SI;
typedef map<string, int>  SIM;
typedef SIM::iterator     SIMi;

// I/O
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
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
    void skip_line() {
        while (b != 10 && b != 13) read();
        while (b == 10 || b == 13) read(); }
};

char country[MAXLEN + 1];
SIM cmap;

int main()
{
    Reader rr;
    int n = rr.next_u32();

    while (n--) {
        rr.next(country);
        rr.skip_line();
        string k(country);

        SIMi elem = cmap.find(k);
        if (elem == cmap.end())
            cmap.insert(SI(k, 1));
        else
            ++(elem->second);
    }

    cFor (SIM, e, cmap)
        printf("%s %d\n", e->first.c_str(), e->second);

    return 0;
}
