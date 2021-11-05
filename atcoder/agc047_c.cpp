#include <bits/stdc++.h>
#include <atcoder/convolution>
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

const int N = 2e5+5;
const int p = 2e5+3;
int a[N];
int n;
int b[N], c[N];

inline void solve() {
  rd(n);
  for (int i = 0, x = 1; i < p - 1; ++i) {
    c[x] = i;
    b[i] = x;
    x <<= 1;
    x %= p;
  }
  vector<int> f(p - 1, 0);
  i64 ans = 0;
  FOR(i, 0, n) {
    int x;
    rd(x);
    ans -= x * x % p;
    if (x) ++f[c[x]];
  }
  vector<int> g = atcoder::convolution(f, f);
  FOR(i, 0, g.size()) {
    ans += g[i] * b[i % (p - 1)];
  }
  println(ans / 2);
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

