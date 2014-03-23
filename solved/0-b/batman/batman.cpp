#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXL 50

#define Zero(v) memset(v, 0, sizeof(v))

char s1[MAXL + 1], s2[MAXL + 1], s3[MAXL + 1];
int l1, l2, l3;

// dp[i][j][k] has the length of the LCS of s1(i), s2(j), s3(k), where s(i)
// means the prefix of s of length i
int dp[MAXL+1][MAXL+1][MAXL+1];

void run_dp()
{
    Zero(dp);

    for (int i = 1, a = 0; i <= l1; i++, a++)
        for (int j = 1, b = 0; j <= l2; j++, b++)
            for (int k = 1, c = 0; k <= l3; k++, c++) {
                if (s1[a] == s2[b] && s1[a] == s3[c]) {
                    dp[i][j][k] = dp[a][b][c] + 1;
                    continue;
                }
                int val;
                val = max(dp[i][b][c], dp[a][j][c]);
                val = max(dp[a][b][k], val);
                val = max(dp[i][j][c], val);
                val = max(dp[i][b][k], val);
                val = max(dp[a][j][k], val);
                dp[i][j][k] = val;
            }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%s%s%s", s1, s2, s3);
        l1 = strlen(s1);
        l2 = strlen(s2);
        l3 = strlen(s3);

        run_dp();

        printf("Case %d: %d\n", ncase++, dp[l1][l2][l3]);
    }

    return 0;
}
