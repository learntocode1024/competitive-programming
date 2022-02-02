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
const int N = 205;
const int p = 998244353;
int inv[N], ifac[N];
int n, k;
int a[114514];
i64 f(int x) {
  i64 ans = 1;
  FOR(i, 1, k) ans = ans * (x + i) % p;
  return ans * ifac[k-1] % p;
}

inline void solve() {
  inv[1] = 1;
  ifac[0] = ifac[1] = 1;
  FOR(i, 2, N) {
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    ifac[i] = 1ll * ifac[i-1] * inv[i] % p;
  }
  cin >> n >> k;
  i64 cnt = 0;
  FOR(i, 0, n) cin >> a[i], cnt += a[i];
  i64 ans = 1;
  cnt -= a[0];
  if (a[0] < k + cnt) {
    println(0);
    return;
  }
  a[0] -= k + cnt;
  FOR(i, 0, n) ans = ans * f(a[i]) % p;
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

