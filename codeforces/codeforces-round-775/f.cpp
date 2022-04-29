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
const int N = 5e5+5;
const i64 inf = 1e18;
i64 a[3][N], dp[N];
i64 s[N], t[N];
vector<pii> g[N];
int n, m;
struct segT {
  i64 a[N<<2];
  i64 mx(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      return a[p];
    }
    int m = (l + r) >> 1;
    i64 ans = -inf;
    if (s < m) ans = mx(p<<1,l,m,s,min(m,t));
    if (t > m) chkmax(ans, mx(p<<1|1,m,r,max(m,s),t));
    return ans;
  }
  void ins(int p, int l, int r, int t, i64 v) {
    chkmax(a[p], v);
    if (r - l == 1) return;
    int m = (l+r)>>1;
    if (t<m) ins(p<<1,l,m,t,v);
    else ins(p<<1|1,m,r,t,v);
  }
} T, T2;
i64 ans = -inf;

struct seg {
  int l, r, v;
};

i64 x[N];

i64 cdq(int l, int r, vector<seg> &q) {
  if (l == r) {
    for (auto v : q) {
      chkmax(ans, dp[l] + t[l] - v.v);
    }
    return dp[l] + t[l];
  }
  int m = (l+r)>>1;
  x[m] = dp[m];
  x[m+1] = t[m+1];
  ROF(i,l,m-1) x[i] = max(x[i+1],dp[i]);
  FOR(i,m+2,r) x[i] = max(x[i-1],t[i]);
  vector<seg> L, R;
  i64 mv = inf, mc = x[l] + x[r];
  for (auto v : q) {
    if (v.l == l && v.r == r) chkmin(mv, (i64)v.v);
    else if (v.r <= m) L.pb(v);
    else if (v.l > m) R.pb(v);
    else {
      chkmax(ans, x[v.l] + x[v.r] - v.v);
      L.pb(seg{v.l,m,v.v});
      R.pb(seg{m+1,v.r,v.v});
    }
  }
  chkmax(mc, cdq(l,m,L));
  chkmax(mc, cdq(m+1,r,R));
  chkmax(ans, mc-mv);
  return mc;
}

inline void solve() {
  rd(n,m);
  FOR(i,0,n<<2) T.a[i] = T2.a[i] = -inf;
  FOR(i,0,2)FOR(j,1,n) rd(a[i][j]), a[i][j] += a[i][j-1];
  FOR(i,1,n) s[i] = a[0][i] - a[1][i-1];
  FOR(i,1,n) t[i] = a[1][i] - a[2][i-1] + a[2][n];
  vector<seg> G;
  FOR(i,1,n) T2.ins(1,1,n+1,i,s[i]);
  FOR(i,1,m) {
    int l,r,v;
    rd(l,r,v);
    G.pb(seg{l,r,v});
    g[r].eb(l,v);
  }
  FOR(i,1,n) {
    dp[i] = -inf;
    for (auto v : g[i]) {
      if (max(1,v.fi-1) < i) chkmax(dp[i], T.mx(1,1,n+1,max(1,v.fi-1),i)-v.se);
      chkmax(dp[i], T2.mx(1,1,n+1,v.fi,i+1)-v.se);
    }
    T.ins(1,1,n+1,i,dp[i]);
  }
  //FOR(i,1,n) cout << dp[i] << " \n"[i==n];
  dp[0] = -inf;
  ROF(i,1,n) dp[i] = max(dp[i-1],s[i]);
  //FOR(i,1,n) cout << dp[i] << " \n"[i==n];
  //FOR(i,1,n) cout << t[i] << " \n"[i==n];
  cdq(1,n,G);
  O(ans);
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

