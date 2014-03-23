#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN 1000000000
#define MAXD 60  // max number of digits of a Fi Binary Number

#define Zero(v) memset((v), 0, sizeof(v))


struct Fi {
    int f;  // fibonacci number
    int d;  // number of digits of the f's number
    Fi (int F, int D) : f(F), d(D) {}
    bool operator<(const Fi &x) const { return f < x.f; }
};
typedef vector<Fi> FV;
typedef FV::iterator FVi;


int n;
FV fis;

int num[MAXD];
int dig;


void solve()
{
    Zero(num);

    dig = 0;

    while (n != 0) {
        FVi it = upper_bound(fis.begin(), fis.end(), Fi(n, 0));
        --it;

        if (dig == 0) dig = it->d;

        num[it->d - 1] = 1;
        n -= it->f;
    }
}

void prepare()
{
    int a, b, c;
    fis.push_back(Fi(1, 1));
    fis.push_back(Fi(2, 2));

    a = 1, b = 2;
    int d = 3;
    while (true) {
        c = a + b;

        fis.push_back(Fi(c, d++));
        if (c > MAXN) break;

        a = b, b = c;
    }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);
        solve();
        for (int i = dig - 1; i >= 0; --i)
            putchar(num[i] + '0');
        putchar('\n');
    }

    return 0;
}
