#include <cstdio>
#include <cstring>

struct Node {
    char g[9][9];
    int c;
    bool s;

    void print() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j)
                putchar(g[i][j]);
            puts("");
        }
    }
};

char ln[10];

bool valid_n(const Node &nd, int i, int j, char n)
{
    for (int k = 0; k < 9; ++k)
        if (nd.g[i][k] == n || nd.g[k][j] == n) return false;

    int I = i / 3 * 3;
    int J = j / 3 * 3;

    for (int a = 0; a < 3; ++a)
        for (int b = 0; b < 3; ++b)
            if (nd.g[I + a][J + b] == n) return false;

    return true;
}

void find_best_alternative(const Node &nd, int &r, int &c)
{
    int best = 10;

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            if (nd.g[i][j] != '.') continue;

            int alt = 0;
            for (char k = '1'; k <= '9'; ++k)
                if (valid_n(nd, i, j, k)) ++alt;

            if (alt < best) r = i, c = j, best = alt;
        }
}

void solve(Node &nd)
{
    if (nd.c == 81) { nd.s = true; return; }

    int i, j;
    find_best_alternative(nd, i, j);

    ++nd.c;
    for (char k = '1'; k <= '9' && ! nd.s; ++k) {
        if (! valid_n(nd, i, j, k)) continue;

        nd.g[i][j] = k;

        solve(nd);
    }
    if (nd.s) return;
    --nd.c;
    nd.g[i][j] = '.';
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        Node nd;

        for (int i = 0; i < 9; ++i) {
            scanf("%s", ln);
            strncpy(nd.g[i], ln, 9);
        }

        nd.c = 0;
        nd.s = false;
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                if (nd.g[i][j] != '.')
                    ++nd.c;

        solve(nd);

        printf("Case %d:\n", ++ncase);

        nd.print();
    }

    return 0;
}
