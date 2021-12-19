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

const int N = 23, S = 26;
const int p = 998244353;
inline void red(int &x) {if (x >= p) x -= p;}
int n;
short o[N][S];
short c[1<<N][S];
int a[1<<N], b[1<<N];

inline void solve() {
  cin >> n;
  FOR(i, 0, n) {
    string s;
    cin >> s;
    for (auto u : s) {
      ++o[i][u - 'a'];
    }
  }
  FOR(i, 0, S) c[0][i] = 32767;
  FOR(u, 1, 1 << n) {
    int i = __builtin_ctz(u);
    int v = u ^ (1 << i);
    i64 cur = 1;
    FOR(h, 0, S) c[u][h] = min(c[v][h], o[i][h]), cur = cur * (c[u][h] + 1) % p;
    // --cur;
    // if (cur < 0) cur = p - 1;
    if (__builtin_parity(u)) a[u] = cur;
    else a[u] = (p - cur) % p;
  }
  for(int i=2;i<=(1<<n);i<<=1)
    for(int j=0;j<(1<<n);j+=i)
      for(int k=0;k<(i>>1);k++)
        red(a[(i>>1)+j+k]+=a[j+k]);
  i64 ans = 0;
  FOR(u, 1, 1 << n) {
    i64 f = 0;
    FOR(i, 0, n) if ((u >> i) & 1) f += i + 1;
    f *= __builtin_popcount(u);
    f *= a[u];
    ans ^= f;
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

