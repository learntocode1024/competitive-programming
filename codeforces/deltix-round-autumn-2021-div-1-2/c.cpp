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

const int N = 2e5+5, NN = 1e6+5;
int n, e;
int a[N], b[N];
int pre[N], nxt[N];
bool isp[NN];
int pri[NN], low[NN], tot;

inline void solve() {
  rd(n, e);
  FOR(i, 0, n) cin >> a[i];
  i64 ans = 0;
  FOR(i, 0, e) {
    int j = 0;
    for (; i + e * j < n; ++j) {
      b[j + 1] = a[i + e * j];
    }
    ++j;
    FOR(k, 1, j) pre[k] = b[k] == 1 ? pre[k-1] : k;
    nxt[j] = j;
    ROF(k, 1, j) nxt[k] = b[k] == 1 ? nxt[k + 1] : k;
    FOR(k, 1, j) if (isp[b[k]]) {
      ans += 1ll * (k - pre[k - 1]) * (nxt[k + 1] - k) - 1;
    }
  }
  println(ans);
}

int main() {
  FOR(i, 2, NN) {
    if (!low[i]) {
      low[i] = i;
      pri[tot++] = i;
      isp[i] = 1;
    }
    for (int j = 0; j < tot && i * pri[j] < NN; ++j) {
      low[pri[j] * i] = low[i];
      if (low[i] == pri[j]) continue;
    }
  }
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  int T;
  cin >> T;
  while (T--)
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

