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

const int N = 0;
vector<string> s;
vector<vector<bool> > vis;
int n, m;
queue<pii> q;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

inline int tpy(int x, int y) {
  if (x < 0 || y < 0 || y >= m || x >= n) return 0;
  if (s[x][y] == '.') return 2;
  if (s[x][y] == '-') return 3;
  return 1;
}

inline int chk(int x, int y) {
  if (s[x][y] != '.') return 0;
  int p[4];
  FOR(i, 0, 4) {
    p[i] = tpy(x + dx[i], y + dy[i]);
  }
  FOR(i, 0, 4) {
    int to = 0;
    FOR(j, 0, 4) if (i != j) to |= p[j];
    if (to == 1) return 1;
  }
  FOR(i, 0, 4) if (p[i] == 2) return 0;
  return 2;
}

inline void solve() {
  rd(n, m);
  s = vector<string>(n);
  vis = vector<vector<bool> > (n, vector<bool>(m, 0));
  FOR(i, 0, n) cin >> s[i];
  pii O;
  FOR(i, 0, n) FOR(j, 0, m) if (s[i][j] == 'L') {
    O = {i, j};
    break;
  }
  q.push(O);
  while (!q.empty()) {
    pii u = q.front();
    q.pop();
    if (vis[u.fi][u.se]) continue;
    vis[u.fi][u.se] = 1;
    FOR(i, 0, 4) {
      int tx = u.fi + dx[i], ty = u.se + dy[i];
      if (tx < 0 || tx >= n || ty < 0 || ty >= m || vis[tx][ty]) continue;
      int val = chk(tx, ty);
      if (!val) continue;
      if (val == 1) s[tx][ty] = '+';
      else s[tx][ty] = '-';
      q.push({tx, ty});
    }
  }
  FOR(i, 0, n) FOR(j, 0, m) if (s[i][j] == '-') s[i][j] = '.';
  FOR(i, 0, n) cout << s[i] << '\n';
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

