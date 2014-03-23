#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>
using namespace std;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef unsigned int u32;

struct Node {
    char c;
    int f;
    Node(char C, int F) : c(C), f(F) {}

    bool operator<(const Node &n) const {
        if (f > n.f) return true;
        if (f < n.f) return false;
        return c < n.c;
    }
};

typedef vector<Node> NV;

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
    void next_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l; *s = 0;
        while (b == 10 || b == 13) read(); }
};

u32 n;
char line[1024];
bool used[26];
int cnt[26];
int len;

void process()
{
    for(int i = 0; i < len; ++i) {
        if (islower(line[i]))
            line[i] = toupper(line[i]);
        if (! isupper(line[i])) continue;

        int idx = line[i] - 'A';
        if (! used[idx]) used[idx] = true;
        ++cnt[idx];
    }
}

int main()
{
    Reader rr;

    n = rr.next_u32();
    rr.next_line(line, len);

    while (n--) {
        rr.next_line(line, len);
        process();
    }

    NV res;

    for (int i = 0; i < 26; ++i)
        if (used[i])
            res.push_back(Node('A' + i, cnt[i]));

    sort(res.begin(), res.end());

    cFor (NV, p, res)
        printf("%c %d\n", p->c, p->f);

    return 0;
}
