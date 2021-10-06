#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
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

using IO::rd;
const int N = 1e5+5;
int a[N];
int pre[N<<1];
vector<pii> g[N];

struct DS {
  struct node {
    i64 g, f, hg, hf;
  } a[N << 2];
  inline void _down(int p, int h1, int h2) {
    chkmax(a[p].g, a[p].f + h2);
    chkmax(a[p].hg, a[p].hf + h2);
    a[p].f += h1;
    a[p].hf += h1;
  }
  inline void down(int p) {
    _down(p<<1, a[p].hf, a[p].hg);
    _down(p<<1|1, a[p].hf, a[p].hg);
    a[p].hg = a[p].hf = 0;
  }
  inline void up(int p) {
    a[p].g = max(a[p<<1].g, a[p<<1|1].g);
    a[p].f = max(a[p<<1].f, a[p<<1|1].f);
  }
  void ins(int p, int l, int r, int s, int t, int v) {
    if (l == s && r == t) {
      _down(p, v, v);
      return;
    }
    down(p);
    int mid = (l + r) >> 1;
    if (s < mid) ins(p<<1, l, mid, s, min(mid, t), v);
    if (t > mid) ins(p<<1|1, mid, r, max(mid, s), t, v);
    up(p);
  }
  i64 get(int p, int l, int r, int s, int t) {
    if (s == l && r == t) return a[p].g;
    down(p);
    int mid = (l + r) >> 1;
    i64 ret = 0;
    if (s < mid) chkmax(ret, get(p<<1, l, mid, s, min(mid, t)));
    if (t > mid) chkmax(ret, get(p<<1|1, mid, r, max(mid, s), t));
    return ret;
  }
} D;

i64 ans[N];
void solve() {
  int n = rd();
  FOR(i, 1, n + 1) a[i] = rd();
  int q = rd();
  FOR(i, 0, q) {
    int l = rd(), r = rd();
    g[r].emplace_back(l, i);
  }
  FOR(i, 1, n + 1) {
    D.ins(1, 1, n + 1, pre[a[i] + N] + 1, i + 1, a[i]);
    for (auto [j, id] : g[i]) {
      ans[id] = D.get(1, 1, n + 1, j, i + 1);
    }
    pre[a[i] + N] = i;
  }
  FOR(i, 0, q) {
    cout << ans[i] << '\n';
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
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on  multiple test cases
 * - sufficient stress tests / random data tests
*/
