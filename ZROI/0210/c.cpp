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
const int N = 5005, M = N<<1;
const int P = 998244353;
int n;
int g[N][N];
int fac[M], inv[M], ifac[M];
int pw[M];

inline void calc_g() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
  for (int i = 2; i < M; ++i) {
    inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
    fac[i] = 1ll * i * fac[i-1] % P;
    ifac[i] = 1ll * ifac[i-1] * inv[i] % P;
  }
  pw[0] = 1;
  i64 inv3 = inv[3];
  FOR(i, 1, M) pw[i] = inv3 * pw[i-1] % P;
  FOR(x, 0, N) {
    int s = 0;
    FOR(k, 0, N) {
      s = (s + 1ll * pw[k+x] * fac[k+x] % P * ifac[k]) % P;
      g[x][k] = s;
    }
  }
}

inline void solve() {
  int ans = 499122178; // 3/2
  for (int b = 1; 3 * b < n; ++b) {
    for (int c = 0; 4 * c + 3 * b < n; ++c) {
      int a = n - 3 * b - 4 * c;
      assert(a > 0);
      ans = (ans + 1ll * (g[b+c][a] - g[b+c][0] + P) % P * ifac[b] % P * ifac[c]) % P;
    }
  }
  for (int b = 1; b * 2 < n; ++b) {
    int c = (n+1)/2 - 1 - b;
    assert(c >= 0);
    ans = (ans + 1ll * g[b][c] * ifac[b]) % P;
  }
  for (int c = 0; c * 2 < n; ++c) {
    int a = n - c * 2;
    assert(a > 0);
    ans = (ans + 1ll * (g[c][a] - g[c][0] + P) % P * ifac[c]) % P;
  }
  cout << ans << ",}"[n==5000];
}

int main() {
  calc_g();
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  cout << '{';
  for (int i = 1; i <= 5000; ++i) {
    n = i;
    solve();
  }
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

