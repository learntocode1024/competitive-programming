/** @file
 * @ingroup sqrt-division
对于$\# \ge B$的数， $O(n)$处理其与其他数组合。
对于小块之间的组合： 枚举替代区间的端点，离线更新答案。（区间众数可以$O(\max len)$更新，并双指针$O(len + \max len)$查询）.
 */
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(T &x, W &...b) {
  cin >> x;
  rd(b...);
}
#ifndef MISAKA
#define err(...)
#else
#define err(...) fprintf(stderr, __VA_ARGS__)
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
typedef pair<int, int> pii;
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define shuf(L, R) shuffle((L), (R), rng)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void ckmin(T &a, const T &b) { a = min(a, b); }
template <typename T> inline void ckmax(T &a, const T &b) { a = max(a, b); }
//#define IOFILE "filename"
#define MULTI
const int N = 2e5+5;
const int B = 450;
int n;
int a[N];
vector<int> g[N];
int var[N], ky[N], ans;
map<int,int> id;
int cnt = 0;

int getans(const vector<int> &f, const vector<int> &g) {
  static int a[N];
  int m = 0;
  for (int i = 0, j = 0; i < f.size() || j < g.size();) {
    if (i == f.size()) a[++m] = 1, ++j;
    else if (j == g.size()) a[++m] = -1, ++i;
    else if (f[i] < g[j]) a[++m] = -1, ++i;
    else a[++m] = 1, ++j;
  }
  int mx = 0, pre = 0;
  FOR(i,1,m) {
    a[i] += a[i-1];
    ckmax(mx, a[i] - pre);
    ckmin(pre, a[i]);
  }
  return f.size() + mx;
}

bool lo[N];
int lt[B];

inline void clear() {
  FOR(i,1,cnt) g[i].clear(), var[i] = ky[i] = 0;
  ans = 0;
  id.clear();
  cnt = 0;
  FOR(i,0,B-1) lt[i] = 0;
  FOR(i,1,n) a[i] = lo[i] = 0;
  n = 0;
}

inline void sol() {
  rd(n);
  FOR(i,1,n) {
    int x;
    rd(x);
    int &idx = id[x];
    if (!idx) idx = ++cnt, ky[cnt] = x;
    g[idx].pb(i);
    a[i] = idx;
  }
  FOR(i,1,cnt) {
    if (g[i].size() >= B) {
      FOR(j,1,cnt) if (j != i) {
        ckmax(var[i], getans(g[i], g[j]));
        if (g[j].size() < B) ckmax(var[j], getans(g[j], g[i]));
      }
    } else {
      lo[i] = 1;
    }
    ckmax(ans, var[i]);
  }
  lt[0] = n+1;
  FOR(i,1,n) if (lo[a[i]]) {
    int j = 0;
    const vector<int> &h = g[a[i]];
    while (h[j] != i) ++j;
    int j0 = j;
    int k = 0;
    for (; j >= -1; --j) {
      while (k < B - 1 && lt[k+1] > (j == -1 ? 0 : h[j])) ++k;
      ckmax(var[a[i]], j - j0 + 1 + k + (int)h.size());
    }
    for (int j = j0; j >= 0; --j) {
      ckmax(lt[j0 - j + 1], h[j]);
    }
    ckmax(ans, var[a[i]]);
  }
  lt[0] = 0;
  FOR(i,1,B-1) lt[i] = n + 1;
  ROF(i,1,n) if (lo[a[i]]) {
    const vector<int> &h = g[a[i]];
    int j = h.size() - 1;
    while (h[j] != i) --j;
    int j0 = j;
    int k = 0;
    for (; j <= h.size(); ++j) {
      while (k < B - 1 && lt[k+1] < (j == h.size() ? n + 1 : h[j])) ++k;
      ckmax(var[a[i]], j0 - j + 1 + k + (int)h.size());
    }
    for (int j = j0; j < h.size(); ++j) {
      ckmin(lt[j - j0 + 1], h[j]);
    }
    ckmax(ans, var[a[i]]);
  }
  O(ans);
  FOR(i,1,cnt) err("%d: %d\n", ky[i], var[i]);
  vector<int> out;
  FOR(i,1,cnt) if (var[i] == ans) out.pb(ky[i]);
  sort(begin(out), end(out));
  for (auto v : out) O(v);
}

int main() {
#ifndef MISAKA
#ifdef IOFILE
  freopen(IOFILE ".in", "r", stdin);
  freopen(IOFILE ".out", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
    clear(), sol();
  return 0;
}

