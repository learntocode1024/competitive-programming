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
int c[N], r[N], v[N];
int ord[N], tord[N];
int n;
struct DS {
  struct segT {
    struct node {
      i64 s;
      int l, r;
    } a[N<<5];
    int tot = 0;
    int ins(int p, int l, int r, int s, int v) {
      int q = ++tot;
      a[q] = a[p];
      a[q].s += v;
      if (r - l == 1) {
        return q;
      }
      int m = (l + r) >> 1;
      if (s < m) a[q].l = ins(a[p].l, l, m, s, v);
      else a[q].r = ins(a[p].r, m, r, s, v);
      return q;
    }
    i64 sum(int p, int q, int l, int r, int s, int t) {
      if (l == s && r == t) return a[p].s - a[q].s;
      int m = (l + r) >> 1;
      i64 ans = 0;
      if (s < m) ans = sum(a[p].l, a[q].l, l, m, s, min(m, t));
      if (t > m) ans += sum(a[p].r, a[q].r, m, r, max(m, s), t);
      return ans;
    }
  } T1, T2;
  int r1[N], r2[N];
  inline void init() {
    FOR(i,1,n) {
      r1[i] = T1.ins(r1[i-1], 1, n+1, ord[i], r[i]);
      r2[i] = T2.ins(r2[i-1], 1, n+1, ord[i], c[i]);
    }
    sort(v+1,v+n+1);
  }
  inline i64 sum(int l, int r, int t) {
    int lim = upper_bound(v+1,v+n+1,t) - v;
    i64 ans = 0;
    if (lim > 1) ans = T2.sum(r2[r], r2[l-1], 1, n+1, 1, lim);
    if (lim <= n) ans += t * T1.sum(r1[r], r1[l-1], 1, n+1, lim, n+1);
    return ans;
  }
} T;

map<pii,pii> S;
int lim;

inline void solve() {
  rd(n);
  FOR(i,1,n) rd(c[i], r[i]), v[i] = ceil(1.0l * c[i] / r[i]), chkmax(lim,v[i]+1);
  iota(tord+1,tord+n+1,1);
  sort(tord+1,tord+n+1,[](int a, int b) { return v[a] < v[b]; });
  FOR(i,1,n) ord[tord[i]] = i;
  T.init();
  S[{1,n}] = {-lim,0};
  int t = 0;
  int q;
  rd(q);
  i64 ans = 0;
  while (q--) {
    int t;
    i64 x;
    rd(t, x);
    int r = 0;
    for (auto u = S.begin(); u != S.end();) {
      if (u->se.se != 0) {
        int i = u->fi.fi;
        int val = min(1ll*c[i], 1ll * ::r[i] * (t - u->se.fi) + u->se.se);
        if (val <= x) {
          x -= val;
          r = i;
          u = S.erase(u);
        } else {
          r = i-1;
          val -= x;
          x = 0;
          u->se.fi = t;
          u->se.se = val;
        }
      } else {
        int L = u->fi.fi, R = u->fi.se;
        i64 tot = T.sum(L,R,t-u->se.fi);
        if (tot <= x) {
          x -= tot;
          r = R;
          u = S.erase(u);
        } else {
          int vL = min(1ll*c[L], 1ll * ::r[L] * (t - u->se.fi));
          if (vL > x) {
            vL -= x;
            x = 0;
            r = L-1;
            if (R>L) S[{L+1,R}] = u->se;
            u = S.erase(u);
            S[{L,L}] = {t, vL};
          } else {
            int ll = L, rr = R;
            while (rr - ll > 1) {
              int m = (ll + rr) >> 1;
              if (T.sum(L, m, t-u->se.fi) <= x) ll = m;
              else rr = m;
            }
            x -= T.sum(L,ll,t-u->se.fi);
            r = ll;
            if (x) {
              vL = min(1ll*c[ll+1], 1ll * ::r[ll+1] * (t - u->se.fi)) - x;
              x = 0;
              S[{ll+1,ll+1}] = {t,vL};
              ++ll;
            }
            ++ll;
            if (ll <= R) {
              S[{ll,R}] = u->se;
            }
            u = S.erase(u);
          }
        }
      }
      if (!x) break;
    }
    ans += x;
    if (r) S[{1,r}] = {t, 0};
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

