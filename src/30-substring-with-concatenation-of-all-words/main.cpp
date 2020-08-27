#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> findSubstring(string str, vector<string>&& words) {
    // windowStart:          v
    //              barfoothefoobarman, [foo,bar] -> [0, 9]
    // windowEnd:            ^
    vector<int> resultIndices;
    if (words.empty() || str.size() < words[0].size() * words.size())
        return resultIndices;

    unordered_map<string, int> wordFreq;
    for (auto w : words)
        ++wordFreq[w];

    int wordsCount = words.size(), wordLength = words[0].length();
    for (int i = 0; i <= str.length() - wordsCount * wordLength; i++) {
        unordered_map<string, int> wordsSeen;
        for (int j = 0; j < wordsCount; j++) {
            int nextWordIndex = i + j * wordLength;

            string word = str.substr(nextWordIndex, wordLength);
            if (wordFreq.find(word) == wordFreq.end())
                break;

            ++wordsSeen[word];

            if (wordsSeen[word] > wordFreq[word])
                break;

            if (j + 1 == wordsCount)
                resultIndices.push_back(i);
        }
    }
    return resultIndices;
}

void testFindSubstring() {
    vector<int> res1 = { 0, 9 };
    assert(res1 == findSubstring("barfoothefoobarman", { "foo", "bar" }));
    vector<int> res2 = { 8 };
    assert(res2 == findSubstring("wordgoodgoodgoodbestword", { "word", "good", "best", "good" }));
    vector<int> res3 = { };
    assert(res3 == findSubstring("a", { "a", "a" }));
}

int main() {

    testFindSubstring();

	return 0;
}
