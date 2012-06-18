#include <cstdio>

#define MAXS 20000

// dp[j] will contain the index i, such that the range (i, j) contains the
// maximum sum subsequence that ends in j
int dp[MAXS + 1];

int ns[MAXS + 1];
int s;

int best_end;  // right index of the best subsequence
int hi;        // highest sum found
int len;       // length of subsequence

void run_dp()
{
    best_end = 1;
    dp[1] = 1;
    hi = ns[1];
    len = 1;

    for (int i = 2; i < s; ++i) {
        dp[i] = i;

        if (ns[i] - ns[dp[i - 1] - 1] >= ns[i] - ns[i - 1])
            dp[i] = dp[i - 1];

        int sum = ns[i] - ns[dp[i] - 1];

        if (sum > hi || (sum == hi && i - dp[i] + 1 > len)) {
            best_end = i;
            hi = ns[i] - ns[dp[i] - 1];
            len = i - dp[i] + 1;
        }
    }
}

int main()
{
    int b;
    scanf("%d", &b);

    for (int ncase = 1; ncase <= b; ++ncase) {
        scanf("%d", &s);

        for (int i = 1; i < s; ++i) {
            scanf("%d", &ns[i]);
            ns[i] += ns[i-1];
        }

        run_dp();

        if (ns[best_end] - ns[dp[best_end] - 1] > 0)
            printf("The nicest part of route %d is between stops %d and %d\n",
                   ncase, dp[best_end], best_end + 1);
        else
            printf("Route %d has no nice parts\n", ncase);
    }
}
