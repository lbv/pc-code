#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXLINE  8
#define MAXNODES 26

#define Zero(v) memset((v), 0, sizeof(v))


typedef vector<int> IV;


// Union-Find disjoint set
struct Set {
    IV s;
    Set(int n) { for (int i=0; i < n; ++i) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};


char line[MAXLINE];
bool vis[MAXNODES];


int main()
{
    int T;
    scanf("%d", &T);
    gets(line);  // skip newline
    gets(line);  // blank line

    int a, b, n;
    bool first = true;

    while (T--) {
        gets(line);

        n = line[0] - 'A' + 1;

        Set s(n);

        while (true) {
            if (gets(line) == NULL || ! isupper(line[0])) break;

            a = line[0] - 'A';
            b = line[1] - 'A';

            if (s.find(a) != s.find(b))
                s.merge(a, b);
        }

        Zero(vis);
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            int p = s.find(i);
            if (!vis[p]) {
                vis[p] = true;
                ++ans;
            }
        }

        if (first) first = false;
        else putchar('\n');

        printf("%d\n", ans);
    }

    return 0;
}
