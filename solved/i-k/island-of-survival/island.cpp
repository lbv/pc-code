#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXT 1000
#define MAXD 1000


// dp[i][j] will have the probability of surviving with i tigers and j deer
double dp[MAXT + 1][MAXD + 1];

int t, d;


void prepare()
{
    for (int j = 0; j <= MAXD; ++j)
        dp[0][j] = 1.0;

    for (int i = 2; i <= MAXT; i += 2)
        for (int j = 0; j <= MAXD; ++j) {
            // number of distinct pairs of tigers, deer and creatures
            int pt = i * (i - 1) / 2;
            int pd = j * (j - 1) / 2;
            int pc = (i + j + 1) * (i + j) / 2;

            // two tigers meet
            dp[i][j] += (1.0 * pt / pc) * dp[i - 2][j];

            if (j == 0) continue;

            // a tiger and a deer meet
            dp[i][j] += (1.0 * i*j / pc) * dp[i][j - 1];

            // if two deer meet, the probability gets multiplied by a factor
            double fac = (1.0 * pc / (pc - pd));

            // if a deer meets with the human
            // (a) and the human kills it
            double opt1 = (dp[i][j] + (1.0 * j / pc) * dp[i][j - 1]) * fac;

            // (b) the human lets the deer live
            fac = 1.0 * pc / (pc - pd - j);
            double opt2 = dp[i][j] * fac;

            dp[i][j] = max(opt1, opt2);
        }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &t, &d);
        printf("Case %d: %.8lf\n", ++ncase, dp[t][d]);
    }

    return 0;
}
