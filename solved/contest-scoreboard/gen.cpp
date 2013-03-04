#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT  100
#define MAXS  200
#define MAXTM 300
#define MAXC  100
#define MAXP  9
#endif

#if 1
#define MAXT  20
#define MAXS  12
#define MAXTM 300
#define MAXC  10
#define MAXP  9
#endif


#define Zero(v) memset((v), 0, sizeof(v))

struct Subm {
    int  c, p, t;
    char l;
    Subm() {}
    Subm(int C, int P, int T, char L) : c(C), p(P), t(T), l(L) {}

    bool operator<(const Subm &x) const {
        return t < x.t;
    }
};

bool vis[MAXTM + 1];

Subm sub[MAXS];

void test_case(bool crit = false)
{
    int nc = crit ? MAXC : rand() % MAXC + 1;
    int ns = crit ? MAXS : rand() % MAXS + 1;
    int np = crit ? MAXP : rand() % MAXP + 1;

    Zero(vis);
    for (int i = 0; i < ns; ++i) {
        int c = rand() % nc + 1;
        int p = rand() % np + 1;
        int t;

        do {
            t = rand() % MAXTM + 1;
        } while (vis[t]);
        vis[t] = true;

        char l;
        int rv = rand() % 10;
        if      (rv == 0) l = 'R';
        else if (rv == 1) l = 'U';
        else if (rv == 2) l = 'E';
        else if (rv < 6)  l = 'C';
        else              l = 'I';

        sub[i] = Subm(c, p, t, l);
    }
    sort(sub, sub + ns);

    puts("");
    for (int i = 0; i < ns; ++i)
        printf("%d %d %d %c\n", sub[i].c, sub[i].p, sub[i].t, sub[i].l);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}
