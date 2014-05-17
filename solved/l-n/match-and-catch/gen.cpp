#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXLEN 5000
#define CRIT   (true)


char s1[MAXLEN + 1];
char s2[MAXLEN + 1];

void test_case()
{
	int len;
	len = CRIT ? MAXLEN : rand() % MAXLEN + 1;
	for (int i = 0; i < len; ++i) s1[i] = 'a' + (rand() % 26);
	len = CRIT ? MAXLEN : rand() % MAXLEN + 1;
	for (int i = 0; i < len; ++i) s2[i] = 'a' + (rand() % 26);
	printf("%s\n%s\n", s1, s2);
}

int main()
{
	srand(time(NULL));

	test_case();

	return 0;
}
