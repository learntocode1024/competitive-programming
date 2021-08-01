// Original Author: misaka18931
// Date: 02-07-21
// tag:
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
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

string s;

void solve() {
  cin >> s;
  for (int i = 0; i < s.length(); ++i) {
    char &c = s[i];
    if (~i & 1)
      cout << ((c == 'a') ? 'b' : 'a');
    else
      cout << ((c == 'z') ? 'y' : 'z');
  }
  CLRBUF
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