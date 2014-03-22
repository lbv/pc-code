#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
using namespace std;


#define MAXK 100000
#define MAXTOK 10


typedef multiset<int> IS;
typedef queue<int>    IQ;


#define BUF 1048576
struct LineReader {
    char buf[BUF]; char b; int bi, bz;
    bool read_line() {
        bi = 0; bool r; if (gets(buf)) r = (bz = strlen(buf)) > 0;
        else r = false, bz = 0; read(); return r; }
    void read() { b = bi < bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }

    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
    bool has_next() { skip(); return b > 0; }
};


int K;
char tok[MAXTOK];
IQ mem;
IS s;
int diff;


void add_n(int n)
{
    mem.push(n);
    s.insert(n);

    int mems = mem.size();
    if (mems > K) {
        int n = mem.front();
        mem.pop();
        s.erase(s.find(n));
    }

    int cur = *(s.rbegin()) - *(s.begin());
    if (cur > diff) diff = cur;
}

int main()
{
    LineReader lr;

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%*d%d ", &K);

        s = IS();
        mem = IQ();
        diff = 0;

        printf("Case %d:", ++ncase);
        lr.read_line();

        while (lr.has_next()) {
            lr.next(tok);
            if (tok[0] == 'X')
                printf(" %d", diff);
            else {
                int n;
                sscanf(tok, "%d", &n);
                add_n(n);
            }
        }
        printf(" %d\n", diff);
    }

    return 0;
}
