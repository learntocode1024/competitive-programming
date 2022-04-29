#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
template <typename T> void rd(T &a) { cin >> a; }
template <typename A, typename... B> void rd(A &a, B &...b) {
  cin >> a;
  rd(b...);
}
template <typename A> void O(const A &a) { cout << a << '\n'; }
template <typename A, typename... B> void O(const A &a, const B &...b) {
  cout << a << ' ';
  O(b...);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<i64, i64> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void chkmin(T &a, const T b) { a = min(a, b); }
template <typename T> inline void chkmax(T &a, const T b) { a = max(a, b); }

//#define MULTI
const int N = 5e5 + 5;
const i64 inf = 1e18;
int n, q;
bool typ;
int a[N], b[N];
vector<pii> f[N << 2];

inline void up(int p) {
  auto &L = f[p << 1], &R = f[p << 1 | 1], &u = f[p];
  for (int i = 0, j = 0; i < L.size(); ++i) {
    i64 l = L[i].fi + L[i].se,
        r = i == L.size() - 1 ? inf : L[i + 1].fi + L[i].se;
    while (j < R.size() - 1 && R[j + 1].fi <= l)
      ++j;
    u.eb(L[i].fi, L[i].se + R[j].se);
    int jo = j;
    if (j < R.size() - 1 && R[j + 1].fi <= r)
      ++j;
    while (j < R.size() - 1 && R[j + 1].fi <= r) {
      u.eb(R[j].fi - L[i].se, L[i].se + R[j].se);
      ++j;
    }
    if (R[j].fi < r && jo != j)
      u.eb(R[j].fi - L[i].se, L[i].se + R[j].se);
  }
  u.shrink_to_fit();
}

void build(int p, int l, int r) {
  if (r - l == 1) {
    f[p] = {{0, 0}, {a[l] + 1, b[l]}};
    return;
  }
  int m = (l + r) >> 1;
  build(p << 1, l, m);
  build(p << 1 | 1, m, r);
  up(p);
}

void qry(int p, int l, int r, int s, int t, i64 &v) {
  if (l == s && r == t) {
    auto it = lower_bound(begin(f[p]), end(f[p]), mkp(v, inf));
    if (it != f[p].begin()) --it;
    v += it->se;
    return;
  }
  int m = (l + r) >> 1;
  if (s < m)
    qry(p << 1, l, m, s, min(m, t), v);
  if (t > m)
    qry(p << 1 | 1, m, r, max(m, s), t, v);
}

i64 ans;

inline void solve() {
  rd(n, q, typ);
  FOR(i, 1, n) rd(a[i]);
  FOR(i, 1, n) rd(b[i]);
  build(1, 1, n + 1);
  while (q--) {
    i64 l, r;
    i64 x;
    rd(l, r, x);
    if (typ)
      l ^= ans, r ^= ans, x ^= ans;
    ++r;
    qry(1, 1, n + 1, l, r, x);
    ans = x;
    O(x);
  }
}

int main() {
#ifndef MISAKA
  freopen("contest.in", "r", stdin);
  freopen("contest.out", "w", stdout);
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
