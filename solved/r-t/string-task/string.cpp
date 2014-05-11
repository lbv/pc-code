#include <cctype>
#include <cstdio>
#include <cstring>


char str[128];
const char vowels[] = "aeiouy";


bool is_vowel(char c)
{
	return strchr(vowels, c) != NULL;
}

int main()
{
	scanf("%s", str);

	for (char *p = str; *p; ++p) {
		char c = tolower(*p);
		if (! is_vowel(c))
			printf(".%c", c);
	}
	putchar('\n');

	return 0;
}
