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
const int P = 1e9+7;
int n, m;
vector<pii> g[N];
int lt[N], typ[N];
int l2[N];

struct seg1 {
  short a[N<<2];
  void ins(int p, int l, int r, int s, int v) {
    a[p] |= v;
    if (r - l == 1) return;
    int m = (l + r) >> 1;
    if (s < m) ins(p<<1,l,m,s,v);
    else ins(p<<1|1,m,r,s,v);
  }
  void clr(int p, int l, int r, int s) {
    if (r - l == 1) {
      a[p] = 0;
      return;
    }
    int m = (l + r) >> 1;
    if (s < m) clr(p<<1,l,m,s);
    else clr(p<<1|1,m,r,s);
    a[p] = a[p<<1] | a[p<<1|1];
  }
  int to = 0;
  int get(int p, int l, int r, int s) {
    if ((s | a[p]) != 3) {
      to = s | a[p];
      return l;
    }
    if (r - l == 1) {
      to = s;
      return r;
    }
    int m = (l + r) >> 1;
    if ((a[p<<1|1] | s) != 3) return get(p<<1, l, m, s | a[p<<1|1]);
    else return get(p<<1|1,m,r,s);
  }
  int g2(int p, int l, int r) {
    if (!a[p]) {
      return l;
    }
    if (r - l == 1) {
      return r;
    }
    int m = (l + r) >> 1;
    if (a[p<<1|1] == 0) return g2(p<<1, l, m);
    else return g2(p<<1|1,m,r);
  }
} T1;

int f[N][26], h[N][26];
int tmp[26];

inline void solve() {
  rd(n, m);
  FOR(i,1,m) {
    int a, b;
    rd(a,b);
    int typ = a > b;
    if (a > b) swap(a, b);
    g[b].eb(a, typ);
  }
  ROF(i,1,n) {
    for (auto [l,t] : g[i]) {
      T1.ins(1,1,n+1,l,1<<t);
    }
    T1.clr(1,1,n+1,i);
    T1.to = 0;
    lt[i] = T1.get(1,1,n+1,0);
    typ[i] = T1.to;
    if (typ[i]) l2[i] = T1.g2(1,1,n+1);
  }
  FOR(i,0,25) f[1][i] = h[1][i] = 1;
  FOR(i,2,n) {
    FOR(j,0,25) tmp[j] = (h[i-1][j] - h[lt[i]-1][j] + P) % P;
    if (lt[i] > i-1) FOR(j,0,25) tmp[j] = 0;
    if (typ[i] == 0) {
      int tt = 0;
      FOR(j,0,25) tt = (tt + tmp[j]) % P;
      FOR(j,0,25) f[i][j] = (tt + P - tmp[j]) % P;
    } else if (typ[i] == 2) {
      FOR(j,1,25) f[i][j] = (f[i][j-1] + tmp[j-1]) % P;
      if (l2[i] < i) {
        FOR(j,0,25) tmp[j] = (h[i-1][j] - h[l2[i]-1][j] + P) % P;
        ROF(j,0,24) tmp[j] = (tmp[j+1] + tmp[j]) % P;
        FOR(j,0,24) f[i][j] = (f[i][j] + tmp[j+1]) % P;
      }
    } else {
      ROF(j,0,24) f[i][j] = (f[i][j+1] + tmp[j+1]) % P;
      if (l2[i] < i) {
        FOR(j,0,25) tmp[j] = (h[i-1][j] - h[l2[i]-1][j] + P) % P;
        FOR(j,1,25) tmp[j] = (tmp[j-1] + tmp[j]) % P;
        FOR(j,1,25) f[i][j] = (f[i][j] + tmp[j-1]) % P;
      }
    }
    FOR(j,0,25) h[i][j] = (h[i-1][j] + f[i][j]) % P;
  }
  int ans = 0;
  FOR(i,0,25) ans = (ans + h[n][i]) % P;
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

