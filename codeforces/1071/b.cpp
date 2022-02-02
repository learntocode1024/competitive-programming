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
const int N = 2005;
int n, k;
char s[N][N];
int d[N][N];
string ans;
bool v[N][N];

inline void solve() {
  rd(n, k);
  FOR(i, 1, n + 1) cin >> s[i] + 1;
  FOR(i, 2, n + 1) d[i][0] = d[0][i] = 1e9;
  FOR(i, 1, n + 1) FOR(j, 1, n + 1) d[i][j] = min(d[i-1][j], d[i][j-1]) + (s[i][j] != 'a');
  if (d[n][n] <= k) {
    FOR(i, 1, n * 2) cout << 'a';
    cout << '\n';
    return;
  }
  int l = 0;
  FOR(i, 1, n + 1) FOR(j, 1, n + 1) if (d[i][j] == k) chkmax(l, i + j - 1), v[i][j] = 1;
  FOR(i, 0, l) ans += 'a';
  if (l == 0 && s[1][1] != 'a') v[1][1] = 1, ans.pb(s[1][1]), l = 1;

  FOR(t, l + 1, n * 2) {
    char c = 'z';
    for (int i = 1, j = t; j > 0; ++i, --j) {
      if (i < 1 || j < 1 || i > n || j > n) continue;
      if (v[i-1][j] || v[i][j-1]) chkmin(c, s[i][j]);
    }
    ans.pb(c);
    for (int i = 1, j = t; i <= n && j >= 1; ++i, --j) {
      if (v[i-1][j] || v[i][j-1]) if (s[i][j] == c) v[i][j] = 1;
    }
  }
  println(ans);
}

int main() {
#ifndef MISAKA
  freopen("scramble.txt", "r", stdin);
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

