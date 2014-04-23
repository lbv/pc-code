#include <cmath>
#include <cstdio>


typedef long long i64;


int SZ;
i64 P;

int row, col;


void solve()
{
	row = (SZ + 1) / 2;
	col = (SZ + 1) / 2;

	if (P == 1) return;

	i64 ring = ceil(sqrt(P));
	ring /= 2;

	i64 offset = P - ((2*ring - 1) * (2*ring - 1) + 1);
	i64 quart = ring * 2;

	if (offset < quart) {
		row += ring;
		col += ring - 1 - offset;
		return;
	}
	if (offset < 2*quart) {
		row += ring - 1 - (offset - quart);
		col += -ring;
		return;
	}
	if (offset < 3*quart) {
		row += -ring;
		col += -ring + 1 + (offset - 2*quart);
		return;
	}

	row += -ring + 1 + (offset - 3*quart);
	col += ring;
}

int main()
{
	while (true) {
		scanf("%d%lld", &SZ, &P);
		if (SZ == 0) break;

		solve();
		printf("Line = %d, column = %d.\n", row, col);
	}

	return 0;
}
