#include <bits/stdc++.h>
#include "atcoder/modint"
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
typedef atcoder::modint998244353 mint;

i64 getlen(i64 i, i64 x, i64 c) {
  if (!c) return 1e18+7;
  return (x - (i+1)*c)/(c*2) + ((x - (i+1)*c) % (c*2) != 0);
}

i64 getd(i64 i, i64 x) {
  return (x/(i+1)) + (x % (i+1) != 0) - 1;
}

mint s1(i64 n) {
  return mint(n) * mint(n+1) / mint(2);
}

mint s2(i64 n) {
  return mint(n) * mint(n+1) * mint(2*n+1) / mint(6);
}

mint sum(i64 i, i64 n, i64 x, i64 c) {
  mint mi = i, mn = n, mx = x, mc = c;
  return mi * mx * (mn+1) + (mx-mi*mc) * s1(n) - mc * s2(n);
}

inline void solve() {
  i64 n, x;
  cin >> n >> x;
  i64 i = 1;
  mint ans(0);
  while (i <= n) {
    i64 c = getd(i, x);
    i64 len = getlen(i, x, c);
    chkmin(len, n - i + 1);
    // println(i, x, c, i + len);
    ans += sum(i, len - 1, x, c);
    x -= c * len;
    i += len;
  }
  println(ans.val());
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

