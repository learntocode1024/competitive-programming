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

const int N = 1e3+5;
int f[N];
int n, d, t;
int get(int x) {
  if (x == f[x]) return x;
  return (f[x] = get(f[x]));
}
int s[N];


inline void calc() {
  priority_queue<int> pq;
  FOR(i, 1, n + 1) {
    ++s[get(i)];
  }
  FOR(i, 1, n + 1) {
    pq.push(s[i]);
    s[i] = 0;
  }
  FOR(i, 0, t) {
    int x = pq.top();
    pq.pop();
    x += pq.top();
    pq.pop();
    pq.push(x);
  }
  println(pq.top() - 1);
}

inline void solve() {
  rd(n, d);
  t = 0;
  iota(f, f + n + 1, 0);
  FOR(i, 0, d) {
    int a, b;
    rd(a, b);
    int fa = get(a), fb = get(b);
    if (fa == fb) ++t;
    else f[fa] = fb;
    calc();
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

