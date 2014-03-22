#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef long long i64;
typedef pair<i64, i64> II;
typedef vector<II> IIV;


IIV times;
int N;


int solve()
{
	sort(times.begin(), times.end());

	int ans = 0;

	int people = 0;

	For (IIV, t, times) {
		if (t->second == 0) --people;
		else ++people;

		if (people > ans) ans = people;
	}

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);

		times.clear();
		i64 x;
		for (int i = 0; i < N; ++i) {
			scanf("%lld", &x);
			times.push_back(II(x, 1));
		}
		for (int i = 0; i < N; ++i) {
			scanf("%lld", &x);
			times.push_back(II(x, 0));
		}

		if (ncase++ > 0) puts("");  // ughhh.....
		printf("%d", solve());
	}

	return 0;
}
