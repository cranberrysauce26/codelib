#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &a) {
    os << "[ ";
    for (auto e : a) os << e << " ";
    os << "]";
    return os;
}

template <typename T, typename V>
ostream &operator<<(ostream &os, const pair<T, V> &x) {
    return os << "{ " << x.first << ", " << x.second << " }";
}

/**
 * Status: Tested
 * Returns a vector p of length s.size() where p[i] is the length of the longest
 * proper prefix of s which is also a suffix of s[0...i]
**/
vector<int> kmp_table(const string &s) {
    vector<int> p(s.size(), 0);
    int len = 0;
    for (int i = 1; i < s.size(); ++i) {
        while (len && s[len] != s[i]) {
            len = p[len - 1];
        }
        if (s[len] == s[i]) {
            ++len;
        }
        p[i] = len;
    }
    return p;
}

/**
 * Status: Tested
 * Returns a vector of all the indices i such that haystack.substr(i, needle.size()) == needle
 */
vector<int> kmp(const string &haystack, const string &needle) {
    vector<int> matches;
    if (needle.size() > haystack.size()) return matches;
    auto p = kmp_table(needle);
    int j = 0;
    for (int i = 0; i < haystack.size(); ++i) {
        while (j && haystack[i] != needle[j]) {
            j = p[j - 1];
        }
        if (haystack[i] == needle[j]) {
            ++j;
        }
        if (j == needle.size()) {
            matches.push_back(i - needle.size() + 1);
            j = p[j - 1];
        }
    }
    return matches;
}

vector<int> naive_string_match(const string &haystack, const string &needle) {
    vector<int> matches;
    for (int i = 0; i < haystack.size() - needle.size() + 1; ++i) {
        if (haystack.substr(i, needle.size()) == needle) {
            matches.push_back(i);
        }
    }
    return matches;
}

int main() {
    string haystack = "a";
    string needle = "";
    auto matches = kmp(haystack, needle);
    cout << matches << "\n";
}