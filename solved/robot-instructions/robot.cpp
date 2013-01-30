#include <cstdio>


#define MAXN 100


int  n;
int  pos;
int  his[MAXN];  // his[i]: delta for i'th command
char comm[8];


int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);
        pos = 0;

        for (int i = 0; i < n; ++i) {
            scanf("%s", comm);

            if (comm[0] == 'L')
                his[i] = -1;
            else if (comm[0] == 'R')
                his[i] = 1;
            else {
                int c;
                scanf(" AS %d", &c);
                his[i] = his[c - 1];
            }

            pos += his[i];
        }

        printf("%d\n", pos);
    }

    return 0;
}
