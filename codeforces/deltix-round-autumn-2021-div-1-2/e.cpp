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

const int N = 1e5+5;
int n, q;
char s[N];
int hb;
struct {
  struct node {
    int a, b;
    int p, s, f;
    node() = default;
    node(char ch) {
      if (ch == 'a') a = 1, b = 0;
      else if (ch == 'b') a = -1, b = -1;
      else a = 0, b = 1;
      p = min(a, 0);
      s = min(b, 0);
      f = min(p, s);
    }
  } a[N<<2];
  inline node merge(const node &l, const node &r) {
    node x;
    x.a = l.a + r.a;
    x.b = l.b + r.b;
    x.p = min(l.p, l.a + r.p);
    x.s = min(r.s, l.s + r.b);
    x.f = min(l.p + r.s, min(l.a + r.f, l.f + r.b));
    return x;
  }
  void build(int p = 1, int l = 0, int r = n) {
    if (r - l == 1) {
      a[p] = node(s[l]);
      return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid, r);
    a[p] = merge(a[p<<1], a[p<<1|1]);
  }
  void ch(int p, int l, int r, int x, char c) {
    if (r - l == 1) {
      a[p] = node(c);
      return;
    }
    int mid = (l + r) >> 1;
    if (x < mid) ch(p<<1, l, mid, x, c);
    else ch(p<<1|1, mid, r, x, c);
    a[p] = merge(a[p<<1], a[p<<1|1]);
  }
} T;

inline void solve() {
  rd(n, q, s);
  T.build();
  FOR(i, 0, n) hb += s[i] == 'b';
  while (q--) {
    int x;
    char c;
    rd(x, c);
    --x;
    hb -= s[x] == 'b';
    hb += c == 'b';
    s[x] = c;
    T.ch(1, 0, n, x, c);
    println(T.a[1].f + hb);
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
 