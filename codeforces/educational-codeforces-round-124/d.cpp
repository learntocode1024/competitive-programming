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
map<pii, int> id;
map<pii, pii> vis;
set<pii> S;
const int dx[4] = {1,-1,0,0}, dy[4] = {0,0,-1,1};

pii qu[N<<4];
pii ans[N];
int hd, tl;

inline void solve() {
  int n;
  rd(n);
  FOR(i,1,n) {
    int x, y;
    rd(x,y);
    id[{x,y}] = i;
    FOR(k,0,3) {
      S.insert(mkp(x+dx[k],y+dy[k]));
    }
  }
  for (auto v : id) S.erase(v.fi);
  hd = 1;
  for (auto v : S) {
    qu[++tl] = v;
    vis[v] = v;
  }
  while (hd <= tl) {
    pii u = qu[hd++];
    FOR(k,0,3) {
      int x = u.fi+dx[k], y = u.se+dy[k];
      if (vis.find({x,y})!=vis.end() || id.find({x,y}) == id.end()) continue;
      vis[{x,y}] = vis[u];
      qu[++tl] = mkp(x,y);
    }
  }
  for (auto v : id) {
    ans[v.se] = vis[v.fi];
  }
  FOR(i,1,n) O(ans[i].fi, ans[i].se);
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

