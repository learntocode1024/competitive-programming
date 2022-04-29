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
const int n = 2e5;
struct seg {
  set<int> S[N<<2];
  int f[N<<2];
  inline void down(int u, int x) {
    if (S[u].find(x) != S[u].end()) {
      S[u].erase(x);
      S[u<<1].insert(x);
      S[u<<1|1].insert(x);
    }
  }
  inline void up(int u) {
    f[u] = max(f[u<<1], f[u<<1|1]);
    chkmin(f[u], S[u].empty()?N:*S[u].begin());
  }
  void ins(int p, int l, int r, int s, int t, int x) {
    if (r == t && l == s) {
      S[p].erase(x);
      up(p);
      return;
    }
    down(p,x);
    int m = (l+r)>>1;
    if (s <= m) ins(p<<1,l,m,s,min(m,t),x);
    if (t > m) ins(p<<1|1,m+1,r,max(s,m+1),t,x);
    up(p);
  }
  int get(int p, int l, int r, int s, int t, int x) {
    chkmin(x, S[p].empty()?N:*S[p].begin());
    if (l == s && r == t) {
      return min(x,f[p]);
    }
    int ret = -1;
    int m = (l+r)>>1;
    if (s <= m) chkmax(ret,get(p<<1,l,m,s,min(m,t),x));
    if (t > m) chkmax(ret,get(p<<1|1,m+1,r,max(s,m+1),t,x));
    chkmin(ret, x);
    return ret;
  }
} T;
int q;
u64 S;

inline void solve() {
  rd(q);
  FOR(i,0,q+1) T.S[1].insert(i);
  FOR(i,3,N<<2) T.f[i-1] = q + 5;
  while (q--) {
    int op;
    rd(op);
    u64 x,y,z;
    if (op==1) {
      rd(x,y,z);
      T.ins(1,0,n,y^S,z^S,x^S);
      O(y^S,z^S,x^S);
    } else {
      rd(x,y);
      x^=S, y ^= S;
      O(x,y);
      int v = T.get(1,0,n,x,y,1e6);
      S += v;
      O(v);
    }
  }
}

int main() {
  freopen("mex1-1.in", "r", stdin);
#ifndef MISAKA
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

