#include <cstdio>

#define MAXM 15


typedef long long    i64;
typedef unsigned int u32;


int N, M;
int ms[MAXM];  // life-cycles of predators
int pos[1 << MAXM];


i64 gcd(i64 a, i64 b) { for (i64 c = a%b; c; a=b,b=c,c=a%b); return b; }
i64 lcm(i64 a, i64 b) { return a*b / gcd(a, b); }

u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
u32 init_popcount(int n) { return (1 << n) - 1; }
#define Back(b)    ((b) & -(b))
#define PopBack(b) (b &= ~Back(b))

int solve()
{
    int ans = N;

    u32 top = 1 << M;
    for (int n = 1; n <= M; ++n) {
        for (u32 b = init_popcount(n); b < top; b = next_popcount(b)) {
            i64 _lcm = 1;

            for (u32 it = b; it; PopBack(it)) {
                u32 bit = Back(it);
                int idx = pos[bit];
                _lcm = lcm(_lcm, ms[idx]);
            }

            int x = N / _lcm;
            ans = n % 2 == 0 ? ans + x : ans - x;
        }
    }

    return ans;
}

void prepare()
{
    for (int i = 0; i < MAXM; ++i)
        pos[1 << i] = i;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &N, &M);

        for (int i = 0; i < M; ++i)
            scanf("%d", &ms[i]);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
