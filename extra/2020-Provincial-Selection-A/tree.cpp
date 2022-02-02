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
const int N = 5.5e5, B = 22;
int tot;
struct Trie {
  int ch[N*B][2], c[N*B], v[N*B];
  inline int xorsum(int rt) {
    return v[rt];
  }
  void ins(int u, int x) {
    ++c[u];
    int cnt = B;
    while (cnt--) {
      if (!ch[u][x&1]) ch[u][x&1] = ++tot;
      v[u] ^= x;
      u = ch[u][x&1];
      ++c[u];
      x >>= 1;
    }
  }
  void add(int u) {
    if (ch[u][1]) add(ch[u][1]);
    swap(ch[u][0], ch[u][1]);
    v[u] = (v[ch[u][0]] ^ v[ch[u][1]]) << 1 | (c[ch[u][1]] & 1);
  }
  int merge(int u, int vv) {
    if (!u || !vv) return u | vv;
    c[u] += c[vv];
    v[u] ^= v[vv];
    ch[u][0] = merge(ch[u][0], ch[vv][0]);
    ch[u][1] = merge(ch[u][1], ch[vv][1]);
    return u;
  }
} T;
vector<int> g[N];
i64 ans;
int n;
int v[N], rt[N];

void dfs(int u) {
  if (g[u].empty()) {
    rt[u] = ++tot;
    T.ins(rt[u], v[u]);
    ans += T.xorsum(rt[u]);
    return;
  }
  for (auto to : g[u]) {
    dfs(to);
    rt[u] = T.merge(rt[u], rt[to]);
  }
  T.add(rt[u]);
  T.ins(rt[u], v[u]);
  ans += T.xorsum(rt[u]);
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n) cin >> v[i+1];
  FOR(i, 2, n + 1) {
    int fa;
    cin >> fa;
    g[fa].pb(i);
  }
  dfs(1);
  println(ans);
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

