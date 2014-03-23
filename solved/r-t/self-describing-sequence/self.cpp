#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 2000000000


typedef unsigned int   u32;
typedef pair<int, int> II;
typedef vector<int>    IV;
typedef vector<II>     IIV;
typedef IIV::iterator  IIVi;


IV seq;
IIV mseq;
int n;

int golomb(u32 n)
{
    static int nxt = 3;

    while (n > seq.size() - 1) {
        int times = seq[nxt];

        for (int i = 0; i < times; ++i)
            seq.push_back(nxt);
        ++nxt;
    }

    return seq[n];
}

void prepare()
{
    seq.push_back(0);
    seq.push_back(1);
    seq.push_back(2);
    seq.push_back(2);

    mseq.push_back(II(1, 1));
    mseq.push_back(II(2, 2));

    II m(2, 2);

    while (m.first <= MAXN) {
        m = II(m.first + golomb(m.second), m.second + 1);
        mseq.push_back(m);
    }
}

int main()
{
    prepare();

    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        IIVi it = upper_bound(mseq.begin(), mseq.end(), II(n, MAXN));
        --it;
        printf("%d\n", it->second);
    }

    return 0;
}
