#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXLINE  1023
#define MAXTEAMS 100

#define Neg(v)  memset((v), -1, sizeof(v))
#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;


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


struct Team {
    int n;       // team number
    int s;       // problems solved
    int p;       // total penalty time
    int pp[10];  // penalty per problem (applied only when solved)

    Team() {}
    Team(int N) : n(N) {
        s = p = 0;
        Zero(pp);
    }

    bool operator<(const Team &x) const {
        if (s != x.s) return s > x.s;
        if (p != x.p) return p < x.p;
        return n < x.n;
    }
};


Team contest[MAXTEAMS + 1];

// par[i] is the index of team i inside contest
int par[MAXTEAMS + 1];

char line[MAXLINE + 1];

int len;
int nt;  // number of teams


int main()
{
    Reader rr;

    int T = rr.next_u32();
    rr.skip_line();
    rr.skip_line();

    bool first = true;
    while (T--) {
        nt = 0;
        Neg(par);

        while (true) {
            rr.next_real_line(line, len);
            if (strcmp("", line) == 0) break;

            int team, prob, time;
            char L;

            sscanf(line, "%d%d%d %c", &team, &prob, &time, &L);

            if (par[team] < 0) {
                par[team] = nt++;
                contest[par[team]] = Team(team);
            }

            int idx = par[team];

            // penalty per problem is negative if it has been solved
            if (contest[idx].pp[prob] < 0 ||
                (L != 'C' && L != 'I')) continue;

            if (L == 'C') {
                ++contest[idx].s;
                contest[idx].p += contest[idx].pp[prob] + time;
                contest[idx].pp[prob] = -1;
            }
            else
                contest[idx].pp[prob] += 20;
        }

        sort(contest, contest + nt);

        if (first) first = false;
        else puts("");

        for (int i = 0; i < nt; ++i)
            printf("%d %d %d\n", contest[i].n, contest[i].s, contest[i].p);
    }

    return 0;
}
