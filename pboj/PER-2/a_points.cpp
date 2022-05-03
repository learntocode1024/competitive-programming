/** @file
 * @ingroup segment-tree 


 */
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
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
//#define MULTI
const int N = 2.5e5+5;

// functional
struct segtree_node {
  int l, r;
  int x;
} a[N<<5];
int tot = 0;

inline int cpy(int fr) {
  ++tot;
  a[tot] = a[fr];
  return tot;
}

int ins(int p, int l, int r, int x, int y) {
  p = cpy(p);
  ckmin(a[p].x, y);
  if (l != r) {
    int m = (l + r) >> 1;
    if (x <= m) a[p].l = ins(a[p].l, l, m, x, y);
    else a[p].r = ins(a[p].r, m+1, r, x, y);
  }
  return p;
}

int getans(int p, int l, int r, int x, int y) {
  if (l == r) return max(l + x, a[p].x + y);
  int m = (l + r) >> 1;
  if (a[a[p].l].x + y <= m + x) return getans(a[p].l, l, m, x, y);
  else return min(getans(a[p].r, m+1, r, x, y), a[a[p].l].x + y);
}

int ans[N];
vector<pii> op[N<<2];

void ins(int p, int l, int r, int s, int t, pii v) {
  if (l == s && r == t) {
    op[p].pb(v);
    return;
  }
  int m = (l + r) >> 1;
  if (s <= m) ins(p<<1, l, m, s, min(m, t), v);
  if (t > m) ins(p<<1|1, m+1, r, max(m+1, s), t, v);
}

void run(int p, int l, int r, int t1, int t2, int cur) {
  for (auto &[x, y] : op[p]) {
    if (x < 0) t2 = ins(t2, 0, 2.5e5, ~x, y), ckmin(cur, getans(t1, 0, 2.5e5, ~x, y));
    else t1 = ins(t1, 0, 2.5e5, x, y), ckmin(cur, getans(t2, 0, 2.5e5, x, y));
  }
  if (l == r) ans[l] = cur >= 1e9 ? -1 : cur;
  else {
    int m = (l + r) >> 1;
    int rev = tot;
    run(p<<1, l, m, t1, t2, cur);
    tot = rev;
    run(p<<1|1, m+1, r, t1, t2, cur);
  }
}

inline pii rd() {
  int t, x, y;
  cin >> t >> x >> y;
  if (t == 2) x = ~x;
  return {x, y};
}

map<pii,pii> S;

inline void sol() {
  a[0].x = 1e9;
  int q;
  cin >> q;
  FOR(i,1,q) {
    int o;
    cin >> o;
    pii u = rd();
    if (o == 1) {
      ++S[u].se;
      if (S[u].fi == 0) S[u].fi = i;
    } else {
      --S[u].se;
      if (!S[u].se) {
        ins(1,1,q,S[u].fi,i-1,u);
        S.erase(u);
      }
    }
  }
  for (auto &[u, t] : S) {
    ins(1,1,q,t.fi,q,u);
  }
  run(1,1,q,0,0,1e9);
  FOR(i,1,q) O(ans[i]);
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


