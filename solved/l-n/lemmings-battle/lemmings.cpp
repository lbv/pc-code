#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

#define MAXLEM 100000

typedef priority_queue<int> IP;

int B, SG, SB;

// armies
int bs[MAXLEM];
int gs[MAXLEM];

// surviving lemmings
int _b[MAXLEM];
int _g[MAXLEM];

void fight()
{
    IP blue(bs, bs + SB);
    IP green(gs, gs + SG);

    while (SG > 0 && SB > 0) {
        // counters for surviving fighters
        int ng = 0;
        int nb = 0;

        for (int r = 0 ; r < B && SG > 0 && SB > 0 ;  ++r, --SG, --SB) {
            int bf = blue.top(); blue.pop();
            int gf = green.top(); green.pop();

            if (bf == gf) continue;

            if (bf > gf) _b[nb++] = bf - gf;
            else _g[ng++] = gf - bf;
        }

        // reincorporate surviving members
        for (int i = 0; i < nb; ++i) blue.push(_b[i]), ++SB;
        for (int i = 0; i < ng; ++i) green.push(_g[i]), ++SG;
    }

    if (SG == 0 && SB == 0) {
        puts("green and blue died");
        return;
    }

    if (SG > 0) {
        puts("green wins");
        while (! green.empty()) { printf("%d\n", green.top()); green.pop(); }
        return;
    }

    puts("blue wins");
    while (! blue.empty()) { printf("%d\n", blue.top()); blue.pop(); }
}

int main()
{
    int N;
    scanf("%d", &N);

    bool first = true;
    while (N--) {
        scanf("%d%d%d", &B, &SG, &SB);

        for (int i = 0; i < SG; ++i) scanf("%d", &gs[i]);
        for (int i = 0; i < SB; ++i) scanf("%d", &bs[i]);

        if (first) first = false;
        else puts("");

        fight();
    }

    return 0;
}
