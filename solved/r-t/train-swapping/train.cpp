#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXL 50

int carr[MAXL + 1];  // carriages
int pos[MAXL + 1];   // positions of the carriages
int L, ans;

void solve()
{
    ans = 0;

    for (int i = 1; i <= L; ++i) {
        while (pos[i] != i) {
            int a = carr[pos[i] - 1];
            int b = i;
            int u = pos[i] - 1;
            int v = pos[i];

            swap(carr[u], carr[v]);
            ++pos[a];
            --pos[b];
            ++ans;
        }
    }
}

int main()
{
    int N;
    scanf("%d", &N);

    while (N--) {
        scanf("%d", &L);

        for (int i = 1; i <= L; ++i) {
            scanf("%d", &carr[i]);
            pos[carr[i]] = i;
        }

        solve();
        printf("Optimal train swapping takes %d swaps.\n", ans);
    }

    return 0;
}
