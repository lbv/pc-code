#include <cstdio>
#include <cstring>


#define MAXN 10
#define MAXLEN 12

#define Zero(v) memset((v), 0, sizeof(v))


int n;
char names[MAXN][MAXLEN + 1];
char name[MAXLEN + 1];
int money[MAXN];
int gifts[MAXN];


int get_idx(char *str)
{
    for (int i = 0; i < n; ++i)
        if (strcmp(names[i], str) == 0) return i;
    return -1;
}

int main()
{
    bool first = true;
    while (true) {
        if (scanf("%d", &n) != 1) break;
        for (int i = 0; i < n; ++i)
            scanf("%s", names[i]);

        Zero(gifts);

        for (int i = 0; i < n; ++i) {
            scanf("%s", name);
            int idx = get_idx(name);

            int friends;
            scanf("%d%d", &money[idx], &friends);
            if (friends == 0) continue;

            int spend = money[idx] / friends;

            for (int j = 0; j < friends; ++j) {
                scanf("%s", name);
                int f = get_idx(name);

                gifts[idx] -= spend;
                gifts[f]   += spend;
            }
        }

        if (first) first = false;
        else       putchar('\n');

        for (int i = 0; i < n; ++i)
            printf("%s %d\n", names[i], gifts[i]);
    }

    return 0;
}
