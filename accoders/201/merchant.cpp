/** @file
 * @ingroup math bgf oeis
OEIS A298637
打表找规律, 暴力出奇迹.
 */
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(T &x, W &...b) {
  cin >> x;
  rd(b...);
}
#ifndef MISAKA
#define err(...)
#else
#define err(...) fprintf(stderr, __VA_ARGS__)
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
typedef pair<int, int> pii;
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define shuf(L, R) shuffle((L), (R), rng)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void ckmin(T &a, const T &b) { a = min(a, b); }
template <typename T> inline void ckmax(T &a, const T &b) { a = max(a, b); }
#define IOFILE "b"
//#define MULTI
const int N = 1e6+5;
const int p = 998'244'353;
const int base = 233;
int f[N];
int inv[N], ifac[N];

inline void sol() {
  int typ, n, k;
  rd(typ,n);
  if (typ == 1) rd(k);
  f[0] = n + 1;
  f[1] = 1;
  inv[1] = 1, ifac[1] = 1;
  FOR(i,2,n/2) {
    inv[i] = 1ll * inv[p % i] * (p - p / i) % p;
    ifac[i] = 1ll * ifac[i-1] * inv[i] % p;
  }
  FOR(i,2,n/2) f[i] = 1ll * f[i-1] * (n-i+2) % p;
  FOR(i,1,n/2) f[i] = 1ll * f[i] * (n - 2 * i + 1) % p * (n - 2 * i + 1) % p * ifac[i] % p;
  if (typ == 1) O(f[k]);
  else {
    int pw = 1;
    int ans = 0;
    FOR(i,0,n/2) ans = (ans + 1ll * pw * f[i]) % p, pw = 1ll * pw * base % p;
    O(ans);
  }
}

int main() {
#ifndef MISAKA
#ifdef IOFILE
  freopen(IOFILE ".in", "r", stdin);
  freopen(IOFILE ".out", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
    sol();
  return 0;
}

