#include <cstdio>
#include <cstring>


#define MAXLEN 128


int n;
char word[MAXLEN];


void solve()
{
	int l = strlen(word);

	if (l <= 10)
		puts(word);
	else
		printf("%c%d%c\n", word[0], l - 2, word[l-1]);
}

int main()
{
	scanf("%d", &n);

	while (n--) {
		scanf("%s", word);
		solve();
	}

	return 0;
}
