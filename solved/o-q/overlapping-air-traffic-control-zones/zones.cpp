#include <cstdio>
#include <cstring>


#define MAXN 15
#define INF 1000000000


#define Clr(m) memset(m, 0, sizeof(m))


typedef unsigned int u32;
typedef long long i64;


struct Par {
	int x1, y1, z1, x2, y2, z2;

	void read() { scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2); }

	void intersect(const Par &p) {
		if (p.x1 > x1) x1 = p.x1;
		if (p.y1 > y1) y1 = p.y1;
		if (p.z1 > z1) z1 = p.z1;

		if (p.x2 < x2) x2 = p.x2;
		if (p.y2 < y2) y2 = p.y2;
		if (p.z2 < z2) z2 = p.z2;
	}

	i64 volume() const {
		if (x1 >= x2 || y1 >= y2 || z1 >= z2) return 0;
		return 1LL * (x2-x1) * (y2-y1) * (z2-z1);
	}
};


int n;
Par ps[MAXN];

// vols[i][j]: total sum of volumes from exactly j solids, that include ps[i]
i64 vols[MAXN][MAXN+1];


i64 incexc(u32 m)
{
	int cnt = 0;

	Par inter = (Par) { -INF, -INF, -INF, INF, INF, INF };

	int i = 0;
	for (u32 x = m; x; x >>= 1, ++i)
		if (x & 1) {
			inter.intersect(ps[i]);
			++cnt;
		}

	i64 v = inter.volume();

	i = 0;
	for (u32 x = m; x; x >>= 1, ++i)
		if (x & 1)
			vols[i][cnt] += v;

	return cnt % 2 != 0 ? v : -v;
}

i64 solve()
{
	Clr(vols);

	u32 all = (1 << n) - 1;
	i64 totalv = 0;

	for (u32 mask = 1; mask <= all; ++mask)
		totalv += incexc(mask);

	i64 ans = totalv;
	for (int i = 0; i < n; ++i) {
		i64 v = totalv;

		for (int c = 1, sgn = -1; c <= n; ++c, sgn *= -1)
			v += vols[i][c] * sgn;

		ans -= totalv - v;
	}

	return ans;
}

int main()
{
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; ++i) ps[i].read();

		printf("%lld\n", solve());
	}

	return 0;
}
