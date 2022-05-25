/** @file
 * @ingroup cartesian-tree heuristic-merging


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
#define IOFILE "a"
//#define MULTI
const int N = 5e5+5;

int a[N];
unordered_map<int,int> s[N];
int ch[N][2];
i64 ans;

void dfs(int u) {
  if (!u) return;
  int x = ch[u][0], y = ch[u][1];
  dfs(x), dfs(y);
  if (s[x].size() < s[y].size()) swap(x, y);
  for (auto &v : s[y]) if (v.fi < a[u] && s[x].find(a[u] - v.fi) != s[x].end()) ans += 1ll * v.se * s[x][a[u]-v.fi];
  for (auto &v : s[y]) s[x][v.fi] += v.se;
  s[u].swap(s[x]);
  ++s[u][a[u]];
}

int t[N], tot;

inline void sol() {
  int n;
  rd(n);
  FOR(i,1,n) rd(a[i]);
  FOR(i,1,n) {
    int lst = tot;
    while (tot && a[t[tot]] < a[i]) --tot;
    if (tot) ch[t[tot]][1] = i;
    if (tot < lst) ch[i][0] = t[tot+1];
    t[++tot] = i;
  }
  dfs(t[1]);
  O(ans);
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
    sol();
  return 0;
}

