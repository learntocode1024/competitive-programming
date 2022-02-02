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
const int N = 205;
const int p = 998244353;
int n;
int a[N];
bool t[N];
bool f[1<<16];
int dp[N][1<<16];

inline void solve() {
  cin >> n;
  FOR(u, 1, 1<<16) {
    if (__builtin_popcount(u) == 1) continue;
    int xmx = 0;
    FOR(i, 0, 16) if ((u>>i)&1) chkmax(xmx, (i+1)*12);
    f[u] = 1;
    FOR(x, 1, xmx + 1) {
      int cnt = 0;
      int v = 0;
      FOR(i, 0, 16) if ((u>>i)&1) {
        int to = (i+1)*12%x;
        if (!to) continue;
        if (!t[to]) ++cnt;
        t[to] = 1;
        if (to % 12 == 0) v |= 1 << (to/12-1);
      }
      if (cnt == 1 && (t[1] || t[2]))  {
        f[u] = 0;
      }
      if (cnt == 2 && t[4] && t[8])  {
        f[u] = 0;
      }
      if (cnt == __builtin_popcount(v) && f[v]) {
        f[u] = 0;
      }
      FOR(i, 0, 16) if ((u>>i)&1) {
        int to = (i+1)*12%x;
        if (!to) continue;
        t[to] = 0;
      }
      if (f[u] == 0) break;
    }
  }
  int mn = 201;
  i64 ans = 1, d = 1;
  FOR(i, 1, n + 1) cin >> a[i], ans = ans * a[i] % p, chkmin(mn, a[i]);
  ans = (ans + p-1) % p;
  if (mn > 1) ans = (ans + p-1) % p;
  FOR(i, 1, n + 1) d = d * (1ll*(a[i]>3) + 1ll*(a[i]>7)) % p;
  ans = (ans + p - d) % p;
  if (mn>3) ++ans;
  if (mn>7) ++ans;
  dp[0][0] = 1;
  FOR(i, 1, n + 1) {
    FOR(u, 0, 1<<16) for (int c = 12, j = 0; c <= a[i]; c += 12, ++j) {
      int v = u | (1<<j);
      dp[i][v] = (dp[i][v] + dp[i-1][u]) % p;
    }
  }
  FOR(i, 0, 1<<16) if (f[i]) {
    // println(i);
    ans = (ans + p - dp[n][i]) % p;
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

