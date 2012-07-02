#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXLEN 1023

// dp[i] is the minimum number of substrings in the palindromic partitions
// of the string (s + i).
int dp[MAXLEN + 1];

// pal[i][j] is true iff the string from s[i] to s[j-1] is a palindrome
bool pal[MAXLEN][MAXLEN + 1];

char s[MAXLEN + 1];
int len;

void run_dp()
{
    for (int l = 2; l <= len; ++l)
        for (int i = 0, j = i + l; j <= len; ++i, ++j)
            pal[i][j] = pal[i + 1][j - 1] && s[i] == s[j-1];

    dp[len] = 0;
    dp[len - 1] = 1;
    for (int i = len - 2; i >= 0; --i) {
        dp[i] = len;
        for (int j = i + 1; j <= len; ++j)
            if (pal[i][j])
                dp[i] = min(dp[i], 1 + dp[j]);
    }

}

void prepare()
{
    // all strings of length 0 or 1 are palindromes
    for (int i = 0; i < MAXLEN; ++i) {
        pal[i][i] = true;
        pal[i][i + 1] = true;
    }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s", s);
        len = strlen(s);

        run_dp();

        printf("Case %d: %d\n", ++ncase, dp[0]);
    }

    return 0;
}
