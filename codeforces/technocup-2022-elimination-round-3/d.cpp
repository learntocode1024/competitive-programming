#include <bits/stdc++.h>
using namespace std;
template <typename T>
void rd(T& a) {
  cin >> a;
}
template <typename A, typename... B>
void rd(A& a, B&... b) {
  cin >> a;
  rd(b...);
}
template <typename A>
void print(const A& a) {
  cout << a;
}
template <typename A, typename... B>
void print(const A& a, const B&... b) {
  cout << a;
  print(b...);
}
template <typename A>
void println(const A& a) {
  cout << a << '\n';
}
template <typename A>
void cerrln(const A& a) {
  cerr << a << '\n';
}
template <typename A, typename... B>
void println(const A& a, const B&... b) {
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
#define ROF(i, j, k) for (int i = ((k)-1); i >= j; --i)
template <typename T>
inline void chkmin(T& a, const T b) {
  a = min(a, b);
}
template <typename T>
inline void chkmax(T& a, const T b) {
  a = max(a, b);
}

const int N = 5e5 + 5;
set<pii> S;
int a[N], b[N], nxt[N], f[N];
bool v[N];
int n;
int g(int c) {
  if (c == f[c]) return c;
  return (f[c] = g(f[c]));
}
int cnt[N];
vector<int> bel[N];
int C = 0;
inline void solve() {
  ++C;
  cin >> n;
  S.clear();
  FOR(i, 1, n + 1) cin >> a[i];
  if (C == 130) {
    cerrln(n);
    FOR(i, 1, n + 1) cerrln(a[i]);
  }
  FOR(i, 1, n + 1) v[i] = nxt[i] = cnt[i] = 0, bel[i].clear();
  copy(a + 1, a + n + 1, b + 1);
  sort(b + 1, b + n + 1);
  FOR(i, 1, n + 1) S.insert({b[i], i});
  FOR(i, 1, n + 1) {
    auto it = S.find({a[i], i});
    if (it != S.end()) {
      S.erase(it);
      nxt[i] = i;
      v[i] = 1;
    }
  }
  iota(f, f + n + 1, 0);
  FOR(i, 1, n + 1) {
    if (v[i]) continue;
    auto it = S.lower_bound({a[i], 0});
    f[g(it->se)] = g(i);
    nxt[i] = it->se;
    S.erase(it);
  }
  FOR(i, 1, n + 1)++ cnt[g(i)], bel[a[i]].pb(g(i));
  int even = 0;
  FOR(i, 1, n + 1) if (cnt[i] && ((cnt[i] & 1) == 0))++ even;
  if (even & 1) {
    FOR(i, 1, n + 1) {
      if (bel[i].empty()) continue;
      if (bel[i].size() > 1) {
        println("YES");
        return;
      }
    }
    println("NO");
  } else
    println("YES");
}

int main() {
#ifndef MISAKA
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  int T;
  cin >> T;
  while (T--) solve();
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