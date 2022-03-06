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
const int N = 305;
char s[N];
int f[N][N][N];

inline void solve() {
  int n, K;
  cin >> s + 1 >> K;
  n = strlen(s+1);
  FOR(i, 1, n+1) ROF(j, i+1, n + 1) FOR(k, 0, K+1) {
    if (s[i]==s[j]) {
      chkmax(f[i+1][j-1][k], f[i][j][k]+1);
    } else if (k<K) {
      chkmax(f[i+1][j-1][k+1], f[i][j][k]+1);
    }
    chkmax(f[i+1][j][k], f[i][j][k]);
    chkmax(f[i][j-1][k], f[i][j][k]);
  }
  int ans = 0;
  FOR(i, 1, n + 1) FOR(j, 0, K+1) chkmax(ans, f[i][i][j]*2+1);
  FOR(i, 1, n + 1) FOR(j, 0, K+1) chkmax(ans, f[i+1][i][j]*2);
  println(ans);
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

