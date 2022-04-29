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
const int N = 1.5e6+1;
vector<int> g[N];
vector<pii> id[289];
int dis[N];
int low[N], pre[N], cnt[N], pri[N], tot;
int D[N];
int ans[N];
int qu[N], hd, tl;
bool vis[N];

inline void solve() {
  low[1] = 1;
  pre[1] = 1;
  FOR(i,2,N-1) {
    if (!low[i]) {
      low[i] = i;
      pri[tot++] = i;
      cnt[i] = 1;
      pre[i] = 1;
    }
    for (int j = 0; j < tot && pri[j] * i < N; ++j) {
      int to = pri[j] * i;
      low[to] = pri[j];
      if (pri[j] == low[i]) {
        pre[to] = pre[i];
        cnt[to] = cnt[i] + 1;
        break;
      } else {
        pre[to] = i;
        cnt[to] = 1;
      }
    }
  }
  FOR(i,1,N-1) {
    int &d = D[i];
    d = 1;
    int u = i;
    while (u > 1) {
      d *= cnt[u] + 1;
      int pp = i / low[u];
      g[pp].pb(i);
      g[i].pb(pp);
      u = pre[u];
    }
  }
  int q;
  rd(q);
  FOR(i,1,q) {
    int x, y;
    rd(x,y);
    ans[i] = 114514;
    id[D[x]].eb(y, i);
    id[D[y]].eb(x, i);
  }
  FOR(d,1,288) if (!id[d].empty()) {
    hd = 1, tl = 0;
    FOR(i,1,N-1) if (D[i] == d) {
      qu[++tl] = i;
      dis[i] = 0;
      vis[i] = 1;
    } else dis[i] = 114514, vis[i] = 0;
    while (hd <= tl) {
      int u = qu[hd++];
      for (auto v : g[u]) if (!vis[v]) {
        vis[v] = 1;
        qu[++tl] = v;
        dis[v] = dis[u] + 1;
      }
    }
    for (auto v : id[d]) {
      chkmin(ans[v.se], dis[v.fi]);
    }
  }
  FOR(i,1,q) O(ans[i]);
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

