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

//#define MULTI
const int N = 5e5+5;
const int B = 350;
int blk[N];
int a[N], r[N];
int n, m;
struct qry {
  int l, r, id;
  bool operator<(const qry &b) const {
    return (blk[l] != blk[b.l]) ? blk[l] < blk[b.l] : ((blk[l] & 1) ? r < b.r : r > b.r);
  }
} q[N];

i64 ans[N], cur;
set<int> S;

inline void ins(int x) {
  auto it = S.insert(a[x]).fi;
  if (S.size() == 1) return;
  if (it == S.begin()) {
    ++it;
    cur += abs(r[*it] - x);
  } else if (it == --S.end()) {
    --it;
    cur += abs(r[*it] - x);
  } else {
    auto it2 = it;
    ++it;
    --it2;
    cur -= abs(r[*it]-r[*it2]);
    cur += abs(r[*it]-x);
    cur += abs(r[*it2]-x);
  }
}

inline void del(int x) {
  auto it0 = S.find(a[x]);
  auto it = it0;
  if (S.size() == 1) return;
  if (it == S.begin()) {
    ++it;
    cur -= abs(r[*it] - x);
  } else if (it == --S.end()) {
    --it;
    cur -= abs(r[*it] - x);
  } else {
    auto it2 = it;
    ++it;
    --it2;
    cur += abs(r[*it]-r[*it2]);
    cur -= abs(r[*it]-x);
    cur -= abs(r[*it2]-x);
  }
  S.erase(it0);
}

inline void solve() {
  cin >> n >> m;
  FOR(i, 1, n + 1) cin >> a[i], r[a[i]] = i;
  for (int i = B; i <= n; i += B) blk[i] = 1;
  FOR(i, B + 1, n + 1) blk[i] += blk[i-1];
  FOR(i, 0, m) cin >> q[i].l >> q[i].r, q[i].id = i;
  sort(q, q + m);
  int l = 1, r = 0;
  FOR(i, 0, m) {
    while (l > q[i].l) ins(--l);
    while (r < q[i].r) ins(++r);
    while (l < q[i].l) del(l++);
    while (r > q[i].r) del(r--);
    ans[q[i].id] = cur;
  }
  FOR(i, 0, m) cout << ans[i] << '\n';
}

int main() {
#ifndef MISAKA
  freopen("rrads.in", "r", stdin);
  freopen("rrads.out", "w", stdout);
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

