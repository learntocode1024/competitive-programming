/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug 17, 2021
 * Algorithm: fhq-treap, DP
 * Difficulty: dmy
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
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
#define MX 200005
i64 a[MX];
int n, q;
i64 lastans = 0;

namespace bst {
struct node {
  int lc, rc, s, w;
  i64 v, t;
} a[MX << 6];
int rts[MX];
int tot;
int cre() {
  a[++tot].s = 1;
  return tot;
}
int cpy(int p) {
  int ret = ++tot;
  memcpy(a + ret, a + p, sizeof(node));
  a[ret].w = rand();
  return ret;
}
void up(int p) {
  a[p].s = a[a[p].lc].s + a[a[p].rc].s + 1;
}
void pushtg(int &p, i64 x) { // create a new node on *any modification
  if (!p) return;
  p = cpy(p);
  a[p].v += x, a[p].t += x;
}
void down(int p) {
  i64 &t = a[p].t;
  if (t) {
    pushtg(a[p].lc, t), pushtg(a[p].rc, t);
    t = 0;
  }
}
void split(int p, int k, int &x, int &y) {
  if (p == 0) return x = y = 0, void();
  down(p);
  if (a[a[p].lc].s <= k)
    x = cpy(p), split(a[x].rc, k, a[x].rc, y), up(x);
  else
    y = cpy(p), split(a[y].lc, k - a[a[p].lc].s - 1, x, a[y].lc), up(y); 
}
int merge(int p, int q) {
  if (!p || !q) return p | q;
  int t;
  down(p);down(q);
  if (a[p].w < a[q].w)
    return t = cpy(p), a[t].rc = merge(a[p].rc, q), up(t), t;
  else return t = cpy(q), a[t].lc = merge(p, a[q].lc), up(t), t;
}
void walk(int p, int t = 0) {
  if (!p) return;
  walk(a[p].lc, t + a[p].t);
  cerr << a[p].v + t << ' ';
  walk((a[p].rc, t + a[p].t));
}
i64 kth(int p, int x) {
  if (x > a[p].s) return -1e9;
  if (a[a[p].lc].s <= x) return a[p].t + kth(a[p].lc, x);
  if (a[a[p].lc].s + 1 < x) return a[p].t + kth(a[p].rc, x - a[a[p].lc].s - 1);
  return a[p].v;
}
i64 val(int i, int c) {
  return kth(rts[i], c);
}
void dp() {
  rts[n + 1] = cre(), rts[n + 2] = cre();
  for (int i = n; i >= 1; --i) {
    int l = 0, r = (n - i + 2) / 2;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (val(i + 1, mid + 1) >= val(i + 2, mid) + ::a[i]) l = mid;
			else r = mid - 1;
		}
		int x, y, z;
		split(rts[i + 1], l + 1, x, z);
		split(rts[i + 2], l, z, y);
		pushtg(y, ::a[i]);
		rts[i] = merge(x, y);
  }
  for (int i = n + 2; i; --i) {
    walk(rts[i]);
    cout << '\n';
  }
}
}

void solve() {
  n = rd(), q = rd();
  for (int i = 1; i <= n; ++i) a[i] = rd();
  bst::dp();
  while (q--) {
    int i = (rd() + lastans) % n + 1, c = (rd() + lastans) % n + 1;
    lastans = bst::val(i, c);
    cout << lastans << '\n';
  }
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
