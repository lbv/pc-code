#include <cstdio>


#define LINE 25
#define MAXN 12


char line[LINE + 1];
int  spaces[MAXN];
int  N;


int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;
        gets(line);

        int lo = LINE;
        for (int i = 0; i < N; ++i) {
            int s = 0;
            gets(line);
            for (int j = 0; j < LINE; ++j)
                if (line[j] == ' ') ++s;

            if (s < lo) lo = s;
            spaces[i] = s;
        }

        int ans = 0;
        for (int i = 0; i < N; ++i)
            ans += spaces[i] - lo;

        printf("%d\n", ans);
    }

    return 0;
}
