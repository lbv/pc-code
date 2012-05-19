#include <algorithm>
#include <cstdio>
using namespace std;

// Calculates the highest exponent of 2 that divides n!
int powDivFact2(int n) {
    int sd = 0; for (int N=n; N; N /= 2) sd += N % 2; return n-sd;
}
int powDivFact5(int n) {
    int sd = 0; for (int N=n; N; N /= 5) sd += N % 5;
    return (n-sd)/4;
}

// The amount of trailing zeroes in n!
int fzeroes(int n)
{
    return min(powDivFact2(n), powDivFact5(n));
}

int solve(int q)
{
    int min = q*2;
    int max = q*5;

    while (min <= max) {
        int mid = (min+max)/2;
        int v = fzeroes(mid);

        if (v == q && fzeroes(mid-1) != q) return mid;

        if (v < q) min = min==mid ? min+1 : mid;
        else max = max==mid ? max-1 : mid;
    }
    return -1;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int Q;
        scanf("%d", &Q);

        int ans = solve(Q);
        if (ans < 0)
            printf("Case %d: impossible\n", ncase++);
        else
            printf("Case %d: %d\n", ncase++, ans);
    }

    return 0;
}
