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
const int N = 105, M = 1005;
const int p = 1e9+7;
inline void red(int &x) { if (x >= p) x -= p; }
int dp[2][M][M];
int s1[M][M], s2[M][M];
int H[N], l[N];
int n;

inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) cin >> H[i];
  FOR(i, 0, H[1]+1) dp[1][i][i] = 1;
  l[1] = H[1];
  FOR(i, 2, n + 1) {
    if (i & 1) l[i] = min(H[i], l[i-1]);
    else l[i] = l[i-1];
  }
  FOR(i, 2, n + 1) {
    auto &f = dp[i&1];
    auto &g = dp[~i&1];
    memset(f, 0, sizeof(f));
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    FOR(j, 0, H[i-1]+1) FOR(k, 0, l[i-1]+1) s1[j][k] = g[j][k];
    FOR(j, 1, max(H[i-1], H[i])+1) FOR(k, 0, l[i-1]+1) red(s1[j][k] += s1[j-1][k]);
    // FOR(j, 0, H[i]+1) FOR(k, 0, l[i]+1) f[j][k] = 0;
    if (i & 1) {
      FOR(j, 0, max(H[i-1], H[i])+1) ROF(k, 0, l[i-1]+1) red(s2[j][k] = s2[j][k+1] + s1[j][k]);
      FOR(j, 0, H[i]+1) FOR(k, 0, j + 1) {
        if (k == j) f[j][k] = s2[H[i]-j][k];
        else f[j][k] = s1[H[i]-j][k];
      }
    } else {
      FOR(j, 0, H[i] + 1) FOR(k, 0, l[i]+1) {
        f[j][k] = s1[H[i]-j][k];
      }
    }
    // FOR(j, 1, max(H[i-1], H[i])+1) FOR(k, 0, l[i-1]+1) s1[j][k] = s2[j][k] = 0;
  }
  int ans = 0;
  if (n & 1) {
    FOR(j, 0, H[n] + 1) red(ans += dp[1][j][j]);
  } else {
    FOR(k, 0, l[n] + 1) red(ans += dp[0][0][k]);
  }
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

