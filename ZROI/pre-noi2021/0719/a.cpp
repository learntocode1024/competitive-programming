/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 19, 2021
 * Algorithm: command_block's-segtree
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 600005

template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  b = min(a, b);
}

int n, q;

namespace BF {
bitset<600006> t;
char s[600006];
int a, b;
inline void getans() {
  for (int i = 0; i < n; ++i) {
    while (i < n && t[i] == t[i + 1]) ++i;
    a += t[i];
    b += !t[i];
  }
  /* a -= t[0] && t[n - 1]; */
  /* b -= !t[0] && !t[n - 1]; */
  /* printf("%d\n", min(a, b) + 1); */
  /* cout << t.to_string().substr(600006 - n, n) << endl; */
}
void solve() {
  n *= 6;
  scanf("%s", s);
  for (int i = 0; i < n; ++i) {
    t[i] = s[i] != '0';
  }
  getans();
  printf("%d\n", min(a - t[0] && t[n - 1], b - !t[0] && !t[n - 1]) + 1);
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (l == r) {
      --l;
      if (l && l + 1 != n && t[l - 1] == t[l + 1]) {
        if (t[l] == t[l - 1]) ++a, ++b;
        else --a, --b;
      }
      if(!l) {
        
      }
      if (l + 1 == n) {

      }
      t.flip(l);
    }
    else {
      int len = (r - l + n) % n + 1;
      int r = l * 2 + len - 3;
      for (int i = l - 1; i * 2 < r; ++i)
        if (t[i % n] != t[(r - i) % n]) t.flip(i % n), t.flip((r - i) % n);
    }
    printf("%d\n", min(a - t[0] && t[n - 1], b - !t[0] && !t[n - 1]) + 1);
  }
}
}

namespace segtree {
int rt;
struct node {
  int lc, rc, len, c;
  bool flp, l, r;
  inline void flip() {
    swap(lc, rc), flp ^= 1, swap(l, r);
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
  a[u].l = a[a[u].lc].l;
  a[u].r = a[a[u].rc].r;
  a[u].c = a[a[u].lc].c + a[a[u].rc].c - (a[a[u].lc].r == a[a[u].rc].l);
  
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
    a[p].l = a[p].r = A[l];
    a[p].c = 1;
    a[p].len = 1;
    return;
  }
  int mid = (l + r) >> 1;
  _build(a[p].lc, l, mid);
  _build(a[p].rc, mid, r);
  up(p);
}

inline void build() { _build(rt, 0, n); 
  cout << (a[rt].c - (a[rt].l == a[rt].r)) / 2 + 1 << '\n';}

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
  cout << (a[rt].c - (a[rt].l == a[rt].r)) / 2 + 1 << '\n';
}
int pos;
void _flip(int p, int l, int r) {
  if (r - l == 1) {
    a[p].l ^= 1;
    a[p].r ^= 1;
    return;
  }
  down(p);
  int mid = l + a[a[p].lc].len;
  if (pos < mid) _flip(a[p].lc, l, mid);
  else _flip(a[p].rc, mid, r);
  up(p);
}
void flip(int p) {
  pos = p;
  _flip(rt, 0, n);
  cout << (a[rt].c - (a[rt].l == a[rt].r)) / 2 + 1 << '\n';
}
void rev2(int l, int r) {
  --l;
  s = r, t = l;
  split(rt, 0, n);
  for (int i = 1; i <= tl; ++i)
    if (a[L[i]].len > 1) a[L[i]].flip();
  for (int i = 1; i <= tr; ++i)
    if (a[R[i]].len > 1) a[R[i]].flip();
  for (int i = 0; i < min(tl, tr); ++i)
    swap(L[tl - i], R[1 + i]);
  if (tl - tr > 1) reverse(L + 1, L + tl - tr + 1);
  if (tr - tl > 1) reverse(R + tl + 1, R + tr + 1);
  merge();
  cout << (a[rt].c - (a[rt].l == a[rt].r)) / 2 + 1 << '\n';
}
void walk(int p) {
  if (!p) return;
  if (a[p].len == 1) {
    cerr << (int)a[p].l;
  }
  down(p);
  walk(a[p].lc);
  walk(a[p].rc);
}
}

namespace SOL {
char s[MX];
int a[MX];
void solve() {
  cin >> n >> q;
  n *= 6;
  cin >> s;
  for (int i = 0; i < n; ++i) {
    a[i] = s[i] - '0';
  }
  segtree::A = a;
  segtree::build();
  while (q--) {
    int l, r;
    cin >> l >> r;
    if (l < r) segtree::rev(l - 1, r);
    if (l == r) segtree::flip(l - 1);
    if (l > r) segtree::rev2(l, r);
    /* segtree::walk(segtree::rt); */
    /* cerr << endl; */
  }
}
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  SOL::solve();
  return 0;
}

