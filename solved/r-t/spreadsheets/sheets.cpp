#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


char col[8];
char input[16];
int R, C;


void convert_from_rc()
{
	int len = 0;

	while (C != 0) {
		int v = C % 26;
		C /= 26;

		char d;
		if (v == 0) {
			d = 'Z';
			--C;
		}
		else
			d = 'A' - 1 + v;

		col[len++] = d;
	}
	col[len] = 0;
	for (int i = 0, j = len - 1; i < j; ++i, --j)
		swap(col[i], col[j]);

	printf("%s%d\n", col, R);
}

void convert_to_rc()
{
	C = 0;
	int len = strlen(col);

	for (int i = len - 1, exp = 1; i >= 0; --i, exp *= 26)
		C += exp * (col[i] - 'A' + 1);

	printf("R%dC%d\n", R, C);
}

int main()
{
	int n;
	scanf("%d", &n);

	while (n--) {
		scanf("%s", input);

		if (sscanf(input, "R%dC%d", &R, &C) == 2)
			convert_from_rc();
		else {
			sscanf(input, "%[A-Z]%d", col, &R);
			convert_to_rc();
		}
	}

	return 0;
}
