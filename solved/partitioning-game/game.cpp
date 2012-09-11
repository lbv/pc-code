#include <cstdio>
#include <cstring>


#define MAXN 10000

#define Zero(v) memset((v), 0, sizeof(v))


int n;
int pile;

int sg[MAXN + 1];
bool aux[MAXN + 1];


void prepare()
{
    for (int i = 3; i <= MAXN; ++i) {
        Zero(aux);

        for (int a = 1, b = i - 1; a < b; ++a, --b)
            aux[sg[a] ^ sg[b]] = true;

        for (int j = 0; aux[j]; ++j) ++sg[i];
    }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        int nim = 0;
        while (n--) {
            scanf("%d", &pile);
            nim ^= sg[pile];
        }

        printf("Case %d: ", ++ncase);
        if (nim == 0)
            puts("Bob");
        else
            puts("Alice");
    }

    return 0;
}
