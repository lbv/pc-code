#include <cmath>
#include <cstdio>


#define MAXN 50


int N;
int ns[MAXN];
double ans;


int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

bool solve()
{
    int den = 0;
    int num = 0;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j) {
            if (gcd(ns[i], ns[j]) == 1) ++num;
            ++den;
        }

    if (num == 0) return false;
    ans = sqrt(6.0 * den / num);

    return true;
}

int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        for (int i = 0; i < N; ++i) scanf("%d", &ns[i]);

        if (solve())
            printf("%.6lf\n", ans);
        else
            puts("No estimate for this data set.");
    }

    return 0;
}
