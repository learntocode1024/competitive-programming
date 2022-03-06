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
const int N = 55, M = 2505;
const int p = 998244353;

int fac[M], ifac[M], inv[M];

int f[N][N];

inline int C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return 1ll * fac[n] * ifac[k] % p * ifac[n-k] % p;
}

inline void solve() {
  int n, m, b, w;
  rd(n,m,b,w);
  fac[0] = ifac[0] = inv[1] = ifac[1] = fac[1] = 1;
  FOR(i,2,M-1) {
    inv[i] = 1ll * (p - p / i) * inv[p%i] % p;
    fac[i] = 1ll * fac[i-1] * i % p;
    ifac[i] = 1ll * ifac[i-1] * inv[i] % p;
  }
  FOR(i,0,n) FOR(j,0,m) {
    FOR(i1,0,i) FOR(j1,0,j) if (i1<i || j1<j) {
      f[i][j] = (f[i][j] + 1ll * f[i1][j1] * C(i,i1) % p * C(j,j1) % p) % p;
    }
    f[i][j] = (-f[i][j] + p + C(i*j, b)) % p;
  }
  int ans = 0;
  FOR(i,0,n) FOR(j,0,m) {
    ans = (ans + 1ll * f[i][j] * C((n-i)*(m-j), w) % p * C(n,i) % p * C(m,j)) % p;
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

