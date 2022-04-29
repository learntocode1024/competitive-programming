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
const int N = 1e7+5;
const int p = 998244353;
int f[N];
int n, m;
int a[N], k[N], b[N];
bool vis[N], ins[N];
int s[N], tot;

inline int q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

inline int inv(int x) {
  return q_pow(x, p - 2);
}

inline int to(int x) {
  return x*2%m;
}

inline void solve() {
  rd(n);
  FOR(i,1,n) rd(a[i]), m += a[i];
  vis[0] = vis[m] = 1;
  const i64 im = inv(m);
  const i64 i2 = inv(2);
  if (~m & 1) {
    f[m/2] = i2;
    int u = m/2;
    vis[u] = 1;
    while (!vis[to(u)]) {
      a[to(u)] = 2ll * (f[u] + p - im * u % p) % p;
      u = to(u);
      vis[u] = 1;
    }
  }
  FOR(i,1,m-1) if (!vis[i]) {
    tot = 0;
    int u = i;
    while (!vis[u]) {
      s[++tot] = u;
      vis[u] = 1;
      ins[u] = 1;
      u = to(u);
    }
    if (ins[u]) {
      k[to(u)] = 2;
      b[to(u)] = (p - 2 * u * im % p) % p;
      int o = to(u);
      while (o != u) {
        k[to(o)] = 2 * k[o] % p;
        b[to(o)] = (p + 2 * b[o] % p - 2 * o * im % p) % p;
        o = to(o);
      }
      f[u] = 1ll * b[u] * inv(1+p-k[u]) % p;
      o = u;
      while (to(o) != u) {
        f[to(o)] = 2ll * (p + f[o] - o * im % p) % p;
        o = to(o);
      }
      FOR(i,1,tot) ins[s[i]] = 0;
      while (s[tot] != u) --tot;
      --tot;
    } else FOR(i,1,tot) ins[s[i]] = 0;
    ROF(i,1,tot) {
      f[s[i]] = (s[i] * im + i2 * f[to(s[i])]) % p;
    }
  }
  int ans = 0;
  FOR(i,1,n) ans = (ans + f[a[i]]) % p;
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

