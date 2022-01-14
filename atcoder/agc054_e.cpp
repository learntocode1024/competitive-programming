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
const int N = 1e6+5;
const int p = 998244353;
i64 fac[N], ifac[N], inv[N];

void work() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1ll;
  for (int i = 2; i < N; ++i) {
    inv[i] = (p - p / i) * inv[p % i] % p;
    fac[i] = fac[i - 1] * i % p;
    ifac[i] = ifac[i - 1] * inv[i] % p;
  }
}

i64 calc(int n, int a) {
  if (n - a - 2 < 0) return 0;
  return (inv[a] + inv[a + 1] *(n-a-2)%p) * fac[n-2]%p;
}

inline void solve() {
  int n, a;
  cin >> n >> a;
  println((fac[n-1] + p + p - calc(n, a) - calc(n, n + 1 - a)) % p);
}

int main() {
  work();
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

