#include <cstdio>

int G;      // guess
char w[8];  // second word from each line of strings

int main()
{
    int bottom = 0;
    int top = 11;

    while (true) {
        scanf("%d", &G);
        if (G == 0) break;

        scanf("%*s%s", w);

        if (w[0] == 'h' && G < top)
            top = G;
        if (w[0] == 'l' && G > bottom)
            bottom = G;

        if (w[0] == 'o') {
            if (G <= bottom || G >= top)
                puts("Stan is dishonest");
            else
                puts("Stan may be honest");
            bottom = 0;
            top = 11;
        }
    }

    return 0;
}
