#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;


#define MAXLEN 10


vector<string> ss;

char str[MAXLEN + 1];


bool cmp(const string &a, const string &b)
{
    if (a[1] != b[1]) return a[1] < b[1];
    int n = a.size(), m = b.size();
    char p = n >= 4 ? a[3] : ' ';
    char q = m >= 4 ? b[3] : ' ';
    if (p != q) return p < q;

    p = a[n-1], q = b[m-1];
    if (p != q) return p < q;

    p = a[0], q = b[0];
    if (p != q) return p < q;

    return a < b;
}

int main()
{
    while (true) {
        if (scanf("%s", str) != 1) break;
        ss.push_back(string(str));
    }

    sort(ss.begin(), ss.end(), cmp);
    for (int i = 0, I = ss.size(); i < I; ++i)
        printf("%s\n", ss[i].c_str());

    return 0;
}
