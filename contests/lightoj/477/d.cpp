/**
 * LightOJ Contest #477: Exam Ending Contest
 *
 * Problem D: WordFolding
 *
 * Keywords:
 *	 - strings
 *	 - greedy
 */

#include <cstdio>
#include <cstring>


char str[1024];


int solve()
{
	int len = strlen(str);
	int ans = 1;

	for (int i = 0; i < len; ++i) {
		char c = str[i];

		int tmp = 1;
		for (int j = i + 1; j < len; j += 2)
			if (str[j] == c)
				++tmp, --j;

		if (tmp > ans) ans = tmp;
	}

	return ans;
}

int main()
{
	while (true) {
		if (scanf("%s", str) != 1) break;
		printf("%d\n", solve());
	}

	return 0;
}
