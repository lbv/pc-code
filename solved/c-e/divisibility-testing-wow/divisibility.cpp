#include <cstdio>
#include <cstring>


#define MAXD 5000
#define MAXE 1000

#define Zero(v) memset((v), 0, sizeof(v))


template <typename TB, typename TE>
TB mod_pow(TB b, TE e, TB m) {
    TB res = 1; for (; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
    return res;
}


int B, D;

bool vis[MAXD];


int least_power_mod_congruent(int x)
{
    Zero(vis);
    for (int e = 1; e <= MAXE; ++e) {
        int p = mod_pow(B, e, D);
        if (p == x) return e;

        if (vis[p]) return -1;
        vis[p] = true;
    }
    return -1;
}

void solve()
{
    int cnt = 0;

    int p;

    p = least_power_mod_congruent(0);
    if (p > 0) {
        printf("Rightmost %d\n", p);
        ++cnt;
    }

    p = least_power_mod_congruent(1);
    if (p > 0) {
        printf("Add all %d\n", p);
        ++cnt;
    }

    p = least_power_mod_congruent(D - 1);
    if (p > 0) {
        printf("Alternate %d change sign\n", p);
        ++cnt;
    }

    if (cnt == 0)
        puts("condition not found.");
}

int main()
{
    int N;
    scanf("%d", &N);

    bool first = true;
    while (N--) {
        scanf("%d%d", &B, &D);

        if (first) first = false;
        else       putchar('\n');

        solve();
    }

    return 0;
}
