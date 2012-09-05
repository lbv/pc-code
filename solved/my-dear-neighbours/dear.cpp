#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define MAXLINE 8192

typedef vector<int> IV;

int P;
char line[MAXLINE];

int count()
{
    int len = strlen(line);

    int cnt = 0;
    for (int i = 0; i < len; ++i) {
        if (! isdigit(line[i])) continue;

        ++cnt;
        while(isdigit(line[i])) ++i;
    }

    return cnt;
}

int main()
{
    int N;
    scanf("%d", &N);

    while (N--) {
        scanf("%d", &P);

        gets(line);  // skip newline
        int lo = P;

        IV neighbours[P + 1];

        for (int i = 1; i <= P; ++i) {
            gets(line);
            int n = count();
            neighbours[n].push_back(i);
            if (n < lo) lo = n;
        }

        printf("%d", neighbours[lo][0]);

        for (int i = 1, I = neighbours[lo].size(); i < I; ++i)
            printf(" %d", neighbours[lo][i]);
        putchar('\n');
    }

    return 0;
}
