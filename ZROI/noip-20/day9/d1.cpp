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

const int N = 5e5+5;
const int p = 998244353;
inline void red(int &x) { if (x >= p) x -= p; }
int n, L, q;
vector<int> G[N];
int d[N] = {-1}, son[N], dep[N];
int f1[N], g1[N], f2[N], g2[N];
int *f, *g;

struct lst : vector<int>{
  int &operator[](int x) {
    return (*this)[this->size() - x - 1];
  }
} h[N];

struct tg {
  int d, int v;
  tg() = default;
  tg(int _d, int _v) {
    d = _d, v = _v;
  }
};
vector<tg> tag[N], lev[N];

void decomp(int u, int fa) {
  dep[u] = dep[fa] + 1;
  for (auto v : G[u]) if (v != fa) {
    decomp(v, u);
    if (d[v] > d[son[u]]) son[u] = v;
  }
  d[u] = d[son[u]] + 1;
}

void up(int u, int fa) {
  if (son[u]) {
    up(son[u], u);
    h[u].swap(h[son[u]]);
    if (d[u] >= L) red(f[u] += h[u][L]);
  }
  h[u].pb(1);
  for (auto v : G[u]) if (v != fa && v != son[u]) {
    up(v, u);
    for (int i = 0; i <= min(d[v], L - 1); ++i) {
      if (L - i - 1 <= d[u]) red(f[u] += 1ll * h[u][L - i - 1] * h[v][i]);
    }
    for (int i = 0; i <= d[v]; ++i) {
      h[u][i + 1] += h[v][i];
    }
    h[v].clear();
  }
}

int c[N];

void sum(int u, int fa) {
  
}

inline void solve() {
  cin >> n >> L >> q;
  FOR(i, 1, n) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  decomp(1, 0);
  f = f1;
  g = g1;
  up(1, 0);
  sum(1, 0);
  h[1].clear();
  L = q;
  f = f2;
  g = g2;
  up(1, 0);
  sum(1, 0);

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
