#include <cctype>
#include <cstdio>
#include <string>
using namespace std;


#define MAXLINE 120

#define AC 0
#define PE 1
#define WA 2


int n, m;
string judge;
string input;
char line[MAXLINE + 1];


int solve()
{
    if (judge == input) return AC;
    string num1, num2;

    for (int i = 0, I = judge.size(); i < I; ++i)
        if (isdigit(judge[i]))
            num1.push_back(judge[i]);

    for (int i = 0, I = input.size(); i < I; ++i)
        if (isdigit(input[i]))
            num2.push_back(input[i]);

    if (num1 == num2) return PE;

    return WA;
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;
        gets(line);

        judge.clear();
        for (int i = 0; i < n; ++i) {
            gets(line);
            judge.append(line);
            judge.push_back('|');
        }
        scanf("%d", &m);
        gets(line);

        input.clear();
        for (int i = 0; i < m; ++i) {
            gets(line);
            input.append(line);
            input.push_back('|');
        }

        printf("Run #%d: ", ++ncase);

        int ans = solve();
        if (ans == AC)
            puts("Accepted");
        else if (ans == PE)
            puts("Presentation Error");
        else
            puts("Wrong Answer");
    }

    return 0;
}
