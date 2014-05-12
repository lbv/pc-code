#include <cstdio>


int n;


int main()
{
	scanf("%d", &n);

	int officers = 0;
	int crimes = 0;

	for (int i = 0; i < n; ++i) {
		int ev;
		scanf("%d", &ev);

		if (ev >= 0) {
			officers += ev;
			continue;
		}

		if (officers > 0)
			--officers;
		else
			++crimes;
	}
	printf("%d\n", crimes);

	return 0;
}
