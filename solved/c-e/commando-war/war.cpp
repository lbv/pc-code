#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 1000


struct Commando {
    int B, J;
    Commando() {}
    bool operator<(const Commando &x) const { return J > x.J; }
};


int N;
int tbrief;  // total briefing time

Commando comm[MAXN];


int solve()
{
    sort(comm, comm + N);

    int ans = tbrief;
    int cbrief = 0;   // cumulative briefing time

    for (int i = 0; i < N; ++i) {
        cbrief += comm[i].B;
        ans = max(ans, cbrief + comm[i].J);
    }
    return ans;
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        tbrief = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &comm[i].B, &comm[i].J);
            tbrief += comm[i].B;
        }

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
