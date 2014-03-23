#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXLEN 20

typedef unsigned long long u64;

char str[MAXLEN + 1];
int len;
int n;

void print_permutation(char *s, int l, u64 n)
{
    if (n == 1) {
        printf("%s", s);
        return;
    }

    // perm[i] is the number of permutations starting at i
    u64 perm[MAXLEN + 1];
    // count of occurrences of each character
    int cnt[26] = {0};

    u64 num = 1;
    u64 den = 1;
    for (int i = l - 1, j = 1; i >= 0; --i, ++j) {
        int c = s[i] - 'a';
        num *= j;
        den *= ++cnt[c];
        perm[i] = num / den;
    }

    if (perm[0] < n) {
        printf("Impossible");
        return;
    }

    int i = 0;
    while (i + 1 < l && perm[i + 1] >= n) putchar(s[i++]);

    int j = i + 1;
    while (s[i] >= s[j]) ++j;
    swap(s[i], s[j]);

    print_permutation(s + i, l - i, n - perm[i + 1]);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s%d", str, &n);
        len = strlen(str);

        sort(str, str + len);

        printf("Case %d: ", ++ncase);

        print_permutation(str, len, n);
        putchar('\n');
    }

    return 0;
}
