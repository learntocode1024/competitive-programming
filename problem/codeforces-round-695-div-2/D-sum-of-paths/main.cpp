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
#define MX 5005
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

LL fib[MX];
LL a[MX];
LL c[MX];
LL ans = 0;

void solve() {
  LL pos, t;
  cin >> pos >> t;
  ans = (ans + c[pos] * (t - a[pos]) % mod) % mod;
  if (ans < 0) ans = mod + ans;
  cout << ans << endl;
  a[pos] = t;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int n, k;
  cin >> n >> k;++k;
  int T = 1;
  cin >> T;
  fib[0] = fib[1] = 1;
  for (int i = 2; i <= k; ++i) {
    fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
  }
  c[1] = fib[k - 1] * 2;
  for (int i = 2; i < k; ++i) {
    if (k - 1 == 2 * i) {
      c[1] = (c[1] + fib[i - 1]) % mod;
      continue;
    }
    c[1] = (c[1] + fib[k - i] + fib[i - 1]) % mod;
  }
  c[n] = c[1];
  c[2] = fib[k] * 2;
  for (int i = 2; i < k; ++i) {
    if (k - 1 == 2 * i) {
      c[2] = (c[2] + fib[i]) % mod;
      continue;
    }
    c[2] = (c[2] + fib[k - i + 1] + fib[i]) % mod;
  }
  for (int i = 3; i < n; ++i) {
    c[i] = c[2];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    ans = (ans + c[i] * a[i] % mod) % mod;
  }
  while (T--) {
    solve();
  }
  return 0;
}
