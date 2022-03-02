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
const int N = 1e5+5;
int n, q, t;
i64 a[N];
i64 c[N], d[N];

void add(int i, i64 n, i64 v) {
  if (i == 1) {
    c[n] += v;
    return;
  }
  i64 p = n / a[i-1], r = n - p * a[i-1];
  d[i-1] += p * v;
  i = lower_bound(a + 1, a + t + 1, r) - a;
  add(i, r, v);
}

inline void solve() {
  rd(n, q);
  a[1] = n;
  t = 1;
  FOR(i, 0, q) {
    i64 l;
    rd(l);
    while (t && a[t] >= l) --t;
    a[++t] = l;
  }
  d[t] = 1;
  ROF(i, 1, t + 1) add(i, a[i], d[i]);
  ROF(i, 1, n) c[i] += c[i+1];
  FOR(i, 0, n) println(c[i + 1]);
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

