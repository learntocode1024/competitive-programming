// Original Author: misaka18931
// Date: 01-15-21
// tag: easy
// AC

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b)
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
}

void solve() {
  string a, b, c;
  cin >> a >> b;
  for (int i = 0; i < a.size() * b.size() / __gcd(a.size(), b.size()); ++i) {
    if (a[i % a.size()] == b[i % b.size()])
      c.push_back(a[i % a.size()]);
    else {
      c = "-1";
      break;
    }
  }
  cout << c LF;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  CLRBUF;
  return 0;
}