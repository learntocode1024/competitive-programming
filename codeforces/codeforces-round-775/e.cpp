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
const int N = 2e5+5;
const int p = 998244353;
int a[N], b[N], c[N];
int fac[N], ifac[N], inv[N];

int s[N];
inline void add(int x) {
  for (; x < N; x += x & -x) ++s[x];
}
inline void del(int x) {
  for (; x < N; x += x & -x) --s[x];
}

inline int get(int x) {
  int ret = 0;
  for (; x; x -= x & -x) ret += s[x];
  return ret;
}

inline void solve() {
  inv[1] = fac[1] = fac[0] = ifac[1] = ifac[0] = 1;
  FOR(i,2,N-1) {
    fac[i] = 1ll * fac[i-1] * i % p;
    inv[i] = 1ll * (p - p/i) * inv[p%i] % p;
    ifac[i] = 1ll * ifac[i-1] * inv[i] % p;
  }
  int n, m, mx = 0;
  rd(n,m);
  FOR(i,1,n) rd(a[i]), chkmax(mx, a[i]);
  FOR(i,1,m) rd(b[i]);
  int k = min(n,m);
  FOR(i,1,n) ++c[a[i]], add(a[i]);
  i64 cur = 1;
  FOR(i,1,mx) {
    cur = 1ll * cur * ifac[c[i]] % p;
  }
  int ans = 0;
  bool ok = 1;
  FOR(i,1,k) {
    ans = (ans + 1ll * get(b[i]-1) * cur % p * fac[n-i]) % p;
    cur = 1ll * cur * c[b[i]] % p;
    del(b[i]);
    --c[b[i]];
    if (c[b[i]] < 0) {
      ok = 0;
      break;
    }
    O(ans);
  }
  if (n < m) {
    ans = (ans + ok) % p;
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

