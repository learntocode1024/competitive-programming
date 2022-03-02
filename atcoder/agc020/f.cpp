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
const int N = 6, M = 51;
typedef long double dbl;
int C, n;
int a[N];
int r[N], rk[N];
i64 dp[1<<5][M*N][M*N];

inline void solve() {
  rd(n, C);
  FOR(i, 0, n) rd(a[i]);
  if (accumulate(a,a+n,0) <= C) {
    println(0);
    return;
  }
  sort(a,a+n);
  iota(r,r+n,0);
  dbl ans = 0;
  --n;
  do {
    memset(dp, 0, sizeof(dp));
    dp[0][0][a[n]*n] = 1;
    FOR(i,0,C*n) FOR(u, 0, 1 << n) FOR(j,i,C*n+1) {
      dp[u][i+1][j] += dp[u][i][j];
      int t = i % n;
      if (!((u>>t)&1)&&j>i) {
        dp[u|(1<<t)][i+1][min(C*n, max(j, i+a[r[t]]*n))] += dp[u][i][j];
      }
    }
    ans += dp[(1<<n)-1][C*n][C*n];
  } while (next_permutation(r,r+n));
  FOR(i,1,n+1) ans /= i * C;
  cout << setprecision(12) << ans << '\n';
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

