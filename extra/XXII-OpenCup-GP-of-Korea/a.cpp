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

const int N = 1005;
i64 a[N][N], e[N][N];
int n;
i64 t[N];
i64 x[N], y[N];

inline void solve() {
  rd(n);
  FOR(i, 0, n) FOR(j, 0, n) rd(e[i][j]);
  i64 s = e[0][0] + e[n - 1][n - 1];
  s /= (n - 1) << 1;
  t[0] = s;
  t[n] = -s;
  FOR(i, 1, n) t[i] = -e[0][i] + e[0][i - 1];
  FOR(i, 0, n) x[i] = (t[i] - t[i + 1]) / 2;
  FOR(i, 1, n) t[i] = -e[i][0] + e[i - 1][0];
  FOR(i, 0, n) y[i] = (t[i] - t[i + 1]) / 2;
  FOR(i, 0, n) FOR(j, 0, n) {
    if (!y[i]) break;
    i64 c = min(y[i], x[j]);
    y[i] -= c;
    x[j] -= c;
    a[i][j] = c;
  }
  //FOR(i, 0, n) cerr << x[i] << " \n"[i==n-1];
  //FOR(i, 0, n) cerr << y[i] << " \n"[i==n-1];
  FOR(i, 0, n) FOR(j, 0, n) print(a[i][j], " \n"[j==n-1]);
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
