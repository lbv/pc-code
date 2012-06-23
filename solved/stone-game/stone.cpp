#include <cstdio>

int N, P;

int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        int nim = 0;
        while (N--) {
            scanf("%d", &P);
            nim ^= P;
        }

        puts(nim ? "Yes" : "No");
    }

    return 0;
}
