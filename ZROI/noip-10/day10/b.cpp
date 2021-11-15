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

#define fail { println(-1); return; }
const int N = 1005;
const int p = 1e9+7;
inline void red(i64 &x) { if (x >= p) x -= p; }
i64 inv[N<<1] = {0, 1};
i64 a[N][N], b[N][N];
i64 x[N], y[N];
int n, m;

inline void solve() {
  cin >> n >> m;
  i64 s = 0;
  FOR(i, 0, n) FOR(j, 0, m) cin >> a[i][j], red(s += a[i][j]);
  if (n == 1) {
    FOR(i, 1, m) if (a[0][i] != a[0][i - 1]) fail;
    cout << "1\n";
    FOR(i, 0, m - 1) cout << "0 ";
    cout << a[0][0] << '\n';
    return;
  }
  if (m == 1) {
    FOR(i, 1, n) if (a[i][0] != a[i - 1][0]) fail;
    cout << "1\n";
    FOR(i, 0, m - 1) cout << "0\n";
    cout << a[0][0] << '\n';
    return;
  }
  s = s * inv[n + m - 1] % p;
  FOR(i, 0, n) {
    FOR(j, 0, m) red(y[i] += a[i][j]);
    red(y[i] += p - s);
    y[i] = y[i] * inv[m - 1] % p;
  }
  FOR(j, 0, m) {
    FOR(i, 0, n) x[j] += a[i][j];
    red(x[j] += p - s);
    x[j] = x[j] * inv[n - 1] % p;
  }
  i64 sx = 0, sy = 0;
  FOR(i, 0, m) red(sx += x[i]);
  FOR(i, 0, n) red(sy += y[i]);
  if (sx != s || sy != s) fail;
  FOR(i, 0, n) FOR(j, 0, m) {
    b[i][j] = (y[i] + x[j] + p - a[i][j]) % p;
  }
  println(1);
  FOR(i, 0, n) FOR(j, 0, m) cout << b[i][j] << " \n"[j==m-1];
  return;
}

int main() {
  FOR(i, 2, N<<1) {
    inv[i] = inv[p % i] * (p - p / i) % p;
  }
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

