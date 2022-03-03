#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 5e5+5, K = 45;
int n, k;

class QWQ {
  mt19937 a;
  uniform_int_distribution<int> e{0,1000000000};
public:
  QWQ() {
    int s = chrono::steady_clock::now().time_since_epoch().count();
    O(s);
    a.seed(s);
  }
  inline int operator() () {
    return e(a);
  }
} rng;

struct edge {
  int u, v, w;
  bool operator< (const edge& rhs) const {
    return w < rhs.w;
  }
  inline edge operator+(const int &x) const {
    edge ret;
    ret.w = w;
    ret.u = u+x;
    ret.v = v+x;
    return ret;
  }
};

struct DSU {
  int f[K<<2];
  inline void set(int n) {
    iota(f,f+n+1,0);
  }
  int get(int x) {
    return x == f[x] ? x : (f[x] = get(f[x]));
  }
  bool chk(int u, int v) {
    if (get(u) == get(v)) return 0;
    f[f[u]] = f[v];
    return 1;
  }
} f;

vector<edge> G;
vector<pii> g;
bool tag[K], id[N];

bool dfs1(int u, int fa) {
  int cson = 0;
  for (auto v : g[u]) if (v.fi != fa) cnt += dfs1(v.fi, u);
  tag[u] |= cson > 1;
  return tag[u] || cson != 0;
}

void dfs2(int u, int fa, int anc) {
  
}

struct MST {
  i64 ans;
  int n;
  vector<edge> e;
  MST() = default;
  MST(const MST& a, const MST& b) {
    ans = a.ans + b.ans;
    int mid = min(k-1, min(a.n, b.n));
    n = a.n + b.n - mid;
    mid = a.n - mid + 1;
    for (auto x : a.e) G.pb(x), ans -= x.w;
    for (auto x : b.e) G.pb(x+mid), ans -= x.w;
    sort(begin(G), end(G));
    f.set(n);
    FOR(i, 1, n) g[i].clear();
    for (x : G) {
      if (f.chk(x.u, x.v)) {
        g[x.u].eb(x.v, x.w);
        g[x.v].eb(x.u, x.w);
        ans += x.w;
      }
    }
    G.clear();
    FOR(i,1,k) tag[i] = 1;
    FOR(i,n-k+1,n) tag[i] = 1;
    dfs1(1,0);
    FOR(i,1,n) id[i] = id[i-1] + tag[i];
    dfs2(1,0);
    e.swap(G);
  }
} L[N], R[N];

inline void solve() {
  rd(n,k);
  
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

