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

const int N = 2005, K = 55;
const int p = 998244353;
inline void red(int &x) { if (x >= p) x -= p; }
i64 fac[N] = {1, 1}, ifac[N] = {1, 1}, inv[N] = {0, 1};
int dp[2][K<<1][N];
int tmp[N<<1][N];
int a[N];
int n, k;
int D[N], U[N], L[N];
#define mnex(i) max(0, a[i] - k)
#define mxex(i) min(n, a[i] + k)
#define FMEX(i, u) FOR(u, 0, L[i])

inline i64 P(int n, int k) {
  if (k < 0 || k > n) return 0;
  return 1ll * fac[n] * ifac[n - k] % p;
}

inline void solve() {
  rd(n, k);
  FOR(i, 2, n + 1) {
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    fac[i] = fac[i - 1] * i % p;
    ifac[i] = ifac[i - 1] * inv[i] % p;
  }
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n + 1) D[i] = mnex(i), U[i] = mxex(i), L[i] = U[i] - D[i] + 1;
  dp[0][0][0] = 1;
  FOR(i, 1, n + 1) {
    auto f = dp[i & 1];
    auto g = dp[~i & 1];
    int mnc = D[i];
    int mxc = U[i];
    int co = mnc - D[i - 1];
    FMEX(i - 1, j) FOR(t, 0, n + 1) {
      if (j > co) continue;
      red(tmp[j + t + D[i - 1]][max(j + D[i - 1], mnc - 1)] += 1ll * g[j][t] * fac[t] % p);
    }
    FOR(T, max(0, mnc - 1), mxc + n + 1) FOR(x, max(0, mnc - 1), mxc) {
      red(tmp[T][x + 1] += tmp[T][x]);
    }
    FMEX(i, j) FOR(t, 0, n + 1) {
      if (t) red(f[j][t] += g[j+co][t - 1]);
      red(f[j][t] += 1ll * (j + t + mnc) * g[j+co][t] % p);
      if(j) red(f[j][t] += 1ll * ifac[t] * tmp[j + t - 1][j - 1] % p);
    }
    FMEX(i - 1, j) FOR(t, 0, n + 1) g[j][t] = 0;
    FOR(T, max(0, mnc - 1), mxc + n + 1) FOR(x, max(0, mnc - 1), mxc + 1) {
      tmp[T][x] = 0;
    }
  }
  int ans = 0;
  FMEX(n, i) FOR(t, 0, n + 1) 
    red(ans += 1ll * dp[n & 1][i][t] * P(n - i - D[n], t) % p);
  println(ans);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
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


