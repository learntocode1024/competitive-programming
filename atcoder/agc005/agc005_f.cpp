#include <bits/stdc++.h>
#include "atcoder/convolution"
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
const int N = 2e5+5;
const int p = 924844033;
int n, s[N];
vector<int> g[N];
int c[N];
i64 inv[N], fac[N], ifac[N];
void dfs(int u, int fa) {
  s[u] = 1;
  for (auto v : g[u]) if (v != fa) {
    dfs(v, u);
    s[u] += s[v];
    ++c[s[v]];
    ++c[n - s[v]];
  }
}


inline void solve() {
  cin >> n;
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs(1, 0);
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
  FOR(i, 2, n + 1) {
    fac[i] = fac[i-1] * i % p;
    inv[i] = (p - p / i) * inv[p % i] % p;
    ifac[i] = ifac[i-1] * inv[i] % p;
  }
  fac[n+1] = fac[n] * n % p;
  vector<int> A(n+1), B(n+1);
  FOR(i, 0, n + 1) A[i] = ifac[i];
  FOR(i, 0, n + 1) B[i] = c[n - i] * fac[n - i] % p;
  auto C = atcoder::convolution<p>(A, B);
  for (int i = 1; i <= n; ++i) {
    println(ifac[i] * (fac[n+1]*ifac[n-i] % p+p-C[n-i]) % p);
  }
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

