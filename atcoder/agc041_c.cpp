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

const int N = 10;
const char* a[4][7] {
    {
      "aacd",
      "bbcd",
      "efgg",
      "efhh"
    },{
      "aaxxy",
      "bbw.y",
      "ccwzz",
      "..def",
      "..def"
    },{
      "aabbcc",
      "xyz...",
      "xyz...",
      "...pqr",
      "...pqr",
      "mmnntt"
    },{
      "..xxssy",
      "bbf...y",
      "ccf...g",
      "ddw...g",
      "..wttzz",
      "...efh.",
      "...efh."
    }
};

inline void solve() {
  int n;
  rd(n);
  if (n == 3) cout << R"(aa.
..b
..b
)";
  else if (n < 4) println(-1);
  else {
    int r = n & 3;
    FOR(i, 0, r + 4) {
      print(a[r][i]);
      FOR(i, r + 4, n) print('.');
      cout << '\n';
    }
    for (int i = r + 4; i < n; i += 4) {
      FOR(j, 0, 4) {
        FOR(_, 0, i) print('.');
        print(a[0][j]);
        FOR(_, i + 4, n) print('.');
        print('\n');
      }
    }
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

