#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> reorderLogFiles(vector<string>& logs) {
    vector<string> digitLogs, letterLogs;
    for (string& s : logs) {
        int i = 0;
        while (s[i] != ' ')
            ++i;
        if (isalpha(s[i + 1]))
            letterLogs.push_back(s.substr(i + 1) + " " + s.substr(0, i)); // move identifier to the end of the string
        else
            digitLogs.push_back(s);
    }

    sort(letterLogs.begin(), letterLogs.end()); // sort letterLogs lexicographically

    for (string& s : letterLogs) {
        int i = s.size() - 1;
        while (s[i] != ' ')
            --i;
        s = s.substr(i + 1) + " " + s.substr(0, i); // return the identifier to the beginning of the string
    }

    for (string& s : digitLogs)
        letterLogs.push_back(s); // append digitLogs array to the letterLogs

    return letterLogs;
}

void testReorderLogFiles() {
    vector<string> input1 = { "dig1 8 1 5 1", "let1 art can", "dig2 3 6", "let2 own kit dig", "let3 art zero" };
    vector<string> output1 = { "let1 art can", "let3 art zero", "let2 own kit dig", "dig1 8 1 5 1", "dig2 3 6" };
    assert(output1 == reorderLogFiles(input1));
}

int main() {

    testReorderLogFiles();

	return 0;
}
