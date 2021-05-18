// Original Author: misaka18931
// Date: 01-02-21
// tag: STL-map, simulation
// AC

#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#define MX
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;
std::map<std::string, bool> a, b;

void solve() {
  std::string s;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    if (s[0] == '!') s = s.assign(s, 1, s.size() - 1), b[s] = true;
    else a[s] = true;
    if (a[s] && b[s]) {
      cout << s << endl;
      return;
    }
  }
  cout << "satisfiable" << endl;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
