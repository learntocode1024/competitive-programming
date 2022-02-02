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
const int N = 3005;
const int inf = 1e8;
int n, m;
pii _A[N], _B[N];
int a[N], p[N], b[N], q[N];
int dp[N][N], hd[N], tl[N], v[N][N], I[N];
int h, t, J, va[N];

inline void solve() {
  int _n, _m;
  rd(_n, _m);
  n = m = 0;
  FOR(i, 1, _n + 1) rd(_A[i].fi, _A[i].se);
  FOR(i, 1, _m + 1) rd(_B[i].fi, _B[i].se);
  sort(_A + 1, _A + _n + 1);
  sort(_B + 1, _B + _m + 1);
  FOR(i, 1, _n + 1) {
    int A = _A[i].fi, P = _A[i].se;
    while (n && A >= a[n] && P >= p[n]) --n;
    ++n;
    a[n] = A;
    p[n] = P;
  }
  FOR(i, 1, _m + 1)  {
    int A = _B[i].fi, P = _B[i].se;
    while (m && A >= b[m] && P >= q[m]) --m;
    ++m;
    b[m] = A;
    q[m] = P;
  }
  FOR(i, 0, m + 1) {
    hd[i] = 0, tl[i] = 1;
    I[i] = 0;
  }
  FOR(i, 0, n + 1) FOR(j, 0, m + 1) dp[i][j] = inf;
  dp[0][0] = 0;
  p[0] = q[0] = inf;
  FOR(i, 0, n + 1) {
    h = 0, t = 1;
    J = 0;
    FOR(j, 0, m + 1) {
      while (J < j && dp[i][J] <= b[j]) {
        ++J;
      }
      while (I[j] < i && dp[I[j]][j] <= a[i]) {
        ++I[j];
      }
      while (h >= t && va[t] < J) ++t;
      while (hd[j] >= tl[j] && v[j][tl[j]] < I[j]) ++tl[j];
      chkmin(dp[i][j], q[J] + b[j]);
      chkmin(dp[i][j], p[I[j]] + a[i]);
      if (t <= h) chkmin(dp[i][j], dp[i][va[t]] + q[va[t] + 1]);
      if (tl[j] <= hd[j]) chkmin(dp[i][j], dp[v[j][tl[j]]][j] + p[v[j][tl[j]]+1]);
      while (h >= t && dp[i][va[t]] + q[va[h]+1] >= dp[i][j] + q[j+1]) --h;
      while (hd[j] >= tl[j] && dp[v[j][hd[j]]][j] + p[v[j][hd[j]]+1] >= dp[i][j] + p[i+1]) --hd[j];
      va[++h] = j;
      v[j][++hd[j]] = i;
    }
  }
  println(dp[n][m]);
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

