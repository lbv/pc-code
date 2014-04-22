#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 10000
#define MAXK 50
#define MOD  1000000

#define Clr(m) memset(m, 0, sizeof(m))
#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))


typedef int BitT;


//
// Binary Indexed Tree
//
#define MAXBIT (MAXN+1)
struct Bit {
	BitT f[MAXBIT + 1];
	int n;
	void init(int N) { n=N; Clr(f); }
	void add(int i, BitT v) {
		while (i <= n) {
			f[i] += v;
			if (f[i] >= MOD) f[i] %= MOD;
			i += GetFS(i);
		}
	}
	BitT query(int i) {
		BitT r = 0; for (;i; ClrFS(i)) r += f[i];
		if (r >= MOD) r %= MOD;
		return r;
	}
	BitT query(int from, int to) { return query(to) - query(from - 1); }
};

struct Bits {
	Bit up;  // # of K-peak charts that end going up to a certain height
	Bit dn;  // # of K-peak charts that end going down to a certain height
	Bit nt;  // # of K-peak charts that end neutrally (not up, not down)

	void init(int n) {
		up.init(n);
		dn.init(n);
		nt.init(n);
	}
};

struct Data {
	int s, r, n;  // SRT, rating, normalized rating
};

bool cmp_by_r(const Data &a, const Data &b) { return a.r < b.r; }
bool cmp_by_s(const Data &a, const Data &b) { return a.s < b.s; }


int N, K;
Data data[MAXN];

Bits bits[MAXK + 1];


int normalize(int x)
{
	x %= MOD;
	if (x < 0) x += MOD;
	return x;
}

int solve()
{
	sort(data, data + N, cmp_by_r);
	data[0].n = 1;
	for (int i = 1; i < N; ++i)
		if (data[i].r > data[i-1].r)
			data[i].n = data[i-1].n + 1;
		else
			data[i].n = data[i-1].n;
	int top = data[N-1].n;

	sort(data, data + N, cmp_by_s);

	for (int i = 0; i <= K; ++i) bits[i].init(top);

	for (int i = 0; i < N; ++i) {
		int h = data[i].n;

		for (int j = 0; j <= K; ++j) {
			Bits &cur = bits[j];

			int sum_up = -cur.up.query(h, h);
			int sum_dn = -cur.dn.query(h, h);
			int sum_nt = -cur.nt.query(h, h);

			sum_up += cur.up.query(h - 1) + cur.nt.query(h - 1);
			sum_dn += cur.dn.query(h + 1, top) + cur.nt.query(h + 1, top);

			if (j == 0)
				sum_nt += 1;
			else {
				Bits &pre = bits[j-1];

				sum_up += pre.dn.query(h - 1);
				sum_dn += pre.up.query(h + 1, top);
			}

			sum_up = normalize(sum_up);
			sum_dn = normalize(sum_dn);
			sum_nt = normalize(sum_nt);
			if (sum_up != 0) cur.up.add(h, sum_up);
			if (sum_dn != 0) cur.dn.add(h, sum_dn);
			if (sum_nt != 0) cur.nt.add(h, sum_nt);
		}
	}

	Bits &res = bits[K];
	int ans = res.up.query(top) + res.dn.query(top) + res.nt.query(top);
	if (K == 0) ++ans;
	return normalize(ans);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &N, &K);
		for (int i = 0; i < N; ++i) scanf("%d%d", &data[i].s, &data[i].r);

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
