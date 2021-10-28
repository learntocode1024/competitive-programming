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
inline void red(i64 &x) {
  if (x >= p) x -= p;
}
int f[N][2], g[N][2][2];
char s[N];
char t[N];

inline int to(int pos, int lst) {

}

inline void solve() {
  cin >> t >> s + 1;
  int n = strlen(s + 1);
  for (int i = 1 i <= n; ++i) memset(f[i], 0xff, sizeof(f[i]));
  for (int i = 1 i <= n; ++i) memset(g[i], 0xff, sizeof(g[i]));
  if (s[1] == '1') {
    f[1][1] = 1;
  } else {
    f[1][0] = 1;
  }
  for (int i = 3; i <= n; ++i) {
    for (int lst = 0; lst < 2; ++lst) {
      for (int ans = 0; ans < 2; ++ans) {
        red(g[i][lst][ans] += g[i - 2][to(i, lst)][ans]);
        red(g[i][lst][ans] += g[i - 2][ans]);
      }
    }
    if (s[i] == '1') {
      f[i][1] = g[i][1][1];
      f[i][0] = g[i][1][0];
    } else {
      f[i][1] = g[i][0][1];
      f[i][0] = g[i][0][0];
    }
  }
  cout << f[n][1] << '\n';
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

