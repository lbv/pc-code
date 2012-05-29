#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

#define MAXL 100

char s1[MAXL + 1];
char s2[MAXL + 1];
int l1, l2;

// dp[i][j] contains the length of the LCS of s1(i) and s2(j), where s(i) is
// the prefix of s of length i
int dp[MAXL + 1][MAXL + 1];

// lcs[i][j] has the lexicographically lowest LCS of s1(i) and s2(j)
string lcs[MAXL + 1][MAXL + 1];

void run_dp()
{
    dp[0][0] = 0;
    for (int i = 1; i <= l1; i++) {
        dp[i][0] = 0;
        lcs[i][0].clear();
    }
    for (int i = 1; i <= l2; i++) {
        dp[0][i] = 0;
        lcs[0][i].clear();
    }

    for (int i = 1; i <= l1; i++)
        for (int j = 1; j <= l2; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                lcs[i][j] = lcs[i-1][j-1];
                lcs[i][j].push_back(s1[i-1]);
            }
            else if(dp[i][j-1] > dp[i-1][j]) {
                dp[i][j] = dp[i][j-1];
                lcs[i][j] = lcs[i][j-1];
            }
            else if(dp[i-1][j] > dp[i][j-1]) {
                dp[i][j] = dp[i-1][j];
                lcs[i][j] = lcs[i-1][j];
            }
            else {
                dp[i][j] = dp[i-1][j];
                lcs[i][j] = min(lcs[i-1][j], lcs[i][j-1]);
            }
        }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%s%s", s1, s2);
        l1 = strlen(s1);
        l2 = strlen(s2);

        run_dp();

        if (dp[l1][l2] == 0)
            printf("Case %d: :(\n", ncase++);
        else
            printf("Case %d: %s\n", ncase++, lcs[l1][l2].c_str());
    }

    return 0;
}
