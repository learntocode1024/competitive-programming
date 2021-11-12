#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned u32;
typedef unsigned long long u64;
typedef pair<int, int> pii;
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= (j); --i)
template <typename T>
inline void chkmin(T& a, const T b) {
  a = min(a, b);
}
template <typename T>
inline void chkmax(T& a, const T b) {
  a = max(a, b);
}

const int N = 5e5+5;
int n;
char x[N];

struct segT {
  struct node {
    int l, r, c;
    char v;
    bool f;
    inline void flp() {
      swap(l, r);
      f ^= 1;
    }
  } a[N << 2];
  int rt;
  int tot;
  int frd[N << 2], tl;
  inline int get() {
    if (!tl) return ++tot;
    memset(&a[frd[tl]], 0, sizeof(node));
    return frd[tl--];
  }
  inline void del(int x) {
    frd[++tl] = x;
  }
  inline void down(int p) {
    if (a[p].f) {
      a[p].f = 0;
      a[a[p].l].flp();
      a[a[p].r].flp();
    }
  }
  int L[N<<2], M[N<<2], R[N<<2];
  int cl, cm, cr;
  int ll, rr;
  void _flip(int p, int l, int r) {
    assert(p <= tot);
    if (l >= ll && r <= rr) {
      M[++cm] = p;
      return;
    }
    if (r <= ll) {
      L[++cl] = p;
      return;
    }
    if (l >= rr) {
      R[++cr] = p;
      return;
    }
    down(p);
    int mid = l + a[a[p].l].c;
    _flip(a[p].l, l, mid);
    _flip(a[p].r, mid, r);
    del(p);
  }
  inline int _merge(int lp, int rp) {
    int cur = get();
    assert(cur <= tot);
    a[cur].c = a[lp].c + a[rp].c;
    a[cur].l = lp;
    a[cur].r = rp;
    return cur;
  }
  inline void flip(int l, int r) {
    ll = l;
    rr = r;
    _flip(rt, 1, n + 1);
    reverse(M + 1, M + cm + 1);
    FOR(i, 1, cm + 1) {
      a[M[i]].flp();
    }
    FOR(i, 1, cm + 1) {
      L[cl + i] = M[i];
    }
    cl += cm;
    FOR(i, 1, cr + 1) {
      L[cl + i] = R[i];
    }
    cl += cr;
    while (cl > 1) {
      for (int i = 1; i <= cl / 2; ++i) {
        L[i] = _merge(L[i * 2 - 1], L[i * 2]);
      }
      if (cl & 1) {
        L[cl / 2 + 1] = L[cl];
        cl = cl / 2 + 1;
      } else cl >>= 1;
    }
    rt = L[1];
    cl = cr = cm = 0;
  }
  void _build(int &p, int l, int r) {
    p = get();
    a[p].c = r - l;
    if (r - l == 1) {
      a[p].v = x[l];
      return;
    }
    int mid = (l + r) >> 1;
    _build(a[p].l, l, mid);
    _build(a[p].r, mid, r);
  }
  inline void build() {
    _build(rt, 1, n + 1);
  }
  void _walk(int p) {
    if (!p) return;
    assert(p <= tot);
    if (a[p].c == 1) {
      // cout << a[p].v;eeee
      return;
    }
    down(p);
    _walk(a[p].l);
    _walk(a[p].r);
  }
  inline void walk() {
    _walk(rt);
  }
} T;

inline void solve() {
  int k;
  cin >> n >> k >> x + 1;
  T.build();
  while (k--) {
    int r;
    cin >> r;
    T.flip(1, r + 1);
  }
  cerr << T.tot << '\n';
  T.walk();
  cout << '\n';
}

int main() {
#ifndef MISAKA
<<<<<<< HEAD
=======
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
>>>>>>> 0e749f1d98248ea37d67a437f97c467eaebd3db7
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  solve();
  return 0;
}
<<<<<<< HEAD
=======
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
>>>>>>> 0e749f1d98248ea37d67a437f97c467eaebd3db7
