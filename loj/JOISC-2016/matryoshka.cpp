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
int n, q;
int ans[N];
int r[N], h[N];
int A[N], B[N];
vector<pii> g[N<<1];
int dis1[N<<1], dis2[N<<1], t1, t2;
int c[N<<1];

inline void ch(int x, int v) {
  for (; x <= t2; x += x & -x) {
    chkmax(c[x], v);
  }
}

inline int get(int x) {
  int ret = 0;
  for (; x; x -= x & -x) {
    chkmax(ret, c[x]);
  }
  return ret;
}

inline void solve() {
  rd(n, q);
  FOR(i, 1, n + 1) rd(r[i], h[i]);
  FOR(i, 1, q + 1) rd(A[i], B[i]);
  FOR(i, 1, n + 1) dis1[t1++] = r[i];
  FOR(i, 1, q + 1) dis1[t1++] = A[i];
  sort(dis1, dis1 + t1);
  t1 = unique(dis1, dis1 + t1) - dis1;
  FOR(i, 1, n + 1) r[i] = t1 - (lower_bound(dis1, dis1 + t1, r[i]) - dis1);
  FOR(i, 1, q + 1) A[i] = t1 - (lower_bound(dis1, dis1 + t1, A[i]) - dis1);
  FOR(i, 1, n + 1) dis2[t2++] = h[i];
  FOR(i, 1, q + 1) dis2[t2++] = B[i];
  sort(dis2, dis2 + t2);
  t2 = unique(dis2, dis2 + t2) - dis2;
  FOR(i, 1, n + 1) h[i] = lower_bound(dis2, dis2 + t2, h[i]) - dis2 + 1;
  FOR(i, 1, q + 1) B[i] = lower_bound(dis2, dis2 + t2, B[i]) - dis2 + 1;
  // wtf
  FOR(i, 1, n + 1) g[r[i]].eb(h[i], 0);
  FOR(i, 1, q + 1) g[A[i]].eb(B[i], i);
  FOR(i, 1, t1 + 1) {
    sort(g[i].begin(), g[i].end());
    for (auto v : g[i]) {
      if (v.se) continue;
      int cur = get(v.fi);
      ch(v.fi, cur + 1);
    }
    for (auto v : g[i]) {
      if (!v.se) continue;
      ans[v.se] = get(v.fi);
    }
  }
  FOR(i, 1, q + 1) {
    cout << ans[i] << '\n';
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

