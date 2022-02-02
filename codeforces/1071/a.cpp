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
int a, b;

inline void solve() {
  int k = 0, k1 = 0;
  int s = 0, s1 = 0;
  rd(a, b);
  while (s <= a + b) ++k, s += k;
  --k;
  while (s1 <= a) ++k1, s1 += k1;
  s1 -= k1;
  --k1;
  a -= s1;
  if (k1 == k) {
  println(k1);
  FOR(i, 1, k1 + 1) cout << i << ' ';
println(0);
return;
  }
  println(k1);
  FOR(i, 1, k1 + 1)  cout << (i == k1 + 1 - a ? k1 + 1 : i) << ' ';
  cout << '\n';
  println(k - k1);
  cout << k1 + 1 - a << ' ';
  FOR(i, k1 + 2, k + 1) cout << i << ' ';

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

