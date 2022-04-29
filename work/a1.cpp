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
const int CNT[8] = {4, 13, 74, 732, 12085, 319988, 13170652, 822378267};
unordered_map<u64, bool> vis;
const int N = 1e6+5;
u64 qu[N], hd, tl;

inline void solve() {
  u64 u = 0ull;
  int k, n;
  rd(k,n);
  FOR(i,1,n) {
    int x;
    rd(x);
    u |= 1ull << x;
  }
  int ans = 0;
  n = 1 << k;
  FOR(_,0,n) {
    u64 u1 = u;
    FOR(i,0,n-1) if ((u1>>i)&1) FOR(j,0,n-1) if ((u1>>j)&1) {
      u |= 1ull<<(i|j);
      u |= 1ull<<(i&j);
    }
  }
  O(u);
  if (u) ++ans;
  qu[hd = tl = 1] = u;
  vis[u] = 1;
  while (hd <= tl) {
    u = qu[hd++];
      if (u == 2052)  {
        O("1");
      }
    FOR(i,0,n-1) if ((~u>>i)&1ull) {
      u64 v = u | (1ull << i);
      FOR(j,0,n-1) if ((u>>j)&1ull) {
        v |= 1ull<<(j|i);
        v |= 1ull<<(j&i);
      }
       if (!vis[v]) {
        qu[++tl] = v;
        ++ans;
        vis[v] = 1;
        O(v);
      }
    }
  }
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

