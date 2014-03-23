#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXLEN 100

#define Zero(v) memset(v, 0, sizeof(v))

// dp[i][j] will have the minimal number of characters to add to the word
// formed by the letters from the ith to the jth position, so it becomes a
// palindrome
int dp[MAXLEN][MAXLEN];

char word[MAXLEN + 1];
int len;
int ans;

void run_dp()
{
    Zero(dp);

    for (int s = 2; s <= len; ++s)
        for (int i = 0, j = i + s - 1; j < len; ++i, ++j) {
            dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;

            if (word[i] == word[j])
                dp[i][j] = min(dp[i][j], dp[i+1][j-1]);
        }

    ans = dp[0][len - 1];
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s", word);
        len = strlen(word);

        run_dp();

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}
