#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

#define MAXLEN 1023

// dp[i][j] has the length of the longest palindromic subsequence in the
// range [i, j)
int dp[MAXLEN][MAXLEN + 1];

// ps[i][j] is the lexicographically lowest, longest palindromic subsequence
// from the range [i, j)
string ps[MAXLEN][MAXLEN + 1];

char str[MAXLEN + 1];
int len;

void run_dp()
{
    for (int i = 0; i < len; ++i) {
        dp[i][i + 1] = 1;
        ps[i][i + 1] = string();
        ps[i][i + 1].push_back(str[i]);
    }

    for (int l = 2; l <= len; ++l)
        for (int i = 0, j = i + l; j <= len; ++i, ++j) {
            if (str[i] == str[j - 1]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
                ps[i][j] = string();
                ps[i][j].push_back(str[i]);
                ps[i][j].append(ps[i + 1][j - 1]);
                ps[i][j].push_back(str[i]);
                continue;
            }

            if (dp[i][j - 1] > dp[i + 1][j]) {
                dp[i][j] = dp[i][j - 1];
                ps[i][j] = ps[i][j - 1];
                continue;
            }

            if (dp[i + 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i + 1][j];
                ps[i][j] = ps[i + 1][j];
                continue;
            }

            dp[i][j] = dp[i + 1][j];
            ps[i][j] = min(ps[i][j-1], ps[i+1][j]);
        }
}

int main()
{
    while (true) {
        if (scanf("%s", str) != 1) break;
        len = strlen(str);

        run_dp();

        printf("%s\n", ps[0][len].c_str());
    }

    return 0;
}
