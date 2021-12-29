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
const int N = 1e5+5;
const int p = 998244353;
int fac[N] = {1, 1};
int p2[N] = {1, 2};
int inv[N] = {0, 1}, ifac[N] = {1, 1};
int n;
int f[N] = {1};
char s[N];
int a[N], t;

inline void solve() {
  rd(n, s);
  FOR(i, 2, n + 1) {
    p2[i] = 2ll * p2[i -1] % p;
    fac[i] = 1ll * i * fac[i - 1] % p;
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    ifac[i] = 1ll * ifac[i-1] * inv[i] % p;
  }
  for (int i = 1, s = 1; i <= n; ++i) {
    f[i] = 1ll * s * inv[2] % p * inv[i] % p;
    s = (s + f[i]) % p;
  }
  FOR(i, 1, n + 1) {
    f[i] = 1ll * f[i] * p2[i] % p * fac[i] % p;
  }
  FOR(i, 0, n) {
    if (s[i] == '.') a[t++] = i;
  }
  int ans = 0;
  int c1 = 0, c2 = a[t-1] + 1;
  FOR(i, 0, a[0]) if (s[i] == '<') ++c1;
  FOR(i, a[t-1], n) if (s[i] == '<') ++c2;
  ans = (ans + 1ll * f[t] * c1) % p;
  ans = (ans + 1ll * f[t] * c2) % p;
  FOR(i, 1, t) {
    i64 cur = a[i - 1] + 1;
    FOR(j, a[i - 1] + 1, a[i]) {
      if (s[j] == '<') ++cur;
    }
    cur = cur * f[i] % p;
    cur = cur * f[t - i] % p;
    cur = cur * fac[t] % p * ifac[i] % p * ifac[t - i] % p;
    ans = (ans + cur) % p;
  }
  FOR(i, 0, t) ans = 1ll * ans * inv[2] % p;
  ans = 1ll * ans * ifac[t] % p;
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

