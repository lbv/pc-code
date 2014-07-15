#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXT 200


struct Area {
	int s, p;  // size, people in area

	bool operator<(const Area &x) const { return p < x.p; }
};


int T, P;
int grid[MAXT][MAXT];

int supplied, area, deficit, population;

// dp[i][j][k]: the sum of square of size k that has its lower-right corner
// at grid[i][j]
int dp[MAXT][MAXT][MAXT + 1];

Area as[MAXT * MAXT * MAXT];
int nas;


void run_dp()
{
	nas = 0;

	for (int i = 0; i < T; ++i)
		for (int j = 0; j < T; ++j) {
			dp[i][j][1] = grid[i][j];
			as[nas++] = (Area) { 1, grid[i][j] };
		}

	for (int k = 2; k <= T; ++k)
		for (int i = k-1; i < T; ++i)
			for (int j = k-1; j < T; ++j) {
				dp[i][j][k] = dp[i][j-1][k-1] + dp[i-1][j][k-1] -
					dp[i-1][j-1][k-2] + dp[i-k+1][j-k+1][1] + dp[i][j][1];
				as[nas++] = (Area) { k, dp[i][j][k] };
			}

	sort(as, as + nas);

	int size = 0, aux = nas;
	nas = 0;
	for (int i = 0; i < aux; ++i) {
		if (as[i].s < size) continue;
		if (as[i].s > size) size = as[i].s;
		as[nas++] = as[i];
	}
}

void solve()
{
	int idx = upper_bound(as, as + nas, (Area) { 0, P }) - as;

	if (idx == 0)
		supplied = 0, area = 0;
	else
		supplied = as[idx-1].p, area = as[idx-1].s;
	deficit = population-supplied;
}

int main()
{
	scanf("%d", &T);

	population = 0;
	for (int i = 0; i < T; ++i)
		for (int j = 0; j < T; ++j) {
			scanf("%d", &grid[i][j]);
			population += grid[i][j];
		}

	run_dp();

	bool first = true;
	while (true) {
		scanf("%d", &P);
		if (P == 0) break;

		if (first) first = false;
		else putchar('\n');

		solve();

		printf("City: Square Town\n"
		       "Power Supplied: %d consumer(s)\n"
		       "Covered Area: %d x %d block(s)\n"
		       "Power Deficit: %d consumer(s)\n",
			supplied, area, area, deficit);
	}

	return 0;
}
