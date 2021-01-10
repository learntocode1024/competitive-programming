// Original Author: misaka18931
// Date: 01-08-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
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

void solve() {
  int n;
  cin >> n;
  if (n == 1){
    cout << '9' LF;
    return;
  }
  n -= 2;
  cout << "98";
  for (int i = 0; i < n; ++i) {
    cout << "9012345678"[i % 10];
  }
  cout LF;
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
