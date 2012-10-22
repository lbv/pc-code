#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXNAME 20

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))


typedef unsigned int u32;


struct Player {
    char name[MAXNAME + 1];
    int off, def;
    void read() { scanf("%s%d%d", name, &off, &def); }
    bool operator<(const Player &x) const { return strcmp(name, x.name) < 0; }
};

struct Form {
    u32 bo;   // bitmask of the offensive line
    int off;  // total score of offensive line
    int def;  // score of defense
    Form(u32 BO, int O, int D) : bo(BO), off(O), def(D) {}
    bool operator<(const Form &x) const {
        if (off != x.off) return off > x.off;
        if (def != x.def) return def > x.def;
        return bo < x.bo;
    }
};


Player ps[10];
const u32 b_all = (1 << 10) - 1;
const u32 top   = 1 << 10;


u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
u32 init_popcount(int n) { return (1 << n) - 1; }
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])


u32 solve()
{
    sort(ps, ps + 10);

    Form best(0, -1, -1);

    for (u32 bo = init_popcount(5); bo < top; bo = next_popcount(bo)) {
        int off = 0;
        int def = 0;
        for (int i = 0; i < 10; ++i) {
            if (bo & (1 << i)) off += ps[i].off;
            else def += ps[i].def;
        }
        Form f(bo, off, def);

        if (f < best) best = f;
    }

    return best.bo;
}

void print_line(u32 b)
{
    putchar('(');
    int idx = Ctz(GetFS(b));
    printf("%s", ps[idx].name);

    for (ClrFS(b); b; ClrFS(b)) {
        idx = Ctz(GetFS(b));
        printf(", %s", ps[idx].name);
    }
    puts(")");
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        for (int i = 0; i < 10; ++i)
            ps[i].read();


        printf("Case %d:\n", ++ncase);

        u32 attack = solve();
        print_line(attack);
        print_line(b_all & ~attack);
    }

    return 0;
}
