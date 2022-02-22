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
const int N = 30;
i64 f[N][N], inv[N], cf[N][N];
float g[N][N], cg[N][N];
int n, p;

void w1() {
  g[1][1] = 1;
  FOR(i, 0, N) cg[i][0] = 1;
  FOR(i, 1, N) FOR(j, 1, i + 1) cg[i][j] = cg[i-1][j] + cg[i-1][j-1];
  FOR(i, 2, n + 1) FOR(j, 1, i) {
    FOR(d1, 1, i - j + 1) FOR(d2, 1, j + 1) {
      g[i][max(d1, d2 + 1)] += g[i-j][d1] * g[j][d2] * cg[i-2][j-1];
    }
  }
  float ans = 0;
  FOR(i, 1, n + 1) ans += i * g[n][i];
  FOR(i, 1, n) ans /= i;
  println(floor(ans + 0.5));
}

void w2() {
  f[1][1] = 1;
  FOR(i, 0, N) cf[i][0] = 1;
  FOR(i, 1, N) FOR(j, 1, i + 1) cf[i][j] = (cf[i-1][j] + cf[i-1][j-1])%p;
  FOR(i, 2, n + 1) FOR(j, 1, i) {
    FOR(d1, 1, i - j + 1) FOR(d2, 1, j + 1) {
      f[i][max(d1, d2 + 1)] =(f[i][max(d1, d2 + 1)] + f[i-j][d1] * f[j][d2] %p * cf[i-2][j-1] %p) % p;
    }
  }
  i64 ans = 0;
  FOR(i, 1, n + 1) ans = (ans + i * f[n][i]) % p;
  inv[1] = 1;
  FOR(i, 2, n) inv[i] = inv[p%i]*(p-p/i) % p;
  FOR(i, 2, n) ans = ans * inv[i] % p;
  println(ans);

}

inline void solve() {
  rd(n, p);
  w1(), w2();
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

