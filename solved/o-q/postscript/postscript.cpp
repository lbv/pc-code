#include <cstdio>
#include <cstring>


char grid[60][61];
char cmd[8];
char str[64];

const char C5[3][512] = {
".***..****...****.****..*****.*****..****.*...*.*****."
"*...*.*...*.*...*.*...*.*.....*.....*.....*...*...*..."
"*****.****..*.....*...*.***...***...*..**.*****...*..."
"*...*.*...*.*.....*...*.*.....*.....*...*.*...*...*..."
"*...*.****...****.****..*****.*......***..*...*.*****.",

"..***.*...*.*.....*...*.*...*..***..****...***..****.."
"...*..*..*..*.....**.**.**..*.*...*.*...*.*...*.*...*."
"...*..***...*.....*.*.*.*.*.*.*...*.****..*...*.****.."
"*..*..*..*..*.....*...*.*..**.*...*.*.....*..**.*..*.."
".**...*...*.*****.*...*.*...*..***..*......****.*...*.",

".****.*****.*...*.*...*.*...*.*...*.*...*.*****......."
"*.....*.*.*.*...*.*...*.*...*..*.*...*.*.....*........"
".***....*...*...*..*.*..*.*.*...*.....*.....*........."
"....*...*...*...*..*.*..**.**..*.*....*....*.........."
"****...***...***....*...*...*.*...*...*...*****......."
};

char letters[27][5][6];


void reset_grid()
{
	for (int i = 0; i < 60; ++i)
		grid[0][i] = '.';
	for (int i = 1; i < 60; ++i)
		strncpy(grid[i], grid[0], 60);
}

void do_eop()
{
	for (int i = 0; i < 60; ++i)
		puts(grid[i]);
	putchar('\n');
	for (int i = 0; i < 60; ++i) putchar('-');
	puts("\n");
	reset_grid();
}

void do_font1(int r, int c)
{
	for (char *p = str; *p; ++p, ++c)
		if (*p != ' ' && 0 <= c && c < 60)
			grid[r][c] = *p;
}

void do_letter5(int idx, int r, int c)
{
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 6; ++j) {
			int p = i + r, q = j + c;
			if (0 <= p && p < 60 && 0 <= q && q < 60)
				grid[p][q] = letters[idx][i][j];
		}
}

void do_font5(int r, int c)
{
	for (char *p = str; *p; ++p, c += 6)
		if (*p != ' ')
			do_letter5(*p - 'A', r, c);
}

bool read_command()
{
	if (scanf("%s", cmd) != 1 || cmd[0] != '.') return false;
	if (cmd[1] == 'E') { do_eop(); return true; }

	char font;
	int row, col;
	scanf(" %*c%c %d", &font, &row);
	if (cmd[1] == 'P') scanf("%d", &col);
	scanf(" |%[^|]|", str);

	int width = (font == '1' ? 1 : 6) * strlen(str);
	if      (cmd[1] == 'L') col = 1;
	else if (cmd[1] == 'R') col = 61 - width;
	else if (cmd[1] == 'C') col = 31 - width/2;

	if      (font == '1') do_font1(row-1, col-1);
	else if (font == '5') do_font5(row-1, col-1);

	return true;
}

void prepare()
{
	for (int let = 0; let < 27; ++let) {
		int grp = let / 9;
		int elm = let % 9;

		int idx = 6*elm;
		for (int i = 0; i < 5; ++i, idx = 6*elm + i*6*9)
			for (int j = 0; j < 6; ++j, ++idx)
				letters[let][i][j] = C5[grp][idx];
	}
}

int main()
{
	prepare();
	reset_grid();
	while (read_command());

	return 0;
}
