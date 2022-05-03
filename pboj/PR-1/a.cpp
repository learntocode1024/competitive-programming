#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

#define MULTI
const int N = 3e5+5, W = 50;
int a[N];
int n;
int f[N][W];
int dp[N];

inline void solve() {
  rd(n);
  FOR(i,0,n-1) rd(a[i]);
  ROF(i,1,n-1) a[i] -= a[i-1];
  FOR(i,1,n) FOR(j,0,W-1) {
    f[i][j] = 0;
  }
  int m = 0;
  for (int i = 1, j = 1; i < n; ++i) {
    if (a[j-1] || a[i]) a[j++] = a[i];
    m = j;
  }
  n = m;
  FOR(i,1,n-1) {
    if (!a[i]) continue;
    int c = __builtin_ctz(abs(a[i]));
    a[i] /= (1<<c);
    f[i][c] = i;
    int j = i - 1;
    while (j && a[j] == a[i] && f[j][c]) {
      f[i][c+1] = f[j][c];
      j = f[j][c] - 1;
      ++c;
    }
  }
  FOR(i,1,n-1) {
    dp[i] = dp[i-1]+1;
    FOR(j,0,W-1) if (f[i][j]) {
      chkmin(dp[i], dp[f[i][j]-1] + 1);
    }
  }
  O(dp[n-1]+1);
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

