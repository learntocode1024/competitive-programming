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

const int N = 0;

inline void solve() {
  int n;
  rd(n);
  if (__builtin_popcount(n + 1) == 1 && n > 1) {
    println("Yes");
    FOR(i, 1, 2 * n) println(i, i + 1);
  } else if (n > 1 && n & 1) {
    println("Yes");
    int l = (1 << (31 - __builtin_clz(n)));
    FOR(i, 1, l - 1) println(i, i + 1);
    println(l - 1, n + 1);
    FOR(i, n + 1, n + l - 1) println(i, i + 1);
    for (int i = l; i < n; i += 2) {
      println(i, i + 1);
      println(1, i + 1);
      println(1, i + n);
      println(i + n, i + 1 + n);
    }
  } else if (n > 1 && __builtin_popcount(n) > 1) {
    println("Yes");
    int l = (1 << (31 - __builtin_clz(n)));
    FOR(i, 1, l - 1) println(i, i + 1);
    println(l - 1, n + 1);
    FOR(i, n + 1, n + l - 1) println(i, i + 1);
    println(l, l+1);
    println(l+1,1);
    println(1,l+n);
    println(l+n,l+n+1);
    println(l+2,l+1);
    println(2,l+2+n);
    for (int i = l + 3; i <= n; i += 2) {
      int t = (1 << (__builtin_ctz(i+1)+1)) - 1;
      println(i, i + 1);
      println(t, i + 1);
      println(t, i + n);
      println(i + n, i + 1 + n);
    }

  } else {
    println("No");
  }

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

