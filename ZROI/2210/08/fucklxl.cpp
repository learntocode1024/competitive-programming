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
const int N = 2e5+5;
int n, m;
vector<int> g[N];
struct node {
  int l, r;
  int s;
} a[N<<5];
int tot = 0;
int r[N], rt[N];

int inc(int l, int r, int s) {
  int p = ++tot;
  a[p].s = 1;
  if (r - l == 1) return p;
  int m = (l+r) >> 1;
  if (s < m) a[p].l = inc(l,m,s);
  else a[p].r = inc(m,r,s);
  return p;
}

int merge(int p, int q) {
  if (!p || !q) return p|q;
  a[p].s += a[q].s;
  a[p].l = merge(a[p].l, a[q].l);
  a[p].r = merge(a[p].r, a[q].r);
  return p;
}

int sum(int p, int l, int r, int s, int t) {
  if (!p) return 0;
  if (s == l && r == t) {
    return a[p].s;
  }
  int ret = 0;
  int m = (l+r)>>1;
  if (s<m) ret = sum(a[p].l,l,m,s,min(m,t));
  if (t>m) ret += sum(a[p].r,m,r,max(m,s),t);
  return ret;
}

int find(int p, int l, int r, int s) {
  if (!p || r - l == 1) return a[p].s == 0 ? l : r;
  int m = (l+r)>>1;
  if (s >= m || sum(a[p].l,l,m,s,m) == m-s) return find(a[p].r,m,r,max(s,m));
  else return find(a[p].l,l,m,s);
}

struct seg {
  struct node {
    int tg;
    i64 s;
  } a[N<<2];
  inline void down(int p, int l, int r) {
    int m = (l+r)>>1;
    int &tg = a[p].tg;
    if (tg) {
      a[p<<1].tg += tg;
      a[p<<1].s += 1ll * tg * (m-l);
      a[p<<1|1].tg += tg;
      a[p<<1|1].s += 1ll * tg * (r-m);
      tg = 0;
    }
  }
void add(int p, int l, int r, int s, int t) {
  if (s == l && r == t) {
    a[p].s += r-l;
    ++a[p].tg;
    return;
  }
  i64 ret = 0;
  int m = (l+r)>>1;
  down(p,l,r);
  if (s<m) add(p<<1,l,m,s,min(m,t));
  if (t>m) add(p<<1|1,m,r,max(m,s),t);
  a[p].s = a[p<<1].s + a[p<<1|1].s;
}
i64 sum(int p, int l, int r, int s, int t) {
  if (s == l && r == t) {
    return a[p].s;
  }
  i64 ret = 0;
  int m = (l+r)>>1;
  down(p,l,r);
  if (s<m) ret = sum(p<<1,l,m,s,min(m,t));
  if (t>m) ret += sum(p<<1|1,m,r,max(m,s),t);
  return ret;
}
  
} T;

vector<pii> q[N];
int ans[N];

void dfs(int u) {
  rt[u] = inc(1,n+1,u);
  for (auto v : g[u]) {
    dfs(v);
    merge(rt[u], rt[v]);
  }
  r[u] = find(rt[u],1,n+1,u);
}

inline void solve() {
  rd(n,m);
  int useless;
  FOR(i,1,n) rd(useless);
  FOR(i,2,n) {
    int fa;
    rd(fa);
    g[fa].pb(i);
  }
  dfs(1);
  FOR(i,1,m) {
    int l, r;
    rd(l,r);
    q[l].eb(r,i);
  }
  ROF(i,1,m) {
    T.add(1,1,n+1,i,r[i]);
    for (auto v : q[i]) {
      ans[v.se] = T.sum(1,1,n+1,i,v.fi+1);
    }
  }
  //FOR(i,1,n) cout << r[i] << " \n"[i==n];
  FOR(i,1,m) O(ans[i]);
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

