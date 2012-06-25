#include <cstdio>

int k;
const int res[14] = {
    0,
    2,
    7,
    5,
    30,
    169,
    441,
    1872,
    7632,
    1740,
    93313,
    459901,
    1358657,
    2504881
};

int main()
{
    while (true) {
        scanf("%d", &k);
        if (k == 0) break;

        printf("%d\n", res[k]);
    }

    return 0;
}

#if 0

#include <cstdio>
#include <list>
using namespace std;

typedef list<int> IL;
typedef IL::iterator ILi;

int k;
IL joseph;

ILi get_it(int p)
{
    ILi it = joseph.begin();
    while (p--)
        ++it;
    return it;
}

bool try_joseph(int m)
{
    int sz = 2*k;
    joseph.clear();
    for (int i = 0; i < sz; ++i)
        joseph.push_back(i);

    int removed = 0;
    int pos = 0;
    while (true) {
        pos = (pos + m - 1) % sz;
        ILi it = get_it(pos);

        if (*it < k) return false;
        joseph.erase(it);
        --sz;
        if (pos == sz) pos = 0;
        ++removed;

        if (removed == k) return true;
    }
    return false;
}
int solve()
{
    for (int m = 1; ; ++m)
        if (try_joseph(m)) return m;
    return -1;
}

int main()
{
    while (true) {
        scanf("%d", &k);
        if (k == 0) break;


        printf("%d\n", solve());
    }

    return 0;
}

#endif
