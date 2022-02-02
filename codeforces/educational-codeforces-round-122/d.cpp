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

#define MULTI
const int N = 1e3+5, M = 2e4;
int d[N], qu[N], hd, tl;
int n, k;
int b[N], c[N];
int f[M], g[M];

inline void solve() {
  rd(n, k);
  int ck = 0, cc = 0;
  FOR(i, 1, n + 1) cin >> b[i], ck += d[b[i]];
  FOR(i, 1, n + 1) cin >> c[i], cc += c[i];
  if (ck <= k) println(cc);
  else {
    f[0] = 0;
    FOR(i, 1, k+1) f[i] = INT_MIN;
    FOR(i, 1, n + 1) {
      FOR(j, 0, k + 1) g[j] = f[j];
      FOR(j, 0, k + 1 - d[b[i]]) if (g[j] != INT_MIN) chkmax(f[j+d[b[i]]], g[j] + c[i]);
    }
    int mn = 0;
    FOR(i, 0, k + 1) chkmax(mn, f[i]);
    println(mn);
  }
}

int main() {
  FOR(i, 2, N) d[i] = 1e8;
  hd = tl = qu[1] = 1;
  int md = 0;
  while (hd <= tl) {
    int u = qu[hd++];
    for (int x = 1; x <= u; ++x) {
      int v = u + u / x;
      if (v >= N) continue;
      if (d[v] != 1e8) continue;
      d[v] = d[u] + 1;
      qu[++tl] = v;
    }
  }
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

