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
const int N = 2e5+5;
int a[N], mn[N], mx[N];
int n, m;
pii b[N];
bool vis[N];

struct segT {
  int a[N<<2], tg[N<<2];
  void add(int p, int l, int r, int s, int t, int v) {
    if (l == s && r == t) {
      a[p] += v;
      tg[p] += v;
      return;
    }
    int mid = (l + r) >> 1;
    a[p<<1] += tg[p];
    a[p<<1|1] += tg[p];
    tg[p<<1] += tg[p];
    tg[p<<1|1] += tg[p];
    tg[p] = 0;
    if (s < mid) add(p<<1, l, mid, s, min(t, mid), v);
    if (t > mid) add(p<<1|1, mid, r, max(s, mid), t, v);
    a[p] = min(a[p<<1], a[p<<1|1]);
  }
  int get(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      return a[p];
    }
    int mid = (l + r) >> 1;
    a[p<<1] += tg[p];
    a[p<<1|1] += tg[p];
    tg[p<<1] += tg[p];
    tg[p<<1|1] += tg[p];
    tg[p] = 0;
    int ret = 1e8;
    if (s < mid) ret = get(p<<1, l, mid, s, min(t, mid));
    if (t > mid) chkmin(ret, get(p<<1|1, mid, r, max(s, mid), t));
    return ret;
  }
} T;

inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) mn[i] = 1e8;
  FOR(i, 1, n + 1) cin >> a[i], chkmin(mn[a[i]], i), chkmax(mx[a[i]], i);
  FOR(i, 1, n + 1) if (mx[i] - mn[i] > 1) {
    b[m++] = {mn[i], mx[i]};
    T.add(1, 1, n + 1, mn[i] + 1, mx[i], 1);
  }
  FOR(i, 0, m) {
    if (T.get(1, 1, n + 1, b[i].fi + 1, b[i].se) > 1) {
      vis[i] = 1;
      T.add(1, 1, n + 1, b[i].fi + 1, b[i].se, -1);
    }
  }
  int ans = n;
  FOR(i, 1, n + 1) 
    if (T.get(1, 1, n + 1, i, i + 1) == 0) --ans;
  int crs = 0;
  FOR(i, 0, m) if (!vis[i]) {
    if (T.get(1, 1, n + 1, b[i].fi, b[i].fi + 1) > 0) ++crs;
    if (T.get(1, 1, n + 1, b[i].se, b[i].se + 1) > 0) ++crs;
  }
  FOR(i, 0, m) if (!vis[i]) {
    println(b[i].fi, b[i].se);
  }
  println(ans - crs/2);
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

