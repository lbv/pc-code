#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 50

int A[MAXN];  // Own karate team
int B[MAXN];  // Rival team

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int N;
        scanf("%d", &N);

        for (int i = 0; i < N; ++i)
            scanf("%d", &A[i]);
        for (int i = 0; i < N; ++i)
            scanf("%d", &B[i]);

        sort(A, A + N);
        sort(B, B + N);

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = N - 1; j >= 0; --j) {
                if (B[j] < 0) continue;

                if (A[i] > B[j]) {
                    ans += 2;
                    A[i] = B[j] = -1;
                    break;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (A[i] < 0) continue;
            for (int j = N - 1; j >= 0; --j) {
                if (B[j] < 0) continue;

                if (A[i] == B[j]) {
                    ++ans;
                    B[j] = -1;
                    break;
                }
            }
        }

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}
