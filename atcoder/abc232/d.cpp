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

const int N = 105;
char c[N][N];
bool v[N][N];
const int dx[2] = {1, 0};
const int dy[2] = {0, 1};
int h, w;

inline void solve() {
  rd(h,w);
  FOR(i, 0, h) cin >> c[i];
    if (c[0][0] == '#') {
      println(0);
      return;
  }
  queue<pii> q;
  q.push(mkp(0, 0));
  int ans = 0;
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    if (v[u.fi][u.se]) continue;
    v[u.fi][u.se] = 1;
    chkmax(ans, u.fi + u.se);
    FOR(i, 0, 2) {
      int x = u.fi + dx[i], y = u.se + dy[i];
      if (x < 0 || y < 0 || x >= h || y >= w|| v[x][y] || c[x][y] == '#') continue;
      q.push(mkp(x, y));
    }
  }
  println(ans + 1);
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

