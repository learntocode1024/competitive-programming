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
vector<pii> g[N];
int n, m;
int ans[N], cnt;
int a[N], b[N], op[N];
int f[N], id[N], dep[N];
int bel[N];

int get(int x) {
  return x == bel[x] ? x : (bel[x] = get(bel[x]));
}

void dfs(int u, int fa) {
  for (auto v : g[u]) if (v.fi != fa) {
    dep[v.fi] = dep[u] + 1;
    f[v.fi] = u;
    id[v.fi] = v.se;
    dfs(v.fi, u);
  }
}

int tmp[N];

void merge_path(int u, int v) {
  int cur = 0;
  while (1) {
    u = get(u), v = get(v);
    if (u == v) break;
    if (dep[u] < dep[v]) swap(u, v);
    tmp[cur++] = id[u];
    bel[u] = f[u];
  }
  sort(tmp, tmp + cur);
  FOR(i, 0, cur) {
    ans[tmp[i]] = ++cnt;
  }
}

inline void solve() {
  rd(n, m);
  FOR(i, 1, m + 1) {
    rd(a[i], b[i], op[i]);
    if (op[i] == 1) {
      g[a[i]].eb(b[i], i);
      g[b[i]].eb(a[i], i);
    }
  }
  dfs(1, 0);
  iota(bel, bel + n + 1, 0);
  FOR(i, 1, m + 1) {
    merge_path(a[i], b[i]);
    if (!op[i]) {
      ans[i] = ++cnt;
    }
  }
  FOR(i, 1, m + 1) cout << ans[i] << " \n"[i==m];
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

