#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100000

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;

int N, K;
int L[MAXN];


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

struct State {
	int L, groups;
	bool valid;

	State() {}
	State(int _L, int G, bool V): L(_L), groups(G), valid(V) {}
	bool operator<(const State &s) const {
		if (valid != s.valid) return valid;
		if (groups != s.groups) return groups < s.groups;
		return L >= s.L;
	}
	bool inRange(int x) {
		return valid && abs(L - x) <= K;
	}
};



// dp[i][j]: best state for L[0]..L[i], such that the last group needs j
// more people to become a valid group
State dp[MAXN][3];


int solve()
{
	if (N < 3) return -1;

	sort(L, L + N);
	Zero(dp);

	dp[0][2] = State(L[0] + K, 1, true);

	if (dp[0][2].inRange(L[1]))
		dp[1][1] = dp[0][2];

	for (int i = 2; i < N; ++i) {
		if (dp[i-2][2].inRange(L[i]))
			dp[i][0] = min(dp[i][0], dp[i-2][2]);

		if (dp[i-1][2].inRange(L[i]))
			dp[i][1] = min(dp[i][1], dp[i-1][2]);

		if (dp[i-1][1].inRange(L[i]))
			dp[i][0] = min(dp[i][0], dp[i-1][1]);

		if (dp[i-1][0].inRange(L[i]))
			dp[i][0] = min(dp[i][0], dp[i-1][0]);

		if (dp[i-1][0].valid)
			dp[i][2] = State(L[i] + K, dp[i-1][0].groups + 1, true);
	}

	return dp[N-1][0].valid ? dp[N-1][0].groups : -1;
}

int main()
{
	Reader rr;

	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		N = rr.next_u32();
		K = rr.next_u32();
		for (int i = 0; i < N; ++i) L[i] = rr.next_u32();

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
