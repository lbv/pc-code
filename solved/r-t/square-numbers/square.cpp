#include <cstdio>
#include <cstring>


#define MAXB 100000

#define Zero(v) memset((v), 0, sizeof(v))
#define GetFS(b) ((b) & -(b))


const int MAX_BIT = MAXB;


typedef long long i64;


struct Bit {
    int f[MAX_BIT + 1]; int n;
    void init(int N) { n=N; Zero(f); }
    void add(int i, int v) { while (i <= n) { f[i] += v; i += GetFS(i); } }
    int query(int i) {
        int r = 0; while (i) { r += f[i]; i -= GetFS(i); } return r; }
};


Bit tree;

int a, b;


void prepare()
{
    tree.init(MAXB);
    int n = 1;
    while (true) {
        i64 n2 = 1LL * n * n;
        if (n2 > MAXB) break;
        tree.add(n2, 1);
        ++n;
    }
}

int main()
{
    prepare();

    while (true) {
        scanf("%d%d", &a, &b);
        if (a == 0 && b == 0) break;
        printf("%d\n", tree.query(b) - tree.query(a - 1));
    }

    return 0;
}
