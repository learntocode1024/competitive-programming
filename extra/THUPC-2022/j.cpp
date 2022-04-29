#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
map<int, vector<pii> > h, V;
struct seg {
  bool t;
  int l, h, c;
  bool operator == (seg r) {
    return l == r.l && h == r.h && c == r.c;
  }
  bool operator != (seg r) {
    return l != r.l || h != r.h || c != r.c;
  }
};

vector<seg> a, b, ff;

#define d(i) a##i.l
#define l(i) a##i.l
#define r(i) a##i.h
#define u(i) a##i.h
#define x(i) a##i.c
#define y(i) a##i.c

bool crs(seg a, seg b) {
  return a.t != b.t && a.c >= b.l && a.c <= b.h && b.c >= a.l && b.c <= a.h;
}

bool inv(vector<seg> f) {
  for (auto i : f) {
    for (auto j : ff) {
      if (crs(i,j)) {
        bool fid = 0;
        for (auto k : f) fid |= k == j;
        if (!fid) return 1;
      }
    }
  }
  return 0;
}

bool T(seg a1, seg a2) {
  if (inv(vector<seg> {a1,a2})) return 0;
  return (d(2)<y(1)&&y(1)==u(2)&&l(1)<x(2)&&x(2)<r(1));
}
bool H(seg a3, seg a4, seg a5) {
  if (inv(vector<seg> {a3,a4,a5})) return 0;
  return d(3)==d(5)&&d(5)<y(4)&&y(4)<u(3)&&u(3)==u(5)&&x(3)==l(4)&&l(4)<r(4)&&r(4)==x(5);
}
bool U(seg a6, seg a7, seg a8) {
  if (inv(vector<seg> {a6,a7,a8})) return 0;
  return d(6)==d(8)&&d(8)==y(7)&&y(7)<u(6)&&u(6)==u(8)&&x(6)==l(7)&&l(7)<r(7)&&r(7)==x(8);
}
bool P(seg a9, seg a10, seg a11, seg a12) {
  if (inv(vector<seg> {a9,a10,a11,a12})) return 0;
  return d(9)<y(11)&&y(11)==d(12)&&d(12)<u(9)&&u(9)==y(10)&&y(10)==u(12)&& 
                           x(9)==l(10)&&l(10)==l(11)&&l(11)<r(10)&&r(10)==r(11)&&r(11)==x(12);
}
bool C(seg a13, seg a14, seg a15) {
  if (inv(vector<seg> {a13,a14,a15})) return 0;
  return d(13)==y(15)&&y(15)<u(13)&&u(13)==y(14)&&x(13)==l(14)&&l(14)==l(15)&&l(15)<r(14)&&r(14)==r(15);
}

inline void solve() {
  int n;
  rd(n);
  while (n--) {
    int op, l, r, c;
    rd(op, l, r, c);
    if (op) V[c].eb(l,r);
    else h[c].eb(l,r);
  }
  int cnt = 0;
  for (auto v : h) {
    vector<pii> &f = v.se;
    sort(begin(f), end(f));
    int c = 0;
    for (int i = 1; i < f.size(); ++i) {
      if (f[c].se >= f[i].fi) chkmax(f[c].se, f[i].se);
      else f[++c] = f[i];
    }
    FOR(i, 0, c) {
      a.pb({0,f[i].fi,f[i].se, v.fi});
    }
    cnt += c+1;
  }
  for (auto v : V) {
    vector<pii> &f = v.se;
    sort(begin(f), end(f));
    int c = 0;
    for (int i = 1; i < f.size(); ++i) {
      if (f[c].se >= f[i].fi) chkmax(f[c].se, f[i].se);
      else f[++c] = f[i];
    }
    FOR(i, 0, c) {
      b.pb({1,f[i].fi,f[i].se, v.fi});
    }
    cnt += c+1;
  }
  if (cnt != 15) {
    O("No");
    return;
  }
  for (auto i : a) ff.pb(i);
  for (auto i : b) ff.pb(i);
  bool ok = 1;
  FOR(i,0,a.size()-1) FOR(j,0,b.size()-1) {
    if (T(a[i], b[j])) {
      ok = 0;
      a.erase(begin(a)+i);
      b.erase(begin(b)+j);
      break;
    }
  }
  if (ok) {
    O("No");
    return;
  }
  ok = 1;
  FOR(i,0,a.size()-1) FOR(k,0,b.size()-1) FOR(j,0,b.size()-1) {
    if (j!= k && H(b[j], a[i], b[k])) {
      ok = 0;
      a.erase(begin(a)+i);
      b.erase(begin(b)+k);
      b.erase(begin(b)+j);
      break;
    }
  }
  if (ok) {
    O("No");
    return;
  }
  ok = 1;
  FOR(i,0,a.size()-1) FOR(k,0,b.size()-1) FOR(j,0,b.size()-1) {
    if (j!= k && U(b[j], a[i], b[k])) {
      ok = 0;
      a.erase(begin(a)+i);
      b.erase(begin(b)+k);
      b.erase(begin(b)+j);
      break;
    }
  }
  if (ok) {
    O("No");
    return;
  }
  ok = 1;
  FOR(i,0,a.size()-1) FOR(k,0,a.size()-1) FOR(j,0,b.size()-1) {
    if (i!= k && C(b[j], a[i], a[k])) {
      ok = 0;
      a.erase(begin(a)+i);
      a.erase(begin(a)+k);
      b.erase(begin(b)+j);
      break;
    }
  }
  if (ok) {
    O("No");
    return;
  }
  ok = 1;
  FOR(i,0,a.size()-1) FOR(k,0,a.size()-1) FOR(j,0,b.size()-1) FOR(l,0,b.size()-1) {
    if (j!= l && i != k && P(b[j], a[k], a[i], b[l])) {
      ok = 0;
      break;
    }
  }
  if (ok) {
    O("No");
    return;
  }
  ok = 1;
  O("Yes");
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

