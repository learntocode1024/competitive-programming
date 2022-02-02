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

#define MULTI
const i64 N = 1e6+5;
const i64 p = 998244353;
vector<i64> low(N), phi(N), pri(N), fac(N), inv(N), ifac(N), a(N), c(N), cc(N);
i64 n, tot;


i64 q_pow(i64 x, i64 y) {
  i64 ret = 1;
  while (y) {
    if (y & 1) ret = ret * x % p;
    x = x * x % p;
    y >>= 1;
  }
  return ret;
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n) c[i+1] = 0;
  FOR(i, 0, n) cin >> a[i], ++c[a[i]];
  if (n == 2 && a[0] == 1 && a[1] == 2) {
    println(2);
    return;
  }
  i64 c0 = n;
  sort(begin(c)+1, begin(c)+n+1);
  reverse(begin(c) + 1, begin(c) + n + 1);
  i64 m = 1;
  while (c[m] != 0) ++m;
  if (c[1] == n) {
    println(1);
    return;
  }
  FOR(i, 1, m) c0 = __gcd(c0, c[i]);
  i64 ans = 0, ans2 = 0;
  for (i64 k = 1; k <= c0; ++k) if (c0 % k == 0) {
    i64 d = 0;
    FOR(i, 1, m) cc[i] = c[i] / k, d += cc[i];
    i64 cur = phi[k];
    d = d * d;
    FOR(i, 1, m) cur = cur * ifac[cc[i]] % p, d -= 1ll * cc[i] * cc[i];
    d %= p;
    i64 cur2 = cur * fac[n/k] % p;
    cur = cur * fac[n/k-2] % p;
    cur = cur * d % p;
    ans = (ans + cur) % p;
    ans2 = (ans2 + cur2) % p;
  }
  ans2 = ans2 * inv[n] % p;
  ans2 = q_pow(ans2, p-2);
  println(ans * ans2 % p);
}

int main() {
  fac[0] = ifac[0] = fac[1] = ifac[1] = phi[1] = inv[1] = 1;
  FOR(i, 2, N) {
    fac[i] = 1ll * fac[i-1] * i % p;
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    ifac[i] = 1ll * ifac[i-1] * inv[i] % p;
  }
  FOR(i, 2, N) {
    if (!low[i]) {
      low[i] = pri[tot++] = i;
      phi[i] = i - 1;
    }
    for (i64 j = 0; j < tot && pri[j] * i < N; ++j) {
      int to = pri[j] * i;
      low[to] = pri[j];
      if (pri[j] == low[i]) {
        phi[to] = phi[i] * pri[j];
        break;
      } else {
        phi[to] = phi[i] * (pri[j] - 1);
      }
    }
  }
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
