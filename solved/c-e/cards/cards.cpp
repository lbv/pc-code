#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define Zero(v) memset((v), 0, sizeof(v))


double memo[14][14][14][14][3][3][3][3];
bool vis[14][14][14][14][3][3][3][3];

int C, D, H, S;


// expected number of cards to draw until c, d, h, s are made, having used
// jc jokers for clubs, jd for d, etc.
double dp(int c, int d, int h, int s, int jc, int jd, int jh, int js)
{
    if (c + jc >= C && d + jd >= D && h + jh >= H && s + js >= S) return 0;
    if (vis[c][d][h][s][jc][jd][jh][js])
        return memo[c][d][h][s][jc][jd][jh][js];
    vis[c][d][h][s][jc][jd][jh][js] = true;

    int deck = 54 - (c + d + h + s + jc + jd + jh + js);
    int rc = 13 - c;
    int rd = 13 - d;
    int rh = 13 - h;
    int rs = 13 - s;
    int rj = 2 - (jc + jd + jh + js);

    if (rc == 0 && rd == 0 && rh == 0 && rs == 0 && rj == 0)
        return memo[c][d][h][s][jc][jd][jh][js] = 100;

    double e = 0.0;

    if (rc > 0)
        e += (dp(c + 1, d, h, s, jc, jd, jh, js) + 1.0) * rc / deck;
    if (rd > 0)
        e += (dp(c, d + 1, h, s, jc, jd, jh, js) + 1.0) * rd / deck;
    if (rh > 0)
        e += (dp(c, d, h + 1, s, jc, jd, jh, js) + 1.0) * rh / deck;
    if (rs > 0)
        e += (dp(c, d, h, s + 1, jc, jd, jh, js) + 1.0) * rs / deck;

    if (rj > 0) {
        double opt = dp(c, d, h, s, jc + 1, jd, jh, js);
        opt = min(opt, dp(c, d, h, s, jc, jd + 1, jh, js));
        opt = min(opt, dp(c, d, h, s, jc, jd, jh + 1, js));
        opt = min(opt, dp(c, d, h, s, jc, jd, jh, js + 1));

        e += (opt + 1.0) * rj / deck;
    }

    return memo[c][d][h][s][jc][jd][jh][js] = e;
}

bool valid()
{
    if (C + D + H + S > 54) return false;
    int jok = 0;
    if (C > 13) jok += C - 13;
    if (D > 13) jok += D - 13;
    if (H > 13) jok += H - 13;
    if (S > 13) jok += S - 13;
    if (jok > 2) return false;
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%d", &C, &D, &H, &S);
        printf("Case %d: ", ++ncase);
        if (! valid())
            puts("-1");
        else {
            Zero(vis);
            printf("%.8lf\n", dp(0, 0, 0, 0, 0, 0, 0, 0));
        }
    }

    return 0;
}
