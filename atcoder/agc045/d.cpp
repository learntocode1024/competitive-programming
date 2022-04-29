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
const int A = 5005, N = 1e7+1;
const int p = 1e9+7;
int fac[N], inv[N], ifac[N];

inline int f(int l, int m, int r) {
  return 1ll * fac[l+m+r] * l % p * inv[l+r] % p;
}

inline int binom(int n, int k) {
  if (n < k || k < 0) return 0;
  return 1ll * fac[n] * ifac[n-k] % p * ifac[k] % p;
}

inline void solve() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
  FOR(i,2,N-1) {
    fac[i] = 1ll * fac[i-1] * i % p;
    inv[i] = 1ll * (p-p/i) * inv[p%i] % p;
    ifac[i] = 1ll * ifac[i-1] * inv[i] % p;
  }
  int n, a;
  rd(n,a);
  int ans = 0;
  FOR(t,2,a+1) {
    int cur = 0;
    int l = t - 1, m = max(0,a-t), r = n - a;
    FOR(j,0,l) {
      if ((l-j)&1) cur = (cur + p - 1ll * binom(l,j) * f(j,m,r) % p) % p;
      else cur = (cur + 1ll * binom(l,j) * f(j,m,r)) % p;
    }
    ans = (ans + cur) % p;
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

