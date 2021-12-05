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

const int N = 1.2e5, D = 1e6+5;
const i64 inf = 1e13;
i64 r[N];
i64 s[N];
i64 p[N<<1], g[N<<1];
int n, m, d;
i64 ret;
i64 dif[B];

inline void solve() {
  rd(n, m, d);
  FOR(i, 0, m + 1) cin >> r[i];
  FOR(i, 0, m) cin >> s[i];
  i64 ans = 0;
  int c = n / 2;
  int nn = 2 * m + 2;
  p[0] = -inf;
  FOR(i, 1, m + 1) p[i] = -r[m + 1 - i];
  FOR(i, m + 1, nn - 1) p[i] = r[i - m] + 1;
  p[nn - 1] = inf;
  g[0] = 0;
  FOR(i, 1, m + 1) g[i] = s[m - i];
  FOR(i, m + 1, nn - 1) g[i] = s[i - m];
  g[nn - 1] = 0;
  FOR(i, 0, n) {
    i64 x = 1ll * (i - c) * d;
    int o = upper_bound(p, p + nn, x) - p - 1;
    ans += g[o];
    ++o;
    while (o < nn && p[o] - x <= d) {
      dif[p[o] - x] += g[o] - g[o - 1];
      ++o;
    }
  }
  ret = ans;
  FOR(i, 0, d + 1) {
    ans += dif[i];
    chkmax(ret, ans);
  }
  println(ret);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
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

