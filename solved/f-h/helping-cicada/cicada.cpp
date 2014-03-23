#include <cstdio>

#define MAXM 15

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])


typedef long long    i64;
typedef unsigned int u32;


int N, M;
int ms[MAXM];  // life-cycles of predators


i64 gcd(i64 a, i64 b) { for (i64 c = a%b; c; a=b,b=c,c=a%b); return b; }
i64 lcm(i64 a, i64 b) { return a*b / gcd(a, b); }

int solve()
{
    int ans = N;

    u32 all = (1 << M) - 1;
    for (u32 b = 1; b <= all; ++b) {
        i64 _lcm = 1;

        int n = 0;
        for (u32 r = b; r; ClrFS(r)) {
            ++n;
            if (_lcm < 0) continue;

            u32 bit = GetFS(r);
            int idx = Ctz(bit);
            _lcm = lcm(_lcm, ms[idx]);

            if (_lcm > N) _lcm = -1;
        }

        int x = _lcm > 0 ? N / _lcm : 0;
        ans = n % 2 == 0 ? ans + x : ans - x;
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &N, &M);

        for (int i = 0; i < M; ++i) scanf("%d", &ms[i]);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
