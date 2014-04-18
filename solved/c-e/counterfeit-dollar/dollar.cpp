#include <cstdio>
#include <cstring>


#define Clr(m) memset(m, 0, sizeof(m))


char left[3][16];
char right[3][16];
char balance[3];

bool coins[12];
bool good[12];


bool try_with(int coin, int w)
{
	for (int i = 0; i < 3; ++i) {
		int len1 = strlen(left[i]);
		int len2 = strlen(left[i]);
		char bal = balance[i];

		bool is_left  = strchr(left[i], 'A' + coin) != NULL;
		bool is_right = strchr(right[i], 'A' + coin) != NULL;

		if (len1 != len2) {
			if (bal == 'u' && (
				(is_right && w > 0 && len2 >= len1) ||
				(is_left && w < 0 && len1 <= len2))) return false;
			if (bal == 'd' && (
				(is_right && w < 0 && len2 <= len1) ||
				(is_left && w > 0 && len1 >= len2))) return false;
		}
		else {
			if (bal == 'e' && (is_left || is_right)) return false;
			else if (bal != 'e') {
				if (! is_left && ! is_right) return false;

				if (bal == 'u' && w > 0 && is_right) return false;
				if (bal == 'u' && w < 0 && is_left) return false;

				if (bal == 'd' && w < 0 && is_right) return false;
				if (bal == 'd' && w > 0 && is_left) return false;
			}
		}
	}

	return true;
}

void solve()
{
	for (int i = 0; i < 12; ++i)
		for (int j = -1; j <= 1; j += 2)
			if (try_with(i, j)) {
				printf("%c is the counterfeit coin and it is %s.\n",
				       'A' + i, j > 0 ? "heavy" : "light");
				return;
			}
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		for (int i = 0; i < 3; ++i)
			scanf("%s%s %c%*s", left[i], right[i], &balance[i]);

		solve();
	}

	return 0;
}
