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

#define MX 500005
int n;

namespace segtree {
int rt;
struct node {
  int lc, rc, len;
  char v;
  bool flp;
  inline void flip() {
    swap(lc, rc), flp ^= 1;
  }
} a[MX << 2];
int frd[MX << 2], tot, totf;
int init() {
  return (totf) ? frd[totf--] : ++tot;
}
void del(int u) {
  memset(a + u, 0, sizeof (node));
  frd[++totf] = u;
}
void up(int u) {
  a[u].len = a[a[u].lc].len + a[a[u].rc].len;
}
void down(int u) {
  if (a[u].flp) {
    a[a[u].lc].flip();
    a[a[u].rc].flip();
    a[u].flp ^= 1;
  }
}
char *A;
void _build(int &p, int l, int r) {
  if (!p) p = init();
  if (r - l == 1) {
    a[p].v = A[l];
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
    if (a[M[i]].len > 1) a[M[i]].flip();
  }
  reverse(M + 1, M + tm + 1);
  merge();
}

void walk(int p, int l, int r) {
  if ((r - l) == 1) {
    printf("%c", a[p].v);
    return;
  }
  down(p);
  int mid = l + a[a[p].lc].len;
  walk(a[p].lc, l, mid);
  walk(a[p].rc, mid, r);
}

void output() {
  walk(rt, 0, n);
  putchar('\n');
}
}

char a[MX];
int m;
void solve() {
  cin >> n >> m >> a;
  segtree::A = a;
  segtree::build();
  while (m--) {
    int r;
    cin >> r;
    segtree::rev(0, r);
  }
  segtree::output();
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
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
