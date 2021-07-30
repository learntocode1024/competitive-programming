/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 21, 2021
 * Algorithm: 
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
char in[1 << 27]; // sizeof in varied in problem
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
using IO::read;
#define MX 100005
int a[MX], blk[MX];
int n, m, k;
const int B = 450;
struct qry {
  int l, r, id;
  i64 ans;
  qry() {};
  qry(int a, int b, int c) : l(a), r(b), id(c) {};
  bool operator<(const qry &b) const {
    return (blk[l] == blk[b.l]) ? r < b.r : blk[l] < blk[r];
  }
  inline void rd(int i) {
    l = read();
    r = read();
    id = i;
  }
} q[MX];

i64 p[MX], cnt[MX];
vector<int> vt;

vector<qry> sq[MX];
i64 res[MX];
void solve() {
  n = read();
  m = read();
  k = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    blk[i] = blk[i - 1] + (i % B == 1);
    cerr << blk[i] << endl;
  }

  for (int i = 1; i <= m; ++i) q[i].rd(i);
  for (int i = 0; i < 16384; ++i) {
    if (__builtin_popcount(i) == k)
      vt.push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    p[i] += cnt[a[i]];
    for (auto j : vt) {
      ++cnt[j ^ a[i]];
    }
  }
  sort(q + 1, q + m + 1);
  int l = 1, r = 1;
  for (int i = 1; i <= m; ++i) {
    if (r < q[i].r) sq[l - 1].emplace_back(r + 1, q[i].r, -i);
    while (r < q[i].r) {
      ++r;
      q[i].ans += p[r];
    }
    if (l > q[i].l) sq[r].emplace_back(q[i].l, l - 1, i);
    while (l > q[i].l) {
      --l;
      q[i].ans -= p[l];
    }
    if (r > q[i].r) sq[l - 1].emplace_back(q[i].r + 1, r, i);
    while (r > q[i].r) {
      q[i].ans -= p[r];
      --r;
    }
    if (l < q[i].l) sq[r].emplace_back(l, q[i].l - 1, -i);
    while (l < q[i].l) {
      q[i].ans += p[l];
      ++l;
    }
  }
  for (int i = 0; i < 16384; ++i) cnt[i] = 0;
  for (int i = 1; i <= n; ++i) {
    for (auto j : vt) {
      ++cnt[j ^ a[i]];
    }
    for (auto s : sq[i]) {
      for (int j = s.l; j <= s.r; ++j) {
        i64 cur = cnt[a[j]];
        if (k == 0 && j <= i) --cur; // self-xor
        if (s.id < 0) q[-s.id].ans -= cur;
        else q[s.id].ans += cur;
      }
    }
  }
  for (int i = 2; i <= m; ++i) q[i].ans += q[i - 1].ans;
  for (int i = 1; i <= m; ++i) res[q[i].id] = q[i].ans;
  for (int i = 1; i <= m; ++i) cout << res[i] << '\n';
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
