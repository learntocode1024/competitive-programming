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

const int N = 17;
vector<int> work(int x, int a, int b) {
  if (__builtin_popcount(x) == 1) {
    return {a, b};
  } else if (a & b) {
    int i = __builtin_ctz(a & b);
    int c = 1 << i;
    auto lst = work(x ^ c, a ^ c, b ^ c);
    vector<int> ret;
    for (int v = 0; v < lst.size(); ++v) {
      if (~v & 1) ret.pb(lst[v] ^ c), ret.pb(lst[v]);
      else ret.pb(lst[v]), ret.pb(lst[v] ^ c);
    }
    return ret;
  } else if (x ^ (a | b)) {
    int i = __builtin_ctz(x ^ (a | b));
    int c = 1 << i;
    auto lst = work(x ^ c, a, b);
    vector<int> ret;
    for (int v = 0; v < lst.size(); ++v) {
      if (v & 1) ret.pb(lst[v] ^ c), ret.pb(lst[v]);
      else ret.pb(lst[v]), ret.pb(lst[v] ^ c);
    }
    return ret;
  } else {
    int cc = a ^ b;
    int i = __builtin_ctz(cc);
    int c1 = 1 << i;
    cc ^= c1;
    int j = __builtin_ctz(cc);
    int c2 = 1 << j;
    x = x ^ c1 ^ c2;
    auto lst = work(x, a & x, b & x);
    int c = c1 | c2, d = a & c;
    int tmp[2][4] = {
      {d, d ^ c1, d ^ c, d ^ c2}, {c, d ^ c2, d ^ c2, d ^ c}
    };
    vector<int> ret;
    for (int v = 0; v < lst.size(); ++v) {
      ret.pb(lst[v] | tmp[0][0]);
    }
    for (int v = lst.size() - 1; v >= 0; --v) {
      ret.pb(lst[v] | tmp[0][1]);
    }
    for (int v = 0; v < lst.size(); ++v) {
      FOR(h, 2, 4) ret.pb(lst[v] | tmp[v&1][h]);
    }
    return ret;
  }
}

inline void solve() {
  int n, a, b;
  rd(n, a, b);
  if (!__builtin_parity(a^b))println("NO");
  else {
    println("YES");
    for (auto v : work((1 << n) - 1, a, b)) {
      cout << v << " \n"[b == v];
    }
  }
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

