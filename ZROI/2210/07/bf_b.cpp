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
const int N = 4005;
vector<pii> g[N];
int n, m, q;
int a[N];
map<int, int> S;

inline void solve() {
  rd(n,m,q);
  FOR(i,1,n) rd(a[i]);
  FOR(i,1,m) {
    int l,r,x;
    rd(l,r,x);
    g[l].eb(i,x);
    g[r+1].eb(i,-x);
  }
  FOR(i,1,q) {
    int l1, r1, l2, r2;
    rd(l1, r1, l2, r2);
    i64 ans = 0;
    S.clear();
    S[1e9+7]=1;
    FOR(i,1,n) {
      for (auto x : g[i]) {
        if (x.fi < l1 || x.fi > r1) continue;
        if (x.se > 0) {
          ++S[x.se];
        } else {
          if (S[-x.se] == 1) S.erase(-x.se);
          else --S[-x.se];
        }
      }
      if (i >= l2 && i <= r2) {
        ans += min(S.begin()->fi, a[i]);
      }
    }
    O(ans);
  }
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

