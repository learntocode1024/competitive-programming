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
long double f[N][N], g[N][N], C[N][N];
int n, d, r;
inline void solve() {
  FOR(i, 0, N) C[i][0] = 1;
  FOR(i, 1, N) FOR(j, 1, i + 1) {
    C[i][j] = C[i-1][j] + C[i-1][j-1];
  }
  rd(n, d, r);
  f[0][n] = 1;
  FOR(i, 0, d + 1) FOR(j, 1, n + 1) {
    FOR(k, 1, min(j, d - i) + 1) {
      f[i+k][k] += f[i][j] * C[j][k];
      g[i+k][k] += (g[i][j] + min(k, r) * f[i][j]) * C[j][k];
    }
  }
  long double p = 0, q = 0;
  FOR(i, 1, n + 1) p += g[d][i], q += f[d][i];
  cout << setprecision(7) << p/q+r << '\n';
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

