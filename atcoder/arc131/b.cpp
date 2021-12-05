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

const int N = 705;
string s[N];
bool vis[5];
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
  int n, m;

int col(int x, int y) {
  FOR(i, 0, 5) vis[i] = 0;
  FOR(i, 0, 4) {
    int a = x + dx[i], b = y + dy[i];
    if (a >= 0 && b >= 0 && a < n && b < m) {
      if (s[a][b] != '.') vis[s[a][b] - '1'] = 1;
    }
  }
  FOR(i, 0, 5) if (!vis[i]) return i;
  return -1;
}

inline void solve() {
  cin >> n >> m;
  FOR(i, 0, n) cin >> s[i];
  FOR(i, 0, n) FOR(j, 0, m) if (s[i][j] == '.') s[i][j] = col(i, j) + '1';
  FOR(I, 0, n) cout << s[I] << '\n';
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

