#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXLEN 26

int N, K;
char seq[MAXLEN + 1];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &N, &K);

        char c = 'A';
        for (int i = 0; i < N; ++i, ++c)
            seq[i] = c;
        seq[N] = 0;

        printf("Case %d:\n", ++ncase);
        for (int i = 0; i < K; ++i) {
            printf("%s\n", seq);

            if (! next_permutation(seq, seq + N)) break;
        }
    }

    return 0;
}
