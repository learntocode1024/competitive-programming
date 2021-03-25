// Original Author: misaka18931
// Date: 03-18-21
// tag:
// 

#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define MX 20

int rev[MX];

int kmp(string s, string t) {
  if (s.length() > t.length()) swap(s, t);
  const int n = s.size();
  const int m = t.size();
  for (int i = 0; i < n; ++i) rev[i] = 0;
  int maxl = 0;
  for (int i = 1; i < n; ++i) {
    int j = rev[i - 1];
    while (j && s[i] != s[j]) j = rev[j - 1];
    if (s[i] == s[j]) ++j;
    rev[i] = j;
  }
  for (int i = 0, j = 0; i < m; ++i) {
    while ((j || j >= n) && s[j] != t[i]) j = rev[j - 1];
    if (s[j] == t[i]) ++j;
    maxl = max(maxl, j);
  }
  return maxl;
}

void solve() {
  string s, t;
  cin >> s >> t;
  const int n = s.size();
  const int m = t.size();
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      ans = max(ans, kmp(s.substr(i, j), t));
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j <= m; ++j) {
      ans = max(ans, kmp(s, t.substr(i, j)));
    }
  }
  cout << m + n - 2 * ans << endl;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
