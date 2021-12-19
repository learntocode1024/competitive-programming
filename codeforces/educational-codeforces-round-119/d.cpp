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

const int N = 2e5+5;
int a[N];

inline void solve() {
  int n;
  cin >> n;
  int s = 0;
  FOR(i, 0, n) cin >> a[i];
  bool b1 = 0, b2 = 0;
  FOR(i, 0, n) {
    chkmax(s, (int)ceil(a[i] / 3.0));
    if (a[i] % 3) b1 = 1;
    if (a[i] == 1) b2 = 1;
  } // 2223*
  int ans = s + b1 + b2;
  s = 0;
  bool v[3] = {0,0,0};
  FOR(i, 0, n) {
    chkmax(s, a[i] / 3);
    v[a[i] % 3] = 1;
  }
  chkmin(ans, s + v[1] + v[2]);
  s = 0;
  FOR(i, 0, n) {
    if (a[i] % 3 == 0)chkmax(s, a[i] / 3 - 1);
    else chkmax(s, a[i] / 3);
  }
  chkmin(ans, 2 + s);
  b1 = b2 = 0;
  s = 0;
  int c = 0;
  FOR(i, 0, n) {
    if (a[i] % 3 == 0) chkmax(s, a[i] / 3);
    else if (a[i] % 3 == 1) {
      if (a[i] == 1) b1 = 1;
      c = 2;
      chkmax(s, (a[i] - 4)/3);
    } else {
      chkmax(s, a[i] / 3);
      chkmax(c, 1);
    }
  }
  chkmin(ans, s + c + b1);
  println(ans);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  int T;
  cin >> T;
  while (T--)
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

