#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXSTR 100
#define MAXLEN 100


char ss[MAXSTR][MAXLEN+1];
int ls[MAXSTR];
int n, maxlen;

char rot[MAXLEN][MAXSTR+1];


void rotate()
{
	memset(rot, ' ', sizeof(rot));

	int rows = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < ls[i]; ++j)
			rot[j][n-1-i] = ss[i][j];

		for (int j = ls[i]; j < maxlen; ++j)
			rot[j][n-1-i] = j >= rows ? 0 : ' ';

		rows = max(rows, ls[i]);
	}

	for (int j = 0; j < ls[0]; ++j)
		rot[j][n] = 0;
}

int main()
{
	n = 0;
	for (int i = 0; gets(ss[i]); ++i)
		ls[n++] = strlen(ss[i]);
	maxlen = *max_element(ls, ls + n);

	rotate();

	for (int i = 0; i < maxlen; ++i) puts(rot[i]);

	return 0;
}
