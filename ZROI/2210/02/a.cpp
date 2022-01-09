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
const int N = 10;
const int p = 998244353;
int a[N];
int n;
int k;
int ans, cur;
int b[N], b0[N], bk[N];
int inv[50];

void work() {
  FOR(i, 1, k) ++bk[min(a[b[i]], a[b[i-1]])];
  ++bk[min(a[b[0]], a[b[k-1]])];
  int rem = 0;
  int to = 1;
  FOR(i, 1, n + 1) {
    ++rem;
    while (bk[i]) to *= rem, --rem, --bk[i];
  }
  cur = (cur + to) % p;
}

void run(int i, int v) {
  if (i == k) {
    FOR(j, 0, k) b[j] = b0[j];
    do {
      work();
    } while (next_permutation(b, b + k));
    return;
  }
  for (int c = v; c <= n - k + i; ++c) {
    b0[i] = c;
    run(i+1, c+1);
  }
}

inline void solve() {
  cin >> n;
  inv[1] = 1;
  FOR(i, 2, 50) {
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
  }
  FOR(i, 0, n) cin >> a[i];
  for (int i = 2; i <= n; ++i) k = i, run(0, 0), ans = (ans + 1ll * cur * inv[i<<1])% p, cur = 0;
  println(ans);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
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

