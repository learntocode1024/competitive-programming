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

const int N = 1e6+5;
int f[N], s[N], b[N];
bool vis[N];
vector<int> g[N], grp[N];
int n, m;

void dfs(int u, int fa) {
  vis[u] = 1;
  grp[fa].pb(u);
  for (auto v : g[u]) {
    if (!vis[v]) {
      f[v] = fa;
      b[v] = b[u] + (v - u) / 2;
      dfs(v, fa);
    }
  }
}

bool col(int i, int v) {
  for (auto a : grp[i]) {
    s[a] = v + b[a];
    if (a && f[a - 1] < i && s[a - 1] > s[a]) return false;
    if (a < n && f[a + 1] < i && s[a + 1] < s[a]) return false;
  }
  return true;
}

inline void solve() {
  rd(n, m);
  FOR(i, 0, m) {
    int l, r;
    rd(l, r);
    --l;
    g[l].pb(r);
    g[r].pb(l);
  }
  FOR(i, 0, n + 1) {
    if (!vis[i]) {
      f[i] = i;
      dfs(i, i);
    }
  }
  FOR(i, 0, n + 1) {
    if (f[i] == i) {
      if (i == 0) col(i, 0);
      else if (!col(i, s[i - 1])) col(i, s[i - 1] + 1);
    }
  }
  FOR(i, 1, n + 1) {
    cout << "01"[s[i] != s[i - 1]];
  }
  cout << '\n';
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

