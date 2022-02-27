#include <bits/stdc++.h>
using namespace std;
template <typename T>
void rd(T &a) {
  cin >> a;
}
template <typename A, typename... B>
void rd(A &a, B &...b) {
  cin >> a;
  rd(b...);
}
template <typename A>
void print(const A &a) {
  cout << a;
}
template <typename A, typename... B>
void print(const A &a, const B &...b) {
  cout << a;
  print(b...);
}
template <typename A>
void println(const A &a) {
  cout << a << '\n';
}
template <typename A, typename... B>
void println(const A &a, const B &...b) {
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
#define ROF(i, j, k) for (int i = ((k)-1); i >= j; --i)
template <typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template <typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
typedef long double dbl;
dbl eps = 1e-10;
const int N = 1e5 + 5;
int n, K;

struct pt {
  dbl x, y;
  pt(dbl x = 0, dbl y = 0) : x(x), y(y) {}
};


struct pt2 {
  dbl x, y;
  dbl ang;
  bool typ;
  pt2(pt a, bool t) {
    x = a.x, y = a.y, typ = t;
    ang = atan2(y, x);
  }
  dbl dis() {
    return sqrt(x*x+y*y);
  }
  pt2(dbl x = 0, dbl y = 0) : x(x), y(y) { ang = atan2(y, x); }
  friend bool operator<(const pt2 &a, const pt2 &b) { return a.ang < b.ang; }
};

struct line {
  pt p;
  pt v;
  dbl ang;
  line() = default;
  line(pt p, pt v) : p(p), v(v) { ang = atan2(v.y, v.x); }
  friend bool operator<(const line &a, const line &b) { return a.ang < b.ang; }
};
pt operator+(pt A, pt B) { return pt(A.x + B.x, A.y + B.y); }
pt operator-(pt A, pt B) { return pt(A.x - B.x, A.y - B.y); }
pt operator*(pt A, dbl p) { return pt(A.x * p, A.y * p); }
pt operator/(pt A, dbl p) { return pt(A.x / p, A.y / p); }

dbl cross(pt A, pt B) { return A.x * B.y - B.x * A.y; }
bool left(line L, pt p) {
  return cross(L.v, p - L.p) >= 0;
}

pt l2p(line a, line b) {
  pt u = a.p - b.p;
  dbl t = cross(b.v, u) / cross(a.v, b.v);
  return a.p + a.v * t;
}

line L[N], A[N];
int m;
bool vis[N];
int id[N];
pt2 B[N];

pt2 lcp(const line & p) {
  
}

inline dbl getans() {
  dbl ans = 0;
  if (!m) {
    ans = M_PI * 1e6l;
  } else {
    int t = 0;
    A[m] = A[0];
    FOR(i, 1, m+1) {
      if (fabs(A[i-1].ang - A[i].ang) < M_PI) {
         pt2 c(l2p(A[i-1], A[i]), 0);
         B[t++] = c;
      } else {
        B[t++] = lcp(A[i-1]);
        B[t++] = lcp(A[i]);
      }
    }
    sort(B, B + t);
    t = unique(B, B + t) - B;
  }
  return ans;
}

void work() {
  static pt p[N];
  static line q[N];
  sort(L, L + n);
  int hd, tl;
  q[hd = tl = 0] = L[0];
  id[0] = 0;
  for (int i = 1; i < n; i++) {
    if (fabs(L[i].ang - q[tl].ang) < M_PI) {
      while (hd < tl && !left(L[i], p[tl - 1])) tl--;
      while (hd < tl && !left(L[i], p[hd])) hd++;
    } else {
      while (hd < tl && !left(L[i], p[hd])) hd++;
      while (hd < tl && !left(L[i], p[tl - 1])) tl--;
    }
    q[++tl] = L[i];
    id[tl] = i;
    if (fabs(cross(q[tl].v, q[tl - 1].v)) < eps) {
      tl--;
      if (left(q[tl], L[i].p)) q[tl] = L[i], id[tl] = i;
    }
    if (hd < tl) p[tl - 1] = l2p(q[tl - 1], q[tl]);
  }
  while (hd < tl && !left(q[hd], p[tl - 1])) tl--;
  m = 0;
  for (int i = hd; i <= tl; ++i) {
    vis[id[i]] = 1;
    A[m++] = q[i];
  }
  cout << fixed << setprecision(7) << getans() << '\n';
  int to = 0;
  // FOR(i, 0, n) {
  //   if (vis[i]) cout << i << ' ';
  // }
  cout << '\n';
  FOR(i, 0, n) if (!vis[i]) {
    L[to++] = L[i];
  }
  FOR(i, 0, to) vis[i] = 0;
  n = to;
}

inline void solve() {
  rd(n, K);
  pt ori(0,0);
  FOR(i, 0, n) {
    dbl e, d, c, r;
    rd(e, d, c, r);
    pt s(e, d), t (c, r);
    t = t - s;
    if (left(line(s,t), ori)) L[i] = line(s,t);
    else L[i] = line(s, ori-t);
  }
  while (K--) {
    work();
  }
}

int main() {
#ifndef MISAKA
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
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
