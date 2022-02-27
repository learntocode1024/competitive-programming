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
const int N = 5005;
int n, a[N], b[N], c[N];

inline void op(int *p, int x) {
  swap(p[x+1], p[x+2]);
  swap(p[x], p[x+1]);
}

inline void trans(int *a) {
  FOR(i, 0, n-2) {
    int to = -1, x = 1e9;
    FOR(j, i, n) {
      if (a[j] < x) x = a[j], to = j;
    }
    int d = to - i;
    while (d >= 2) {
      op(a,to - 2);
      d -= 2;
      to -= 2;
    }
    if (d == 1) {
      op(a,to-1);
      op(a,to-1);
    }
  }
}

inline void solve() {
  rd(n);
  int d = 0;
  FOR(i, 0, n) rd(a[i]), ++c[a[i]], d |= (c[a[i]] > 1);
  FOR(i, 0, n) rd(b[i]), --c[b[i]];
  FOR(i, 0, N) {
    if (c[i] != 0) {
      println("No");
      return;
    }
  }
  int cc = 0;
  FOR(i, 0, n) FOR(j, i+1, n) cc ^= (a[i] > a[j]);
  FOR(i, 0, n) FOR(j, i+1, n) cc ^= (b[i] > b[j]);
  println(!d&&cc?"No":"Yes");
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

