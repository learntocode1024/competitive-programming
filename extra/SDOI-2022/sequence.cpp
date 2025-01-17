/** @file
 * @ingroup


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
//#define MULTI
const int N = 3e5+5, B = 300;
const i64 inf = 1e18;
int n, q;
int b[N], m;
vector<int> p[N];
map<int,int> id;
map<pii, i64> ans;
int big[N], tot;

i64 dp[N], s[N];
int lst[N<<1], d;

inline i64 calc(int ix, int iy) {
  const auto &x = p[ix], &y = p[iy];
  int len = x.size() + y.size();
  d = len;
  FOR(i,0,len<<1) lst[i] = -1;
  lst[d] = 0;
  FOR(i,1,len) dp[i] = -inf;
  i64 ans = -inf;
  for (int i = 0, j = 0, k = 1; i < x.size() || j < y.size(); ++k) {
    if (j == y.size() || i < x.size() && x[i] < y[j]) {
      ++d;
      s[k] = s[k-1] + b[x[i]];
      if (lst[d] != -1) {
        dp[k] = s[k] - s[lst[d]] + max(0ll, dp[lst[d]]);
      }
      lst[d] = k;
      ++i;
    } else {
      --d;
      s[k] = s[k-1] + b[y[j]];
      if (lst[d] != -1) {
        dp[k] = s[k] - s[lst[d]] + max(0ll, dp[lst[d]]);
      }
      lst[d] = k;
      ++j;
    }
    ckmax(ans, dp[k]);
  }
  return ans;
}

inline i64 calc2(int ix, int iy) {
  const auto &x = p[ix], &y = p[iy];
  int len = x.size() + y.size();
  d = len;
  i64 ans = -inf;
  
  return ans;
}

inline void sol() {
  rd(n,q);
  FOR(i,1,n) {
    int a;
    rd(a);
    if (!id[a]) id[a] = ++m;
    p[id[a]].pb(i);
  }
  FOR(i,1,n) rd(b[i]);
  while (q--) {
    int x, y;
    rd(x, y);
    x = id[x], y = id[y];
    if (ans.find({x,y}) != ans.end()) O(ans[{x,y}]);
    else if ((p[x].size() >= B) ^ (p[y].size() >= B)) {
      if (p[x].size() > p[y].size()) swap(x, y);
      O(ans[{x,y}] = ans[{y,x}] = calc2(x, y));
    }
    else O(ans[{x,y}] = ans[{y,x}] = calc(x, y));
  }
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
