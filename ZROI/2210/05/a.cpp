#include <bits/stdc++.h>
using namespace std;
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
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
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
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 1e6+5;
const int mod = 998244353;
inline void red(int &x) { if (x >= mod) x -= mod; }
inline void Mul(int &x, int y) { x = 1ll * x * y % mod; }

struct segT1 {
  int mn[N<<2];
  void upd(int p, int l, int r, int s, int v) {
    if (r - l == 1) {
      mn[p] = v;
      return;
    }
    int mid = (l + r) >> 1;
    if (s < mid) upd(p<<1, l, mid, s, v);
    else upd(p<<1|1, mid, r, s, v);
    mn[p] = min(mn[p<<1], mn[p<<1|1]);
  }
  int L;
  int qry(int p, int l, int r, int k) {
    if (r - l == 1) {
      L = mn[p] + 1;
      return l;
    }
    int mid = (l + r) >> 1;
    if (mn[p<<1] < k) return qry(p<<1, l, mid, k);
    else return qry(p<<1|1, mid, r, k);
  }
} G;

struct segT {
  struct node {
    int s, tg;
  } a[N<<2];
  inline void down(int p) {
    int &tg = a[p].tg;
    if (tg != 1) {
      Mul(a[p<<1].s, tg);
      Mul(a[p<<1].tg, tg);
      Mul(a[p<<1|1].s, tg);
      Mul(a[p<<1|1].tg, tg);
      tg = 1;
    }
  }
  void mul(int p, int l, int r, int s, int t, int v) {
    if (l == s && r == t) {
      Mul(a[p].s, v);
      Mul(a[p].tg, v);
      return;
    }
    int mid = (l + r) >> 1;
    down(p);
    if (s < mid) mul(p<<1, l, mid, s, min(mid, t), v);
    if (t > mid) mul(p<<1|1, mid, r, max(mid, s), t, v);
    red(a[p].s = a[p<<1].s + a[p<<1|1].s);
  }
  void ins(int p, int l, int r, int s, int v) {
    if (r - l == 1) {
      red(a[p].s += v);
      return;
    }
    int mid = (l + r) >> 1;
    down(p);
    if (s < mid) ins(p<<1, l, mid, s, v);
    else ins(p<<1|1, mid, r, s, v);
    red(a[p].s = a[p<<1].s + a[p<<1|1].s);
  }
  int sum(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      return a[p].s;
    }
    int ret = 0, mid = (l + r) >> 1;
    down(p);
    if (s < mid) ret = sum(p<<1, l, mid, s, min(mid, t));
    if (t > mid) red(ret += sum(p<<1|1, mid, r, max(s, mid), t));
    return ret;
  }
} T;

struct numset {
  bool vis[N];
  int pre[N], nxt[N];
  inline void init(int n) {
    FOR(i, 1, n + 3) {
      pre[i] = i - 1;
      nxt[i] = i + 1;
    }
  }
  inline void ins(int x) {
    x += 2;
    if (!vis[x]) {
      vis[x] = 1;
      pre[nxt[x]] = pre[x];
      nxt[pre[x]] = nxt[x];
    }
  }
  inline int mex() {
    return nxt[1] - 2;
  }
} ss;



int a[N], inv[N];
map<int, pii> S;
int n;

inline void solve() {
  rd(n);
  FOR(i, 1, n*4+5) T.a[i].tg = 1;
  inv[0] = inv[1] = 1;
  FOR(i, 2, n + 1) {
    inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
  }
  FOR(i, 1, n + 1) rd(a[i]);
  ss.init(n);
  ss.ins(a[1]);
  T.ins(1, 0, n + 1, 0, 1);
  int r;
  G.upd(1, 0, n + 1, a[1], 1);
  if (a[1] == 0) {
    T.ins(1, 0, n + 1, 1, 1);
    S[1] = mkp(1, 1);
    r = 1;
  } else {
    S[0] = mkp(1, 1);
    r = 0;
  }
  int ans = 0;
  FOR(i, 2, n + 1) {
    int x = a[i];
    ss.ins(x);
    G.upd(1, 0, n + 1, a[i], i);
    if (S.find(x) != S.end()) {
      auto it = S.find(x);
      if (it->fi == 0) r = it->se.se;
      if (it != (--S.end())) { // is not first
        auto it1 = it;
        ++it1; // prev
        int fac = inv[it->fi];
        int v = G.qry(1, 0, n + 1, it->se.se);
        int L = G.L, R = it->se.se;
        while (L > it->se.fi) {
          S[v] = mkp(L, R);
          T.mul(1, 0, n + 1, L - 1, R, 1ll * fac * v % mod);
          R = L - 1;
          v = G.qry(1, 0, n + 1, R);
          L = G.L;
        }
        T.mul(1, 0, n + 1, it->se.fi - 1, R, 1ll * fac * v % mod);
        it1->se.se = R;
        S.erase(it);
      } else if (ss.mex() > x) { // is first
        int to = ss.mex();
        int fac = inv[it->fi];
        int R = it->se.se;
        int v = G.qry(1, 0, n + 1, R);
        int L = G.L;
        do {
          S[v] = mkp(L, R);
          T.mul(1, 0, n + 1, L - 1, R, 1ll * fac * v % mod);
          R = L - 1;
          if (!R) break;
          v = G.qry(1, 0, n + 1, R);
          L = G.L;
        } while (1);
        S.erase(it);
      }
    }
    if (x != 0) {
      if (S.find(0) != S.end()) S[0].se = i;
      else S[0] = mkp(i,i);
    } else {
      if (S.find(1) != S.end()) S[1].se = i;
      else S[1] = mkp(i,i);
      r = i;
    }
    if (r) {
      int cur = T.sum(1, 0, n + 1, 0, r);
      ans = cur;
      T.ins(1, 0, n + 1, i, cur);
    }
  }
  println(ans);
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

