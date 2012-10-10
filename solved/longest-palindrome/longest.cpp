#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXLEN 1000


// dp[i][j] has the length of the longest palindromic subsequence in the
// range [i, j)
int dp[MAXLEN][MAXLEN + 1];

char str[MAXLEN + 1];
int len;


void run_dp()
{
    for (int i = 0; i < len; ++i)
        dp[i][i + 1] = 1;

    for (int l = 2; l <= len; ++l)
        for (int i = 0, j = i + l; j <= len; ++i, ++j) {
            if (str[i] == str[j - 1]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
                continue;
            }

            if (dp[i][j - 1] > dp[i + 1][j]) {
                dp[i][j] = dp[i][j - 1];
                continue;
            }

            if (dp[i + 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i + 1][j];
                continue;
            }

            dp[i][j] = dp[i + 1][j];
        }
}

int main()
{
    int T;
    scanf("%d", &T);
    gets(str);

    while (T--) {
        gets(str);
        len = strlen(str);

        run_dp();

        printf("%d\n", dp[0][len]);
    }

    return 0;
}
