/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 20, 2021
 * Algorithm: command_block's-segment-tree
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
#ifdef MASSIVE_INPUT
namespace IO {
template <int size> struct io {
  char ibuf[size], obuf[size];
  char *o, *o1, *p, *p1;
  io() : o(ibuf), o1(ibuf), p(obuf), p1(obuf + size){};
  ~io() { fwrite(obuf, 1, p - obuf, stdout); }
  inline char gc() {
    return o == o1 && (o1 = (o = ibuf) + fread(ibuf, 1, size, stdin)), *o++;
  };
  inline void pc(char ch) {
    p == p1 &&fwrite(obuf, 1, p - obuf, stdout) && (p = obuf), *p++ = ch;
  }
};
io<1 << 20> f;
inline int read() {
  int x = 0, u = 1;
  char ch = f.gc();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      u = -1;
    ch = f.gc();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + ch - '0';
    ch = f.gc();
  }
  return x * u;
}
} // namespace IO
#else
namespace IO {
char in[1 << 23]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int read() {
  unsigned u = 0, s = 0;

  while (*o && *o <= 32)
    ++o; // skip whitespaces...

  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign

  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)

  return static_cast<int>((u ^ s) + !!s);
}
} // namespace IO
#endif

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { b = min(a, b); }

/*********************************** solution *********************************/
#define MX 100005
int n;

namespace segtree {
int rt;
struct node {
  int lc, rc, len, v;
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
int *A;
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
    printf("%d ", a[p].v);
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

int a[MX];
int m;
void solve() {
  n = IO::read();
  m = IO::read();
  for (int i = 0; i < n; ++i) {
    a[i] = i + 1;
  }
  segtree::A = a;
  segtree::build();
  while (m--) {
    int l = IO::read(), r = IO::read();
    segtree::rev(l - 1, r);
  }
  segtree::output();
}

int main() {
#ifndef MASSIVE_INPUT
  IO::init_in();
#endif
#ifdef MULTI
  int T = IO::read();
  while (T--)
    solve(), T &&clear();
#else
  solve();
#endif
  return 0;
}
