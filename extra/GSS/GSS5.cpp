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
const int N = 1e4+5;
int _a[N];

struct DS {
  struct node {
    i64 l, r, p, s;
    node() = default;
    node(int x) { s = l = r = p = x; };
    node operator+(const node &rhs) const {
      node ret;
      ret.s = s + rhs.s;
      ret.l = max(l, s + rhs.l);
      ret.r = max(rhs.r, r + rhs.s);
      ret.p = max(p, max(rhs.p, r + rhs.l));
      return ret;
    }
  } a[N << 2];
  void build(int p, int l, int r) {
    if (r - l == 1) {
      a[p] = node(_a[l]);
      return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid, r);
    a[p] = a[p<<1] + a[p<<1|1];
  }
  node _qry(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return a[p];
    int mid = (l + r) >> 1;
    if (t <= mid) return _qry(p<<1, l, mid, s, t);
    if (s >= mid) return _qry(p<<1|1, mid, r, s, t);
    return _qry(p<<1, l, mid, s, mid) + _qry(p<<1|1, mid, r, mid, t);
  }
  inline node qry(int p, int l, int r, int s, int t) {
    if (s >= t) return node();
    return _qry(p, l, r, s, t);
  }
} D;

void solve() {
  int n = rd();
  FOR(i, 1, n + 1) _a[i] = rd();
  D.build(1, 1, n + 1);
  int q = rd();
  FOR(i, 0, q) {
    int l1 = rd(), r1 = rd(), l2 = rd(), r2 = rd();
    int _l = min(r1, l2), _r = max(r1, l2);
    auto L = D.qry(1, 1, n + 1, l1, _l);
    auto M = D.qry(1, 1, n + 1, _l, _r + 1);
    auto R = D.qry(1, 1, n + 1, _r + 1, r2 + 1);
    i64 ans;
    if (r1 < l2) {
      ans = M.s + L.r + R.l;
    } else {
      ans = M.p;
      chkmax(ans, (L + M).r + R.l);
      chkmax(ans, L.r + (M + R).l);
    }
    cout << ans << '\n';
  }
}

#define MULTI

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
