#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

const int N = 4e6+5;
typedef __int128 bst;
typedef pair<i64, pair<bst, int> > plb;
#define ctzll __builtin_ctzll
// priority_queue<plb, vector<plb>, greater<plb> > pq;

using namespace __gnu_pbds;
tree<plb, null_type, less_equal<plb> > S;
// multiset<plb> S;

bst g[105];
i64 w[105];
int n, k, tot = 1;
char s[105][105];
bst l1 = 1;
plb hp[N];
int sz;

inline int ctz128(bst x) {
  u64 hi = x >> 64, lo = x;
  return (!lo) ? ctzll(hi) + 64 : ctzll(lo);
}

inline void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; ++i) cin >> w[i];
  FOR(i, 0, n) cin >> s[i];
  FOR(i, 0, n) FOR(j, i + 1, n) {
    if (s[i][j] == '1') g[i] |= l1 << j;
  }
  bst to = l1 << n;
  --to;
  S.insert({0, {to, 0}});
  // hp[sz++] = {0, {to, 0}};
  // push_heap(hp, hp + sz, greater<plb>());
  while (k > 1 && S.size()) {
    --k;
    // pop_heap(hp, hp + sz, greater<plb>());
    auto u = *S.begin();
    S.erase(S.begin());
    // auto u = hp[--sz];
    // ++ss[u.se.se];
    // cerr << u.se.se << '\n';
    if (u.se.se >= 20) continue;
    for (bst i = u.se.fi; i; i -= i & -i) {
      int v = ctz128(i);
      if (u.fi + w[v] <= S.rbegin()->fi) S.insert({u.fi + w[v], {u.se.fi & g[v], u.se.se + 1}});
      if (S.size() > k) S.erase(--S.end());
      // hp[sz++] = {u.fi + w[v], {u.se.fi & g[v], u.se.se + 1}};
      // push_heap(hp, hp + sz, greater<plb>());
    }
  // FOR(i, 0, 21) cerr << ss[i] << ' ';
  // cerr << sz << ' ' << k;
  // cerr << '\n';
  }
  if (S.empty()) println(-1);
  else {
    // pop_heap(hp, hp + sz, greater<plb>());
    // println(hp[--sz].fi);
    println(S.begin()->fi);
  }
}

int main() {
  // bst t1 = l1 << 120;
  // t1 |= l1 << 121;
  // println(ctz128(t1), ctz128(t1 - (t1 & -t1)));
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

