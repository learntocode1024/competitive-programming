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
const int N = 15, K = 60;
int f[N][N][K];
int a[N], aa[N];
int g[K];
int n, k;
inline int s(int l, int r) { return aa[r] - aa[l-1]; };

inline void solve() {
  rd(n, k);
  if (n > 10) return;
  FOR(i, 1, n + 1) cin >> a[i], aa[i] = aa[i-1] + a[i];
  FOR(i, 1, n + 1) FOR(j, 1, n + 1) FOR(h, 1, k + 1) f[i][j][h] = INT_MIN;
  FOR(r, 1, n + 1) FOR(l, 1, r + 1) {
    if (l == 1) {
      int m = 1;
      FOR(i, l, r + 1) ROF(j, i, r + 1) g[m++] = s(i, j);
      sort(g + 2, g + m);
      reverse(g + 2, g + m);
      FOR(i, 2, m) g[i] += g[i - 1];
      FOR(i, 1, min(k + 1, m)) f[l][r][i] = g[i];
    } else {
      FOR(d, 1, l) FOR(t, l - 1, r) {
        int m = 2;
        g[1] = s(l, r);
        FOR(i, t + 1, r + 1) ROF(j, i, r + 1) if (!(i == l && j == r)) g[m++] = s(i, j);
        sort(g + 2, g + m);
        reverse(g + 2, g + m);
        FOR(i, 2, m) g[i] += g[i - 1];
        FOR(c, 2, k + 1) FOR(p, 1, min(m, c)) if (f[d][t][c - p] != INT_MIN) chkmax(f[l][r][c], f[d][t][c - p] + g[p]); 
      }
    }
  }
  int ans = INT_MIN;
  FOR(l, 1, n + 1) chkmax(ans, f[l][n][k]);
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

