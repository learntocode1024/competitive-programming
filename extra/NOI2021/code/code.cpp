#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define FILEIO(X) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);
template<typename T>
void chkmax(T& a, const T& b) {
  a = max(a, b);
}
template<typename T>
void chkmin(T& a, const T& b) {
  a = min(a, b);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned i32;
#define MX 200005
const i64 mod = 998244353;
struct mat {
  i64 a[4];
  mat() { a[0] = a[1] = a[2] = a[3] = 0; };
  mat(int x) { a[0] = x, a[1] = a[2] = 1, a[3] = 0; };
  friend mat operator* (const mat &a, const mat &b) {
    mat ret;
    ret.a[0] = (a.a[0] * b.a[0] + a.a[1] * b.a[2]) % mod;
    ret.a[1] = (a.a[0] * b.a[1] + a.a[1] * b.a[3]) % mod;
    ret.a[2] = (a.a[2] * b.a[0] + a.a[3] * b.a[2]) % mod;
    ret.a[3] = (a.a[2] * b.a[1] + a.a[3] * b.a[3]) % mod;
    return ret;
  }
  inline pair<int, int> get() {
    return make_pair(a[0], a[2]);
  }
  inline void print() {
    cout << a[0] << ' ' << a[2] << '\n';
  }
};

int n, q, tot;
i64 a[MX];
char op[MX];

mat E, W, e;
namespace segtree {
int rt;
struct node {
  int lc, rc, len;
  mat v, rv, fv, rfv;
  int tg; // 10 for reverse, 01 for flip
  inline void rev() {
    swap(lc, rc);
    swap(v, rv);
    swap(fv, rfv);
    tg ^= 2;
  }
  inline void flp() {
    swap(v, fv);
    swap(rv, rfv);
    tg ^= 1;
  }
} a[MX << 2];
int frd[MX << 2], tot, totf;
int init() {
  return (totf) ? frd[totf--] : ++tot;
}
void del(int u) {
  memset(a + u, 0, sizeof (mat));
  frd[++totf] = u;
}
void up(int u) {
  a[u].len = a[a[u].lc].len + a[a[u].rc].len;
  a[u].v = a[a[u].lc].v * a[a[u].rc].v;
  a[u].rv = a[a[u].rc].rv * a[a[u].lc].rv;
  a[u].fv = a[a[u].lc].fv * a[a[u].rc].fv;
  a[u].rfv = a[a[u].rc].rfv * a[a[u].lc].rfv;
}
void down(int u) {
  if (a[u].tg & 2) {
    a[a[u].lc].rev();
    a[a[u].rc].rev();
    a[u].tg ^= 2;
  }
  if (a[u].tg & 1) {
    a[a[u].lc].flp();
    a[a[u].rc].flp();
    a[u].tg ^= 1;
  }
}
mat *A, *B;
void _build(int &p, int l, int r) {
  if (!p) p = init();
  if (r - l == 1) {
    a[p].v = a[p].fv = a[p].rv = a[p].rfv = A[l];
    a[p].fv = a[p].rfv = B[l];
    a[p].len = 1;
    return;
  }
  int mid = (l + r) >> 1;
  _build(a[p].lc, l, mid);
  _build(a[p].rc, mid, r);
  up(p);
}

inline void build() { _build(rt, 0, n); }

int L[MX], tl, M[MX], tm, R[MX], tr;
int s, t;
void split(int p, int l, int r) {
  if (r <= s) {
    L[++tl] = p;
    return;
  }
  if (l >= s && r <= t) {
    M[++tm] = p;
    return;
  }
  if (l >= t) {
    R[++tr] = p;
    return;
  }
  down(p);
  int mid = l + a[a[p].lc].len;
  split(a[p].lc, l, mid);
  split(a[p].rc, mid, r);
  del(p);
}

void flip(int p, int l, int r) {
  if (r <= s || l >= t)
    return;
  if (l >= s && r <= t) {
    a[p].flp();
    return;
  }
  down(p);
  int mid = l + a[a[p].lc].len;
  flip(a[p].lc, l, mid);
  flip(a[p].rc, mid, r);
  up(p);
}

int _merge(int lc, int rc) {
  int ret = init();
  a[ret].lc = lc;
  a[ret].rc = rc;
  up(ret);
  return ret;
}

int tmp[MX << 2], tt;
int merge() {
  for (int i = 1; i <= tl; ++i) tmp[++tt] = L[i];
  for (int i = 1; i <= tm; ++i) tmp[++tt] = M[i];
  for (int i = 1; i <= tr; ++i) tmp[++tt] = R[i];
  tl = tm = tr = 0;
  int p;
  while (tt > 1) {
    for (int i = 2; i <= tt; i += 2) {
      p = _merge(tmp[i - 1], tmp[i]);
      tmp[i / 2] = p;
    }
    if (tt & 1) tmp[tt / 2 + 1] = tmp[tt];
    tt = (tt + 1) / 2;
  }
  tt = 0;
  return rt = tmp[1];
}

void rev(int l, int r) {
  s = l, t = r;
  split(rt, 0, n);
  for (int i = 1; i <= tm; ++i) {
    if (a[M[i]].len > 1) a[M[i]].rev();
  }
  reverse(M + 1, M + tm + 1);
  merge();
}
void flp(int l, int r) {
  s = l, t = r;
  flip(rt, 0, n);
}

mat to_val, to_fval;
void mod(int p, int l, int r, int pos) {
  if (a[p].len == 1) {
    a[p].v = a[p].rv = to_val;
    a[p].fv = a[p].rfv = to_fval;
    return;
  }
  int mid = l + a[a[p].lc].len;
  if (pos < mid) mod(a[p].lc, l, mid, pos);
  else mod (a[p].rc, mid, r, pos);
  up(p);
}

void append(int pos, mat v, mat fv) {
  to_val = v;
  to_fval = fv;
  mod(rt, 0, n, pos);
}

void print() {
  a[rt].v.print();
}
}

namespace sol {
mat init[MX], finit[MX];
int L[MX], R[MX];
int O[MX];
void solve() {
  for (int i = 0; i < n; ++i) {
    init[i + 1] = (op[i] == 'E' ? E : W);
    finit[i + 1] = (op[i] == 'W' ? E : W);
  }
  ++n;
  string cur;
  for (int i = 0; i < q; ++i) {
    cin >> cur;
    if (cur == "APPEND") {
      O[i] = 1;
      init[n] = e;
      L[i] = n++;
      char ch;
      cin >> ch;
      R[i] = ch;
    } else if (cur == "REVERSE") {
      O[i] = 2;
      cin >> L[i] >> R[i];
    } else {
      O[i] = 3;
      cin >> L[i] >> R[i];
    }
  }
  segtree::A = init;
  segtree::B = finit;
  segtree::build();
  for (int i = 0; i < q; ++i) {
    segtree::print();
    if (O[i] == 1) {
      segtree::append(L[i], (R[i] == 'E') ? E : W, (R[i] == 'W') ? E : W);
    } else if (O[i] == 2) {
      segtree::rev(L[i], R[i] + 1);
    } else {
      segtree::flp(L[i], R[i] + 1);
    }
  }
  segtree::print();
}
}

int main() {
  e.a[0] = e.a[3] = W.a[0] = W.a[2] = W.a[3] = 1;
  E.a[0] = 2;
  E.a[1] = 1;
  E.a[2] = mod - 1;
  sol::finit[0] = sol::init[0] = mat(0) * mat(1);
  // assignment
  freopen("code.in", "r", stdin);
  freopen("code.out", "w", stdout);
  cin.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> q;
  cin >> op;
  sol::solve();
  return 0;
}
