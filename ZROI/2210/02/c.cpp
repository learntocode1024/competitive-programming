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
const int N = 5e4+5;
int n, m, q;

namespace sub3 {
i64 s[N], a[N<<2];
void build(int p, int l, int r) {
  if (r - l == 1) {
    a[p] = s[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(p<<1, l, mid);
  build(p<<1|1, mid, r);
  a[p] = max(a[p<<1], a[p<<1|1]);
}
i64 mx(int p, int l, int r, int s, int t) {
  if (l == s && r == t) return a[p];
  int mid = (l + r) >> 1;
  i64 ret = 0;
  if (s < mid) chkmax(ret, mx(p<<1, l, mid, s, min(mid, t)));
  if (t > mid) chkmax(ret, mx(p<<1|1, mid, r, max(mid, s), t));
  return ret;
}
inline void work() {
  int x, y, z, w;
  i64 v;
  FOR(i, 0, m) {
    rd(x, y, z, w, v);
    s[y] += v;
    s[w + 1] -= v;
  }
  FOR(i, 2, n + 1) s[i] += s[i - 1];
  build(1, 1, n + 1);
  FOR(i, 0, q) {
    rd(x, y, z, w);
    println(mx(1, 1, n + 1, y, w + 1));
  }
}
}

namespace sub1 {
struct qry {
  int x, y, i;
};
vector<qry> f[105][105];
i64 a[105][105];
i64 b[105][105];
int ans[1000000];
void work() {
  int x, y, z, w;
  i64 v;
  FOR(i, 0, m) {
    rd(x, y, z, w, v);
    a[z+1][w+1] += v;
    a[x][y] += v;
    a[x][w+1] -= v;
    a[z+1][y] -= v;
  }
  FOR(i, 1, n + 1) FOR(j, 1, n + 1) a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
  FOR(i, 0, q) {
    rd(x, y, z, w);
    f[z][w].pb(qry{x, y, i});
  }
  FOR(i, 1, n + 1) FOR(j, 1, n + 1) {
    ROF(x, 1, i + 1) ROF(y, 1, j + 1) b[x][y] = max(a[x][y], max(b[x+1][y], b[x][y+1]));
    for (auto v : f[i][j]) ans[v.i] = b[v.x][v.y];
    ROF(x, 1, i + 1) ROF(y, 1, j + 1) b[x][y] = 0;
  }
  FOR(i, 0, q) println(ans[i]);
}
}

inline void solve() {
  rd(n, m, q);
  if (n <= 100) sub1::work();
  else sub3::work();
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

