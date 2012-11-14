#include <cstdio>


#define MAXN 2000


int n;
int rev[MAXN];  // sequence of numbers in reverse

int len_lis[MAXN];
int len_lds[MAXN];

int I[MAXN + 1];


void lis(int *seq, int *ls)
{
    int len = 0;
    for (int i = 0; i < n; ++i) {
        int lo = 1, hi = len;
        while (lo <= hi) {
            int m = (lo + hi) / 2;
            if (I[m] < seq[i]) lo = m + 1;
            else hi = m - 1;
        }
        I[lo] = seq[i], ls[i] = lo;
        if (len < lo) len = lo;
    }
}

void lds(int *seq, int *ls)
{
    int len = 0;
    for (int i = 0; i < n; ++i) {
        int lo = 1, hi = len;
        while (lo <= hi) {
            int m = (lo + hi) / 2;
            if (I[m] > seq[i]) lo = m + 1;
            else hi = m - 1;
        }
        I[lo] = seq[i], ls[i] = lo;
        if (len < lo) len = lo;
    }
}

int solve()
{
    lis(rev, len_lis);
    lds(rev, len_lds);

    int best = 0;
    for (int i = 0; i < n; ++i) {
        int len = len_lis[i] + len_lds[i] - 1;
        if (len > best) best = len;
    }
    return best;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);
        for (int i = n - 1; i >= 0; --i)
            scanf("%d", &rev[i]);
        printf("%d\n", solve());
    }

    return 0;
}
