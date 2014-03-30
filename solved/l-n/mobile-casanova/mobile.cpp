#include <cstdio>
#include <cstdlib>
#include <cstring>


int N;

char sfrom[16], sto[16], num[16];
int from, to, curr;
int len;


void print_range()
{
	if (from == to) {
		printf("%s\n", sfrom);
		return;
	}

	if (len < 0) len = strlen(sfrom);

	for (int i = 0; i < len; ++i) {
		if (sfrom[i] != sto[i]) {
			printf("%s-%s\n", sfrom + i, sto + i);
			return;
		}
		putchar(sfrom[i]);
	}
}

void handle_range()
{
	if (from > 0) print_range();

	strcpy(sfrom, num);
	strcpy(sto, num);
	from = to = curr;
}

int main()
{
	int ncase = 0;
	while (true) {
		scanf("%d", &N);
		if (N == 0) break;

		printf("Case %d:\n", ++ncase);

		len = -1, from = -3, to = -2;

		while (N--) {
			scanf("%s", num);
			curr = atoi(num);

			if (curr == to + 1) {
				to = curr;
				strcpy(sto, num);
			}
			else handle_range();
		}
		handle_range();

		putchar('\n');
	}

	return 0;
}
