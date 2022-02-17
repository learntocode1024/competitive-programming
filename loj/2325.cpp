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
const int N = 200, W = 64;
const int p = 998244353;
int m, k;
map<int, int> id[N];
int tot;
int inv[N];

int A[W][N][N], B[W][N];

int H(int a, int b, int c) {
  return a << 16 | b << 8 | c;
}

int a[N];
void dfs1(int n, int rem) {
  if (n == k+1) {
    int to = H(a[1], a[2], a[3]);
    id[to] = tot++;
    A[0][to][to] = B[0][to] = inv[m - rem + 1];
    return;
  }
  for (int i = 0; i <= rem; ++i) {
    a[n] = i;
    dfs1(n+1, rem - i);
  }
}

int dfs2(int n, int rem) {
  if (n == k+1) {
    int to = H(a[1], a[2], a[3]);
    FOR(i, 1, k + 1) {
      if (a[i]) {
        --a[i];
        ++a[i-1];
        
        ++a[i];
        --a[i-1];
      }
    }
    return;
  }
  for (int i = 0; i <= rem; ++i) {
    a[n] = i;
    dfs2(n+1, rem - i);
  }

}

inline void solve() {
  int T;
  inv[1] = 1;
  FOR(i, 2, N) {
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
  }
  rd(T, m, k);
  dfs1(1, m);
  dfs2(1, m);
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

