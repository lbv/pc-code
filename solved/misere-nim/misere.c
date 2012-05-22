#include <stdio.h>

int main(void) {
    int T, ncase, k, nim, x, allones;

    scanf("%d", &T);
    for (ncase = 1; ncase <= T; ncase++) {
        scanf("%d", &k);

        nim = 0;
        allones = 1;
        while (k--) {
            scanf("%d", &x);
            if (x != 1) allones = 0;
            nim ^= x;
        }
        if (allones) nim = !nim;

        printf("Case %d: %s\n", ncase, nim == 0 ? "Bob" : "Alice");
    }

    return 0;
}
