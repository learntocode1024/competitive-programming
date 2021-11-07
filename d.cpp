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

const int N = 5e5+5;
char s[N], t[N];
int n, k;

inline void trans_min() {
  int i = 1, j = 0, k = 0;
  while (i < n && j < n && k < n) {
    if (s[(i + k) % n] == s[(j + k) % n]) ++k;
    else {
      if (s[(i + k) % n] < s[(j + k) % n]) j = j + k + 1;
      else i = i + k + 1;
      if (i == j) ++i;
      k = 0;
    }
  }
  chkmin(i, j);
  FOR(f, 0, n) {
    t[f + 1] = s[(f + i) % n];
  }
}

int sa[N], rk[N << 1], tmp[N << 1];
int vis[N];

inline void suf_sort() {
  iota(sa + 1, sa + n + 1, 1);
  FOR(i, 1, n + 1) rk[i] = t[i];
  for (int w = 1; w < n; w <<= 1) {
    sort(sa + 1, sa + n + 1, [w] (auto a, auto b) { return rk[a] == rk[b] ? rk[a + w] < rk[b + w] : rk[a] < rk[b]; });
    memcpy(tmp, rk, sizeof (rk));
    for (int i = 1, c = 0; i <= n; ++i) {
      if (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + w] == tmp[sa[i - 1] + w]) {
        rk[sa[i]] = c;
      } else rk[sa[i]] = ++c;
    }
  }
  vis[n + 1] = 1;
  FOR(i, 1, k) {
    vis[sa[i]] = 1;
  }
  for (int i = sa[k]; !vis[i]; ++i) print(t[i]);
  print('\n');
}

inline void solve() {
  rd(n, k, s);
  FOR(i, 0, n - 1) {
    if (s[i] != s[i + 1]) {
      trans_min();
      suf_sort();
      return;
    }
  }
  s[n / k + ((n % k) != 0)] = '\0';
  cout << s << '\n';
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
