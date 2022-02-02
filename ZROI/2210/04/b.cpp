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
const int N = 505;
const int p = 998244353;
inline void red(int &x) { if (x >= p) x -= p; }
int n;
int o[N], a[N];

namespace sub3 {
int f[N][N], g[N][N];
int c2(int x) {
  return (x - 1) * x / 2;
}
void work() {
  f[n][0] = 1;
  for (int i = 1; i <= n; ++i) {
    FOR(j, 0, n + 1) FOR(k, 0, n + 1) g[j][k] = f[j][k], f[j][k] = 0;
    FOR(j, 0, n + 1) FOR(k, 0, n + 1) {
      if (j > 1) red(f[j-2][k+2] += 1ll * c2(j) * g[j][k] % p);
      if (k > 1) red(f[j][k-2] += 1ll * c2(k) * g[j][k] % p);
      if (j && k) red(f[j-1][k] += 1ll * j * k * g[j][k] % p);
    }
  }
  println(f[0][0]);
}
}

namespace sub1 {
int cnt;

void dfs(int t) {
  if (t == n) {
    ++cnt;
    return;
  }
  for (int i = 0; i < n; ++i) {
    if (i == a[t+1]-1 || !o[i]) continue;
    for (int j = i + 1; j < n; ++j) {
      if (j == a[t+1]-1 || !o[j]) continue;
      --o[i];
      --o[j];
      dfs(t+1);
      ++o[i];
      ++o[j];
    }
  }
}

void work() {
  FOR(i, 0, n) o[i] = 2;
  dfs(0);
  println(cnt);
}
}

inline void solve() {
  cin >> n;
  bool s3 = 1;
  FOR(i, 1, n + 1) {cin >> a[i]; if (a[i] != 0) s3 = 0;}
  if (s3) {
    sub3::work();
  }
  else if (n <= 6) sub1::work();
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

