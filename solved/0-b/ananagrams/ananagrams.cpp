#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define MAXSZ  1000
#define MAXLEN 20

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef map<string, int> SIM;

typedef pair<string, int> SI;

typedef vector<string> SV;
typedef vector<SI>     SIV;


char word[MAXLEN + 1];

SIV dict;  // dictionary of original words, with their original index
SV norm;   // set of normalised words
SIM freq;  // map of normalised words with their frequency

int main()
{
    int idx = 0;
    while (true) {
        scanf("%s", word);
        if (word[0] == '#') break;

        dict.push_back(SI(string(word), idx));

        int len = strlen(word);
        for (int i = 0; i < len; ++i)
            if (islower(word[i]))
                word[i] = toupper(word[i]);

        sort (word, word + len);
        string nword(word);

        norm.push_back(nword);

        ++freq[nword];
        ++idx;
    }

    sort(dict.begin(), dict.end());

    cFor (SIV, e, dict) {
        if (freq[norm[e->second]] == 1)
            printf("%s\n", e->first.c_str());
    }

    return 0;
}
