#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXLEN 1000

#define Zero(v) memset((v), 0, sizeof(v))


// dp[i][j] contains the length of the LCS from A(0, i) and B(0, j)
int dp[MAXLEN + 1][MAXLEN +1];

char A[MAXLEN + 1];
char B[MAXLEN + 1];
int a, b;  // length of strings


void run_dp()
{
    Zero(dp);

    for (int i = 1; i <= a; ++i)
        for (int j = 1; j <= b; ++j) {
            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;

            dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
}

int main()
{
    while (true) {
        if (gets(A) == NULL || gets(B) == NULL) break;
        a = strlen(A);
        b = strlen(B);

        run_dp();

        printf("%d\n", dp[a][b]);
    }

    return 0;
}
