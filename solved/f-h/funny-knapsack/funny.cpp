#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 30

#define Back(b)    ((b) & -(b))
#define PopBack(b) (b &= ~Back(b))


typedef unsigned int u32;
typedef long long    i64;

typedef vector<i64>  IV;
typedef IV::iterator IVi;


// values of (1 << x) for x<32 are unique modulo 37
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])

int n;
i64 W;
i64 ws[MAXN];


i64 solve()
{
    int half1 = n/2;

    IV sums;

    for (int i = 0, I = 1 << half1; i < I; ++i) {
        i64 sum = 0;
        for (u32 b = i; b; PopBack(b))
            sum += ws[Ctz(Back(b))];

        sums.push_back(sum);
    }
    sort(sums.begin(), sums.end());

    i64 ans = 0;

    int half2 = n - half1;
    for (int i = 0, I = 1 << half2; i < I; ++i) {
        i64 sum = 0;
        for (u32 b = i; b; PopBack(b))
            sum += ws[half1 + Ctz(Back(b))];

        i64 cap = W - sum;
        IVi it = upper_bound(sums.begin(), sums.end(), cap);
        ans += (it - sums.begin());
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%lld", &n, &W);

        for (int i = 0; i < n; ++i) scanf("%lld", &ws[i]);

        printf("Case %d: %lld\n", ++ncase, solve());
    }

    return 0;
}
