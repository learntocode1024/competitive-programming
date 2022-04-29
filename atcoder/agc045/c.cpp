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

//#define MULTI
const int N = 5005;
const int p = 1e9+7;
int f[N][2], g[N];

inline void solve() {
  int n, a, b;
  rd(n,a,b);
  if (a > b) swap(a,b);
  FOR(i,0,b) {
    g[i] = 1;
    FOR(j,a+2,i) g[i] = (g[i] + 1ll * g[i-j+1] * (j-a-1))  % p;
  }
  f[0][0] = f[0][1] = 1;
  int ans = 1;
  FOR(i,1,n) ans = (ans<<1)%p;
  FOR(i,1,n-1) {
    if (i < a) f[i][0] = 1;
    if (i < b) f[i][1] = g[i+1];
    FOR(j,1,min(i,a)-1) f[i][0] = (f[i][0] + f[i-j][1]) % p;
    FOR(j,1,min(i,b)-1) f[i][1] = (f[i][1] + 1ll * g[j] * f[i-j][0]) % p;
    if (n-i<a) ans = (ans + p - f[i][1]) % p;
    if (n-i<b) ans = (ans + p - 1ll * f[i][0] *g[n-i+1]%p)%p;
  }
  O(ans);
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

