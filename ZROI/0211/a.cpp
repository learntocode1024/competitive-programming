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

inline void solve() {
  i64 l, r, n;
  cin >> n >> l >> r;
  if (l == r) {
    println(1);
  } else if (n == 1) {
    println(r - l + 1);
  } else {
    i64 x = l ^ r;
    x = (1ull << (64 - __builtin_clzll(x)))-1;
    l &= x;
    r &= x;
    i64 ans = 0;
    i64 m = (1ull << (63 - __builtin_clzll(r)));
    i64 l1 = m + l;
    ans = m - l;
    i64 y = r ^ m;
    if (y) y = (1ull << (64 - __builtin_clzll(y)))-1;
    i64 r1 = y | m;
    if (r1 < l1) {
      ans += (r1 - l + 1);
    } else {
      ans += m;
    }
    println(ans);
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

