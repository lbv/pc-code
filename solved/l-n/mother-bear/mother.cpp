#include <cctype>
#include <cstdio>
#include <cstring>


#define MAXLEN 1024


char str[MAXLEN];
char san[MAXLEN];  // sanitized string


bool is_palindrome(char *s, int n)
{
	for (int i = 0, j = n - 1; i < j; ++i, --j)
		if (s[i] != s[j]) return false;
	return true;
}

bool solve()
{
	int len = 0;

	for (char *p = str; *p; ++p)
		if (isupper(*p)) san[len++] = tolower(*p);
		else if (islower(*p)) san[len++] = *p;

	return is_palindrome(san, len);
}

int main()
{
	while (true) {
		gets(str);
		if (strcmp("DONE", str) == 0) break;

		if (solve()) puts("You won't be eaten!");
		else puts("Uh oh..");
	}

	return 0;
}
