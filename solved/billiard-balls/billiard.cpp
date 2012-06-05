#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> II;
typedef vector<II> IIV;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int L, W, n, k;
        scanf("%d%d%d%d", &L, &W, &n, &k);

        IIV pos;

        for (int i = 0; i < n; i++) {
            int x, y;
            char v, h;  // horizontal and vertical directions
            scanf("%d%d %c%c", &x, &y, &v, &h);
            if (h == 'E') x = x + k;
            else          x = abs(x - k);
            if (v == 'N') y = y + k;
            else          y = abs(y - k);
            div_t d = div(x, L);
            x = d.quot % 2 == 0 ? d.rem : L - d.rem;
            d = div(y, W);
            y = d.quot % 2 == 0 ? d.rem : W - d.rem;
            pos.push_back(II(x, y));
        }

        printf("Case %d:\n", ncase++);
        sort(pos.begin(), pos.end());
        cFor (IIV, p, pos)
            printf("%d %d\n", p->first, p->second);
    }

    return 0;
}
