// Original Author: misaka18931
// Date: 01-28-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

set<LL> a;
vector<LL> b;

void solve() {
  int n;
  LL r;
  cin >> n >> r;
  a.clear();
  b.clear();
  for (int i = 0; i < n; ++i) {
    LL t;cin >> t;
    a.insert(t);
    b.push_back(t);
  }
  bool ans = false;
  if (a.find(r) != a.end()) ans = true;
  bool b1, b2;
  b1 = b2 = false;
  for (auto i : b) {
    if (a.find(2 * i + 1) != a.end()) b1 = true;
    if (a.find(2 * i + 2) != a.end()) b2 = true;
  }
  ans = ans || b1 && b2;
  b1 = b2 = false;
  for (auto i : b) {
    if (a.find(2 * i - 1) != a.end())
      b1 = true;
    if (a.find(2 * i - 2) != a.end())
      b2 = true;
  }
  ans = ans || b1 && b2;
  print(ans);
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