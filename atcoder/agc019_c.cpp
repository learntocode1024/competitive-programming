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

const int N = 1e5+5;
int X, Y, Z;
pii f[N];
i64 ans, sum;
i64 s3[N];
priority_queue<int> pq;
using namespace __gnu_pbds;
tree<pii, null_type, greater<pii>, rb_tree_tag, tree_order_statistics_node_update> S;

inline void solve() {
  rd(X, Y, Z);
  FOR(i, 0, X + Y + Z) {
    int a, b, c;
    rd(a, b, c);
    sum += a;
    f[i] = mkp(b - a, c - a);
  }
  sort(f, f + X + Y + Z);
  reverse(f, f + X + Y + Z);
  i64 cur = 0;
  FOR(i, Y + Z - 1, X + Y + Z) S.insert({f[i].se, i});
  s3[Y + Z - 1] = S.begin()->fi;
  ROF(i, Z, Y + Z - 1) {
    S.insert({f[i].se, i});
    int k = Y + Z - i;
    s3[i] = s3[i + 1];
    if (S.order_of_key({f[i].se, i}) < k) s3[i] += f[i].se;
    else s3[i] += S.find_by_order(k - 1)->fi;
  }
  FOR(i, 0, Y) cur += f[i].fi, pq.push(f[i].se - f[i].fi);
  chkmax(ans, cur + sum + s3[Y]);
  for (int i = Y; i < Z + Y; ++i) {
    cur += f[i].fi;
    pq.push(f[i].se - f[i].fi);
    cur += pq.top();
    pq.pop();
    chkmax(ans, cur + sum + s3[i]);
  }
  println(ans);
}

int main() {
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

