#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXLEN 128
#define INF    1000


char A[MAXLEN], B[MAXLEN];
int la, lb;


int find_match(int j)
{
    char *a = A;
    char *b = B + j;

    while (*a && *b) {
        if (*a == *b) ++a;
        ++b;
    }

    if (! *a) return b - (B+j);
    return INF;
}

int solve()
{
    int ans = INF;

    for (int j = 0; j < lb; ++j)
        if (B[j] == A[0])
            ans = min(ans, find_match(j));

    return ans;
}

int main()
{
    int n;
    scanf("%d\n", &n);

    while (n--) {
        scanf("%s%s", A, B);
        la = strlen(A);
        lb = strlen(B);

        int ans = solve();
        if (ans == INF)
            puts("There is no match.");
        else
            printf("There is a match consisting of %d notes.\n", ans);
    }

    return 0;
}
