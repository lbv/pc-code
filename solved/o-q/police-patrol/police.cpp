#include <cstdio>


#define MAXN 1000000


typedef long long i64;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar(); }
    void skip() { while (0 <= b && b <= 32) read(); }

    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; 48<=b&&b<=57; read()) v = v*10 + b-48; return s ? -v : v; }
};


int n, m;
int xs[MAXN];


i64 solve()
{
	i64 ans = 0;
	int med = n / 2;

	for (int i = 0; i < med; i += m)
		ans += 2LL * (xs[med] - xs[i]);

	for (int i = n - 1; i > med; i -= m)
		ans += 2LL * (xs[i] - xs[med]);

	return ans;
}

int main()
{
	Reader rr;
	n = rr.next_int();
	m = rr.next_int();
	for (int i = 0; i < n; ++i) xs[i] = rr.next_int();

	printf("%lld\n", solve());

	return 0;
}
