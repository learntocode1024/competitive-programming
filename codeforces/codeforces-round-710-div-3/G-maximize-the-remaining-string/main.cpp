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
#define MX

string s;
int cnt[26];
bool flag[26];

bool strless(int pos) {
  while (s[pos + 1] == s[pos]) ++pos;
  return s[pos + 1] > s[pos];
}

void solve() {
  cin >> s;
  for (int i = 0; i < 26; ++i) flag[i] = cnt[i] = 0;
  const int n = s.size();
  for (auto i : s)
    ++cnt[i - 'a'];
  s.push_back(0);
  for (int i = 0; i < n; ++i) {
    if (cnt[s[i] - 'a'] == 1) continue;
    if (flag[i] || strless(i)) {
      --cnt[s[i] - 'a'];
      s[i] = 0;
      continue;
    } else flag[i] = 1;
  }
  for (int i = 0; i < n; ++i) {
    if (s[i]) cout << s[i];
  }
  cout << endl;
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
