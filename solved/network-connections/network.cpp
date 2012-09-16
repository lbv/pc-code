#include <cstdio>
#include <vector>
using namespace std;


#define MAXLINE 128


typedef vector<int> IV;


// Union-Find disjoint set
struct Set {
    IV s;
    Set(int n) { for (int i=0; i < n; ++i) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};


char line[MAXLINE];
int n;

int main()
{
    int T;
    scanf("%d", &T);

    bool first = true;

    while (T--) {
        scanf("%d", &n);
        gets(line);

        Set s(n + 1);

        char type;
        int a, b;

        int suc = 0, uns = 0;

        while (true) {
            if (gets(line) == NULL) break;
            if (sscanf(line, " %c %d%d", &type, &a, &b) != 3) break;

            if (type == 'c')
                s.merge(a, b);
            else {
                if (s.find(a) == s.find(b))
                    ++suc;
                else
                    ++uns;
            }
        }

        if (first) first = false;
        else putchar('\n');

        printf("%d,%d\n", suc, uns);
    }

    return 0;
}
