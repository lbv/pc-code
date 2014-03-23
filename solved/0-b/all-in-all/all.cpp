#include <cstdio>
#include <cstring>

#define MAXLEN 1048575

char s1[MAXLEN + 1];
char s2[MAXLEN + 1];
int l1, l2;

bool is_subseq()
{
    int i, j;
    for (i = 0, j = 0; i < l1 && j < l2; ++j)
        if (s2[j] == s1[i]) ++i;

    return i == l1;
}

int main()
{
    while (true) {
        if (scanf("%s%s", s1, s2) != 2) break;
        l1 = strlen(s1);
        l2 = strlen(s2);

        if (is_subseq())
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}
