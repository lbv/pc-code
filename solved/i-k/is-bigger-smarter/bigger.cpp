#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 1000


struct Tuple {
    int a, b, i;
    Tuple() {}
    Tuple(int A, int B, int I) : a(A), b(B), i(I) {}
    bool operator<(const Tuple &x) const {
        if (a != x.a) return a < x.a;
        return b < x.b;
    }
};


Tuple tups[MAXN];
int N;

// dp[i]: maximum length of sub sequence that ends in tups[i]
int dp[MAXN];

// pre[i]: index of the tuple previous to i to form the sequence
int pre[MAXN];

int sol[MAXN];


int main()
{
    N = 0;
    while (true) {
        int a, b;
        if (scanf("%d%d", &a, &b) != 2) break;
        tups[N] = Tuple(a, b, N + 1);
        ++N;
    }

    sort(tups, tups + N);
    dp[0] = 1;
    pre[0] = -1;

    int len = 1;
    int end = 0;

    for (int i = 1; i < N; ++i) {
        int best = 0;
        pre[i] = -1;

        for (int j = 0; j < i; ++j)
            if (tups[j].a < tups[i].a
                && tups[j].b > tups[i].b
                && dp[j] > best) {
                best = dp[j];
                pre[i] = j;
            }

        dp[i] = best + 1;
        if (best + 1 > len) len = best + 1, end = i;
    }

    printf("%d\n", len);

    int n = 0;
    for (int i = end; i >= 0; i = pre[i])
        sol[n++] = tups[i].i;

    for (int i = n - 1; i >= 0; --i)
        printf("%d\n", sol[i]);

    return 0;
}
