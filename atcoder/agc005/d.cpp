#include <bits/stdc++.h>
using namespace std;
template<typename T>
void rd(T &a) {
  cin >> a;
}
template<typename A, typename... B>
void rd(A &a, B& ...b) {
  cin >> a;
  rd(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 2005;
const int p = 924844033;
int fac[N] = {1, 1};
int f[N][N], h[N<<1][N];
int n, k;

inline void solve() {
  rd(n, k);
  FOR(i, 2, n + 1) fac[i] = 1ll * fac[i - 1] * i % p;
  f[0][0] = f[1][0] = f[1][1] = 1;
  FOR(i, 2, n + 1) FOR(j, 0, (i + 1) / 2 + 1) {
    f[i][j] = f[i - 1][j];
    if (i > 1 && j > 0) f[i][j] += f[i - 2][j - 1];
    f[i][j] %= p;
  }
  h[0][0] = 1;
  FOR(i, 1, k + 1) FOR(j, 0, n + 1) {
    int s = (n - i) / k;
    for (int t = 0; t <= s && j - t >= 0; ++t) {
      h[i][j] = (h[i][j] + 1ll * h[i - 1][j - t] * f[s][t]) % p;
    }
  }
  FOR(i, 1, k + 1) FOR(j, 0, n + 1) {
    int s = (n - i) / k;
    for (int t = 0; t <= s && j - t >= 0; ++t) {
      h[i + k][j] = (h[i + k][j] + 1ll * h[i + k - 1][j - t] * f[s][t]) % p;
    }
  }
  i64 ans = 0;
  FOR(i, 0, n + 1) {
    if (i & 1) ans = (ans + p - 1ll * fac[n - i] * h[k<<1][i] % p) % p;
    else ans = (ans + 1ll * fac[n - i] * h[k<<1][i]) % p;
  }
  println(ans);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
  solve();
  return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */

