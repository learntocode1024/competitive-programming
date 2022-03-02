// Original Author: misaka18931
// Date: 02-18-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 55
using namespace std;

void solve() {
  int n;
  cin >> n;
  int ans = 0;
  int a, b;
  cin >> a;
  for (int i = 1; i < n; ++i, a = b) {
    cin >> b;
    if (a / b < 2 || b / a < 2) continue;
    
  }
  
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