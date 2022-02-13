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
const int N = 5005;
u32 a[N];
int n;
u32 f[N][N], g[N][N];

inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n + 1) {
    g[i][i] = a[i];
    FOR(j, i + 1, n + 1) {
      g[i][j] = max(g[i][j-1], a[j]);
    }
  }
  FOR(l, 1, n + 1) FOR(r, l + 2, n + 1) {
    f[l][r] = a[l] + a[r] + g[l + 1][(l + r) / 2];
  }
  FOR(l, 1, n + 1) FOR(r, l + 3, n + 1) chkmax(f[l][r], f[l][r-1]);
  int q;
  cin >> q;
  FOR(_, 0, q) {
    int l, r;
    rd(l, r);
    u32 ans = 0;
    FOR(i, l, r) {
      chkmax(ans, f[i][r]);
    }
    println(ans);
  }
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

