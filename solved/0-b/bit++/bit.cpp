#include <cstdio>


char op[4];
int x, n;


int main()
{
	scanf("%d", &n);

	while (n--) {
		scanf("%s", op);
		if (op[1] == '-') --x;
		else if (op[1] == '+') ++x;
	}
	printf("%d\n", x);

	return 0;
}
