#include <cstdio>
#include <cstring>


#define MAXLEN 20000


char in[MAXLEN + 1];
char out[MAXLEN + 1];


char translate(char x)
{
	if (x == 'A') return 'Z';
	if (x == 'a') return 'z';

	if ('b' <= x && x <= 'z') return x-1;
	if ('B' <= x && x <= 'Z') return x-1;
	return x;
}

void rec_decode(int from, int to, int len)
{
	if (len == 0) return;

	int half1 = (len-1) / 2;
	out[to + half1] = translate(in[from]);

	int half2 = (len+1) / 2;
	rec_decode(from + 1, to, half2 - 1);
	rec_decode(from + half2, to + half2, len - half2);
}

void decode()
{
	int n = strlen(in);
	out[n] = 0;

	rec_decode(0, 0, n);
}

int main()
{
	while (gets(in) != NULL) {
		decode();
		puts(out);
	}

	return 0;
}
