#include <cstdio>
#include <vector>
using namespace std;


#define RFor(t,i,c) for(t::reverse_iterator i=(c).rbegin(); i!=(c).rend(); ++i)


typedef vector<int> IV;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
    bool has_next() { skip(); return b > 0; }
};


IV ns;
int n;


// Calculates LIS, returns the length of the LIS and store lengths for each
// element of seq in ls
int lis(IV &seq, IV &ls)
{
    IV I(n + 1);
    ls = IV(n);
    int len = 0;
    for (int i = 0; i < n; ++i) {
        int lo = 1, hi = len;
        while (lo <= hi) {
            int m = (lo + hi) / 2;
            if (I[m] < seq[i]) lo = m + 1;
            else hi = m - 1;
        }
        I[lo] = seq[i], ls[i] = lo;
        if (len < lo) len = lo;
    }
    return len;
}

void print_lis(int len, IV &ls)
{
    IV lis;

    for (int i = n - 1; i >= 0; --i)
        if (ls[i] == len) {
            lis.push_back(ns[i]);
            --len;
        }

    RFor (IV, num, lis)
        printf("%d\n", *num);
}

int main()
{
    Reader rr;
    while (rr.has_next())
        ns.push_back(rr.next_int());
    n = ns.size();

    IV ls;
    int len = lis(ns, ls);
    printf("%d\n-\n", len);
    print_lis(len, ls);

    return 0;
}
