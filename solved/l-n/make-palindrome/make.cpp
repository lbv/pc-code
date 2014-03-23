#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;

#define MAXLEN 1000

#define Zero(v) memset(v, 0, sizeof(v))

typedef deque<char> CD;

// dp[i][j] will have the minimal number of characters to add to the word
// formed by the letters from the ith to the jth position, so it becomes a
// palindrome
int dp[MAXLEN][MAXLEN];

#define RIGHT 1
#define LEFT  2
#define MID   3
#define NONE  4
struct Node {
    char c;
    int t;  // type of node
    Node(char C, int T) : c(C), t(T) {}
    Node() {}
};

// Auxiliar data structure to rebuild the palindrome
Node info[MAXLEN][MAXLEN];

char word[MAXLEN + 1];
char pal[2*MAXLEN + 1];
int len;
int ans;

void build_palindrome(int i, int j, CD &q)
{
    if (i > j) return;
    if (info[i][j].t == NONE) {
        q.push_back(info[i][j].c);
        return;
    }

    switch (info[i][j].t) {
    case LEFT:
        build_palindrome(i, j - 1, q);
        break;
    case RIGHT:
        build_palindrome(i + 1, j, q);
        break;
    case MID:
        build_palindrome(i + 1, j - 1, q);
        break;
    }

    q.push_front(info[i][j].c);
    q.push_back(info[i][j].c);
}

void run_dp()
{
    Zero(dp);

    for (int i = 0; i < len; ++i)
        info[i][i] = Node(word[i], NONE);

    for (int s = 2; s <= len; ++s)
        for (int i = 0, j = i + s - 1; j < len; ++i, ++j) {
            if (dp[i + 1][j] < dp[i][j - 1]) {
                dp[i][j] = dp[i + 1][j] + 1;
                info[i][j] = Node(word[i], RIGHT);
            }
            else {
                dp[i][j] = dp[i][j - 1] + 1;
                info[i][j] = Node(word[j], LEFT);
            }

            if (word[i] == word[j] && dp[i+1][j-1] < dp[i][j]) {
                dp[i][j] = dp[i+1][j-1];
                info[i][j] = Node(word[i], MID);
            }
        }

    CD dq;
    build_palindrome(0, len - 1, dq);

    for (int i = 0, I = dq.size(); i < I; ++i)
        pal[i] = dq[i];
    pal[dq.size()] = 0;

    ans = dp[0][len - 1];
}

int main()
{
    while (true) {
        if (scanf("%s", word) != 1) break;
        len = strlen(word);

        run_dp();

        printf("%d %s\n", ans, pal);
    }

    return 0;
}
