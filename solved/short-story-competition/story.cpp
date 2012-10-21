#include <cstdio>
#include <cstring>


#define MAXC 70


int N, L, C;
char word[MAXC + 1];


int main()
{
    while (true) {
        if (scanf("%d%d%d", &N, &L, &C) != 3) break;

        int chars = 0;
        int lines = 0;

        for (int i = 0; i < N; ++i) {
            scanf("%s", word);
            int len = strlen(word);

            if (chars > 0) ++chars;

            chars += len;
            if (chars > C) {
                ++lines;
                chars = len;
            }
        }

        if (chars > 0) ++lines;

        printf("%d\n", (lines + L - 1) / L);
    }

    return 0;
}
