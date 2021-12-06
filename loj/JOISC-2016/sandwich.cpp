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

const int N = 405;
const int inf = 1e7;
int r, c;
char s[N][N];
priority_queue<pair<int, pii> > pq;
int d[N][N];
bool vis[N][N];
const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};
const int dx1[4][2] = {{1,1},{-1,-1},{-1,1},{1,-1}};
const int dy1[4][2] = {{-1,1},{1,-1},{1,1},{-1,-1}};

inline void solve() {
  rd(r, c);
  FOR(i, 0, r) cin >> s[i + 1] + 1;
  FOR(i, 1, r + 1) FOR(j, 1, c + 1) d[i][j] = inf;
  if (s[1][1] == 'Z') pq.push({0, {1, 1}}), d[1][1] = 0;
  if (s[1][c] == 'N') pq.push({0, {1, c}}), d[1][c] = 0;
  if (s[r][1] == 'N') pq.push({0, {r, 1}}), d[r][1] = 0;
  if (s[r][c] == 'Z') pq.push({0, {r, c}}), d[r][c] = 0;
  while (!pq.empty()) {
    auto &[w, u] = pq.top();
    if (vis[u.fi][u.se]) continue;
    vis[u.fi][u.se] = 1;
    for (int i = 0; i < 4; ++i) {
      int x = u.fi + dx[i], y = u.se + dy[i];
      int nx = u.fi + dx1[i][s[x][y]=='N'];
      int ny = u.se + dy1[i][s[x][y]=='N'];
    }
  }
  FOR(i, 1, r + 1) FOR(j, 1, c + 1) print(d[i][j] == inf ? -1 : d[i][j], " \n"[j==c]);
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

