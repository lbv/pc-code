#include <cstdio>


#define MAXN 49


struct Set {
	int s[MAXN];
	Set() {}
	void init(int n) { for (int i=0; i < n; ++i) s[i] = i; }
	int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
	void merge(int i, int j) { s[find(i)] = find(j); }
};


Set s;
int n, m;

// groups of 1 or 2
int g2[MAXN];
int g1[MAXN];
int n1, n2;

int cnt[MAXN];
bool vis[MAXN];


void print_group(int id)
{
	for (int i = 1; i <= n; ++i)
		if (s.find(i) == id)
			printf("%d ", i);
	putchar('\n');
}

void solve()
{
	for (int i = 1; i <= n; ++i)
		++cnt[s.find(i)];

	bool has_sol = true;

	for (int i = 1; i <= n; ++i) {
		if (cnt[i] > 3) has_sol = false;
		else if (cnt[i] == 2) g2[n2++] = i;
		else if (cnt[i] == 1) g1[n1++] = i;
	}

	if (n2 > n1) has_sol = false;

	if (! has_sol) {
		puts("-1");
		return;
	}

	for (int i = 0; i < n2; ++i) {
		int a = g2[i];
		int b = g1[--n1];
		s.merge(a, b);
	}

	for (int i = 0; i < n1; i += 3) {
		s.merge(g1[i], g1[i + 1]);
		s.merge(g1[i], g1[i + 2]);
	}

	for (int i = 1; i <= n; ++i) {
		int id = s.find(i);
		if (! vis[id]) {
			print_group(id);
			vis[id] = true;
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	s.init(n + 1);

	while (m--) {
		int a, b;
		scanf("%d%d", &a, &b);
		s.merge(a, b);
	}

	solve();

	return 0;
}
