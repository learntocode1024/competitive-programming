#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUnCTIOn__ << ": " << #x << " : " << (x) << '\n';
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
const int n = 25;
const i64 inf = 1e18+7;
const i64 tr[5][4][3][3] = {
  {},
  {
    {2,2,2,1,1,1,1,1,1},
    {3,1,-inf,3,1,-inf,-inf,-inf,0},
    {1,1,2,1,1,2,1,1,2},
    {1,1,-inf,3,3,-inf,-inf,-inf,0}
  },
  {
    {1,2,-inf,2,3,-inf,-inf,-inf,0},
    {1,1,1,2,2,2,1,1,1},
    {3,2,-inf,2,1,-inf,-inf,-inf,0},
    {1,2,1,1,2,1,1,2,1}
  },
  {
    {1,1,0,2,2,1,2,2,1},
    {2,3,-inf,1,2,-inf,-inf,-inf,0},
    {1,1,0,2,2,1,2,2,1},
    {2,3,-inf,1,2,-inf,-inf,-inf,0}
  },
  {
    {1,1,1,1,1,1,2,2,2},
    {3,3,-inf,1,1,-inf,-inf,-inf,0},
    {2,1,1,2,1,1,2,1,1},
    {1,3,-inf,1,3,-inf,-inf,-inf,0}
  }
};

i64 tmp[n][n];
i64 tmp2[n];

struct mat {
  i64 c[n][n];
  mat() {
    FOR(i,0,n-1) FOR(j,0,n-1) c[i][j] = i == j ? 0 : -inf;
  }
  mat(i64 h) { // [h0,h1,...h_{n-2},0] -> [h1,h2,...h_{n-2},h,0]
    FOR(i,0,n-1) FOR(j,0,n-1) c[i][j] = -inf;
    FOR(i,0,n-2) c[i][i+1] = 0;
    c[n-2][n-1] = h;
    c[n-1][n-1] = 0;
  }
  inline void apply(const i64 f[3][3], int d) {
    FOR(i,0,2) FOR(j,0,n-1) tmp[i][j] = -inf;
    FOR(i,0,2) FOR(j,0,n-1) FOR(k,0,2) chkmax(tmp[i][j], f[i][k] + c[d+k][j]);
    FOR(i,0,2) FOR(j,0,n-1) c[d+i][j] = tmp[i][j];
  }
  inline void getH(i64 *h) {
    FOR(i,0,n-1) tmp2[i] = h[i], h[i] = -inf;
    FOR(i,0,n-1) FOR(j,0,n-1) chkmax(h[i], c[i][j] + tmp2[j]);
  }
  mat operator* (const mat &b) const {
    mat ret;
    FOR(i,0,n-1) FOR(j,0,n-1) {
      ret.c[i][j] = -inf;
      FOR(k,0,n-1) chkmax(ret.c[i][j], c[i][k] + b.c[k][j]);
    }
    return ret;
  }
};
const int BASE = 100, W = 7;
mat u;
mat r[2005];
mat fpw[W+5][BASE];
int m, k, Q;
i64 H[2505];
i64 h0[n], h[n];
inline void solve() {
  rd(m,k,Q);
  FOR(i,0,m-1) rd(H[i]);
  FOR(i,1,k) {
    int pos, type, dir;
    rd(pos, type, dir);
    u.apply(tr[type][dir], pos);
  }
  FOR(i,0,n-2) {
    h0[i] = H[i];
  }
  u.getH(h0);
  FOR(i,1,m) {
    r[i] = u * mat(H[(n-2+i)%m]) * r[i-1];
  }
  fpw[0][1] = r[m];
  FOR(i,0,W-1) {
    FOR(j,2,BASE-1) {
      fpw[i][j] = fpw[i][j-1] * fpw[i][1];
    }
    fpw[i+1][1] = fpw[i][BASE-1] * fpw[i][1];
  }
  while (Q--) {
    i64 x;
    rd(x);
    --x;
    FOR(i,0,n-1) h[i] = h0[i];
    int rr = x % m;
    x /= m;
    int i = 0;
    while (x) {
      fpw[i++][x % BASE].getH(h);
      x /= BASE;
    }
    r[rr].getH(h);
    O(h[0]);
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

