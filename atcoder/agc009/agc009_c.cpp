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

const int N = 1e5+5;
const int p = 1e9+7;
inline void red(int &x) { if (x >= p) x -= p; }
i64 A, B, n;
i64 a[N];
struct BIT {
int c[N];
int t[N];
int ct;

inline void ch(int x, int v) {
  ++x;
  for (; x <= n; x += x & -x) {
    if (t[x] != ct) {
      t[x] = ct;
      c[x] = 0;
    }
    red(c[x] += v);
  }
}

inline int get(int x) {
  ++x;
  int ret = 0;
  for (; x; x -= x & -x) {
    if (t[x] == ct) red(ret += c[x]);
  }
  return ret;
}
inline void reset() {
  ++ct;
}
} x, y;

inline void solve() {
  rd(n, A, B);
  FOR(i, 1, n + 1) cin >> a[i];
  a[0] = -1e18;
  x.ch(0, 1);
  y.ch(0, 1);
  FOR(i, 2, n + 1) {
    int cx = 0, cy = 0;
    int k = upper_bound(a + 1, a + i, a[i] - A) - a - 1;
    cx = y.get(k);
    k = upper_bound(a + 1, a + i, a[i] - B) - a - 1;
    cy = x.get(k);
    if (a[i] - a[i - 1] < A) x.reset();
    if (a[i] - a[i - 1] < B) y.reset();
    x.ch(i - 1, cx);
    y.ch(i - 1, cy);
  }
  println((x.get(n - 1) + y.get(n - 1)) % p);
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


