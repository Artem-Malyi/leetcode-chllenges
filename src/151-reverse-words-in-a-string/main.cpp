#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string reverseWords(string s) {
    string ans;
    string tmp;

    // trim and reverse the string in O(n) and reverse each word in O(m) where m is the number of non-space chars
    // time complexity: O(m + n)
    bool spaceFound = false;                      //     v
    for (int i = s.size() - 1; i >= 0; --i) {     // "the sky is blue"
        if (s[i] == ' ') {                        // "blue is sky" 
            if (spaceFound)                       // "" 
                continue;
            spaceFound = true;
            ans.append(tmp);                      // O(m)
            ans.push_back(s[i]);                  // O(n)
            tmp.clear();
        }
        else {
            if (spaceFound)
                spaceFound = false;
            tmp.insert(tmp.begin(), s[i]);
        }
    }
    if (!tmp.empty())
        ans.append(tmp);
    if (ans.size() && ans[0] == ' ')
        ans.erase(ans.begin());
    if (ans.size() && ans[ans.size() - 1] == ' ')
        ans.erase(ans.end() - 1);

    return ans;
}

void testReverseWords() {
    assert("blue is sky the" == reverseWords("the sky is blue"));
    assert("world! hello" == reverseWords("  hello world!  "));
    assert("example good a" == reverseWords("a good   example"));
}

int main() {

    testReverseWords();

	return 0;
}