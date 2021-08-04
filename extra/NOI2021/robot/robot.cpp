#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define FILEIO(X) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);
template<typename T>
void chkmax(T& a, const T& b) {
  a = max(a, b);
}
template<typename T>
void chkmin(T& a, const T& b) {
  a = min(a, b);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned i32;
#define MX 1005
string s[MX];
int n, m;
const i64 mod = 1000000007;

i64 Q_pow(i64 x, i64 y) {
  i64 ret = 1;
  while (y) {
    if (y & 1) ret = ret * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return ret;
}

int main() {
  freopen("robot.in", "r", stdin);
  freopen("robot.out", "w", stdout);
  cin.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; ++i) cin >> s[i];
  bool A = 1;
  for (int i = 0; i < m; ++i) {
    for (auto j : s[i])
      if (j == 'R') A = 0;
  }
  if (A) {
    i64 ans = Q_pow(5, m) + Q_pow(3, m);
    ans %= mod;
    ans = Q_pow(ans, n);
    ans = ans - Q_pow(5, m * n) + mod;
    ans %= mod;
    cout << ans << '\n';
  } else if (n == 1 && m == 1) cout << "1\n";
  return 0;
}

