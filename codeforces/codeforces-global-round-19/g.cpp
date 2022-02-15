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

#define MULTI
const int N = 5e4+5, W = 20;
int cnt = 0;
vector<int> work(int n) {
  vector<int> a(W, 0);
  if (!n) return a;
  if (n == 1) {
    a[0] = 1;
    return a;
  }
  if (n == 2) {
    a[0] = 1;
    a[1] = 1;
    return a;
  }
  int t =  (31 - __builtin_clz(n));
  int m = 1 << t;
  if (m == n) {
    a = work(n - 1);
    ++a[t];
    return a;
  }
  a = work(m * 2 - n - 1);
  int r = n - m;
  auto b = work(r);
  cnt += r;
  a[t+1] += r;
  a[t]++;
  FOR(i, 0, W - 1) a[i+1] += b[i];
  return a;
}

void dry(int n, int p = 1) {
  if (n <= 2) {
    return;
  }
  int t =  (31 - __builtin_clz(n));
  int m = 1 << t;
  if (m == n) {
    dry(n - 1, p);
    return;
  }
  dry(m * 2 - n - 1, p);
  int r = n - m;
  FOR(i, 1, r + 1) {
    println(p * (m - i), p * (m + i));
  }
  dry(r, p<<1);
  cnt += r;
  return;
}

inline void solve() {
  cnt = 0;
  int n;
  rd(n);
  if (n == 2) {
    println(-1);
    return;
  }
  auto a = work(n);
  int t = 32 - __builtin_clz(n);
  if (n == (1 << (t-1))) --t;
  int I;
  FOR(i, 0, t) if (a[i] > 1) {
    a[i] -= 2;
    ++a[i+1];
    ++cnt;
    I = i;
    break;
  }
  auto b = a;
  FOR(i, 0, t) {
    while (b[i]) {
      --b[i];
      cnt += 2;
      ++b[i+1];
    }
  }
  ++cnt;
  println(cnt);
  dry(n);
  println(1<<I, 1<<I);
  FOR(i, 0, t) {
    while (a[i]) {
      --a[i];
      println(1<<i, 0);
      println(1<<i, 1<<i);
      ++a[i+1];
    }
  }
  println(0, 1<<t);
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

