#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

struct Node {
    char g[9][9];
    int c;

    void print() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j)
                putchar(g[i][j]);
            puts("");
        }
    }
};

typedef stack<Node> NS;

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

void solve(Node &start, Node &sol)
{
    NS s;

    start.c = 0;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (start.g[i][j] != '.')
                ++start.c;

    s.push(start);
    while (! s.empty()) {
        Node nd = s.top();
        s.pop();

        if (nd.c == 81) {
            sol = nd;
            return;
        }

        int i, j;
        find_best_alternative(nd, i, j);

        for (char k = '1'; k <= '9'; ++k) {
            if (! valid_n(nd, i, j, k)) continue;

            Node nd2 = nd;
            nd2.g[i][j] = k;
            ++nd2.c;
            s.push(nd2);
        }
    }
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

        Node sol;
        solve(nd, sol);

        printf("Case %d:\n", ++ncase);

        sol.print();
    }

    return 0;
}
