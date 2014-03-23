#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


typedef vector<int> IV;
typedef vector<IV>  IVV;


int n;


void print_indent(int ind)
{
    for (int i = 0; i < ind; ++i) putchar(' ');
}

void gen_code(int indent, IV v, IVV vis, int i, int j)
{
    if (j >= n) {
        print_indent(indent);
        printf("writeln(%c", 'a' + v[0]);
        for (int k = 1; k < n; ++k)
            printf(",%c", 'a' + v[k]);
        puts(")");
        return;
    }

    int a = v[i], b = v[j];
    int p = i, q = j + 1;
    if (q >= n) ++p, q = p + 1;

    if (vis[a][b] == 1) {
        gen_code(indent, v, vis, p, q);
        return;
    }
    if (vis[a][b] == 2) {
        swap(v[i], v[j]);
        gen_code(indent, v, vis, p, q);
        return;
    }

    print_indent(indent);
    printf("if %c < %c then\n", 'a' + a, 'a' + b);
    vis[a][b] = 1;
    vis[b][a] = 2;
    gen_code(indent + 2, v, vis, p, q);

    print_indent(indent);
    puts("else");
    swap(v[i], v[j]);
    vis[b][a] = 1;
    vis[a][b] = 2;
    gen_code(indent + 2, v, vis, p, q);
}

void solve()
{
    puts("program sort(input,output);");
    puts("var");
    putchar('a');
    for (int i = 1; i < n; ++i)
        printf(",%c", 'a' + i);
    puts(" : integer;");
    puts("begin");
    printf("  readln(a");
    for (int i = 1; i < n; ++i)
        printf(",%c", 'a' + i);
    puts(");");

    IV ls;
    for (int i = 0; i < n; ++i)
        ls.push_back(i);

    IVV vis(n, IV(n));

    gen_code(2, ls, vis, 0, 1);

    puts("end.");
}

int main()
{
    int M;
    scanf("%d", &M);

    bool first = true;
    while (M--) {
        scanf("%d", &n);

        if (first) first = false;
        else       putchar('\n');

        solve();
    }

    return 0;
}
