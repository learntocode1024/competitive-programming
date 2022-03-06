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
const int N = 405;
const int p = 98244353;
int n, m;
int f[N][N], s[N][N];
vector<int> g[N];

inline int q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

inline int iv(int x) {
  return q_pow(x,p-2);
}

int fac[N], ifac[N], inv[N];

inline int C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return 1ll * fac[n] * ifac[k] % p * ifac[n-k] % p;
}

inline int ps(int l, int r, int k) {
  int ans = s[r][k];
  if (l) ans = (ans + p - s[l-1][k]) % p;
  return ans;
}

inline void solve() {
  fac[0] = ifac[0] = inv[1] = ifac[1] = fac[1] = 1;
  FOR(i,2,N-1) {
    inv[i] = 1ll * (p - p / i) * inv[p%i] % p;
    fac[i] = 1ll * fac[i-1] * i % p;
    ifac[i] = 1ll * ifac[i-1] * inv[i] % p;
  }
  rd(n,m);
  FOR(i,1,m) {
    int l, r;
    rd(l,r);
    g[r].pb(l);
  }
  FOR(i,1,n) {
    sort(begin(g[i]), end(g[i]));
    reverse(begin(g[i]), end(g[i]));
  }
  int im = iv(m);
  f[0][0] = s[0][0] = 1;
  FOR(i,1,n) s[i][0] = 1;
  FOR(i, 1, n) FOR(j, 1, m) {
    if (!g[i].empty()) FOR(k, 0, g[i].size()-1) {
      FOR(h, 1, min(k+1, j)) {
        f[i][j] = (f[i][j] + 1ll * ps(g[i][k]-1, i-1, j-h) * C(k+1, h)) % p;
      }
    }
    s[i][j] = (s[i-1][j] + f[i][j]) % p;
  }
  int ans = 1;
  FOR(i,1,n) {
    ans = (ans + 1ll * q_pow(im, i-1) * iv(m-i) % p * (C(n,i) + p - f[n][i])%p) % p;
    O(f[n][i]);
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

