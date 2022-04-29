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
const int MX = 1e9;
int q, L;
#define F(x) FOR(x,0,1)

struct seg {
  struct node {
    i64 mn[2][2];
    i64 tg;
    i64 c;
    int l, r;
    inline void tag(i64 v, bool typ) {
      if (typ) {
        mn[1][1] += v;
        return;
      }
      tg += v;
      c += v;
      F(i)F(j) mn[i][j] += v;
    }
    inline void upd(i64 s[2][2], i64 t[2][2]) {
      F(i) F(j) mn[i][j] = 1e17;
      F(i)F(j) chkmin(mn[i][0], s[i][j]);
      F(i)F(j) chkmin(mn[0][i], t[j][i]);
      F(i) F(j) chkmin(mn[i][j], s[i][0] + t[0][j]);
      F(i) F(j) chkmin(mn[i][j], s[i][1] + t[0][j]);
      F(i) F(j) chkmin(mn[i][j], s[i][0] + t[1][j]);
      F(i) F(j) chkmin(mn[i][j], s[i][1] + t[1][j] - c);
    }
  } a[N<<6];
  int tot;
  inline void ensure(int &p, int l, int r) {
    if (!p) p = ++tot;
    if (l == r) {
      F(i) F(j) if (!i || !j) a[p].mn[i][j] = 1e17;
    }
  }
  inline void up(int p) {
    a[p].upd(a[a[p].l].mn, a[a[p].r].mn);
  }
  inline void down(int p, int l, int r) {
    int m = (l + r) >>1; 
    if (!a[p].tg) return;
    ensure(a[p].l,l,m);
    a[a[p].l].tag(a[p].tg, l == m);
    ensure(a[p].r,m+1,r);
    a[a[p].r].tag(a[p].tg, m + 1 == r);
    a[p].tg = 0;
  }
  inline void u1(int &p, int l, int r, int s, i64 v) {
    ensure(p,l,r);
    if (r == l) {
      a[p].mn[1][1] -= v;
      return;
    }
    down(p, l, r);
    int m = (l+r)>>1;
    if (s <= m) u1(a[p].l, l, m, s, v);
    else u1(a[p].r, m+1, r, s, v);
    up(p);
  }
  inline void u2(int &p, int l, int r, int s, int t, i64 v) {
    ensure(p,l,r);
    if (l == s && r == t) {
      a[p].tag(v, l == r);
      return;
    }
    down(p, l, r);
    int m = (l+r)>>1;
    if (s <= m) u2(a[p].l, l, m, s, min(m, t), v);
    if (t > m) u2(a[p].r, m+1, r, max(m+1,s), t, v);
    if (s <= m && t > m) a[p].c += v;
    up(p);
  }
  int rt = 0;
  inline void ant(int x, int a) {
    u1(rt, 0, MX, x, a);
  }
  inline void sugar(int x, int a) {
    u2(rt, 0, MX, max(0,x-L), min(x+L,MX), a);
  }
  inline i64 operator() () {
    i64 ret = 0;
    F(i)F(j) chkmin(ret, a[rt].mn[i][j]);
    return ret;
  }
} T;

inline void solve() {
  rd(q, L);
  i64 A = 0;
  while (q--) {
    int op, x, a;
    rd(op,x,a);
    if (op == 1) T.ant(x,a), A += a;
    else T.sugar(x,a);
    O(A + T());
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

