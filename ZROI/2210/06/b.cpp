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
const int N = 1005, M = 8.1e4+5;
const int p = 998244353;
inline int q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

int a[N][N], sol_x[N];
int n, m, s, tot_s;

inline int inv(int x) {
  return q_pow(x,p-2);
}
const int i4 = 748683265;
const int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};

struct equ {
  int a[N];
  equ() {
    FOR(i, 0, s+1) a[i] = 0;
  }
  inline int eval() {
    int ans = a[s];
    FOR(i, 0, s) {
      ans = (ans + 1ll * a[i] * sol_x[i]) % p;
    }
    return ans;
  }
  inline void append() {
    FOR(i, 0, s) {
      ::a[tot_s][i] = a[i];
    }
    ::a[tot_s][s] = (p - a[s]) % p;
    ++tot_s;
  }
  friend equ operator * (const int &c, const equ &x) {
    equ ans;
    FOR(i, 0, s+1) {
      ans.a[i] = 1ll * c * x.a[i] % p;
    }
    return ans;
  }
  friend equ operator + (const equ &x, const equ &y) {
    equ ans;
    FOR(i, 0, s + 1) {
      ans.a[i] = (x.a[i] + y.a[i]) % p;
    }
    return ans;
  }
  friend equ operator + (const equ &x, const int &c) {
    equ ans(x);
    ans.a[s] = (ans.a[s] + c) % p;
    return ans;
  }
} x[M];

inline void gauss() {
  FOR(i, 0, s) {
    FOR(j, i, s) {
      if (a[j][i] != 0) {
        if (j == i) break;
        FOR(k, 0, s+1) swap(a[j][k], a[i][k]);
        break;
      }
    }
    int iv = inv(a[i][i]);
    FOR(k, i, s + 1) a[i][k] = 1ll * a[i][k] * iv % p;
    FOR(j, 0, s) if (j != i && a[j][i] != 0) {
      int c = a[j][i];
      FOR(k, 0, s + 1) a[j][k] = (a[j][k] + p - 1ll * a[i][k] * c % p) % p;
    }
  }
  FOR(i, 0, s) {
    sol_x[i] = a[i][s];
  }
}
map<pii, int> id, w, deg;
map<pii, bool> vis;
pii qu[M];
int hd, tl;

inline void cross(pii o) {
  static const int cx[4] = {1,1,-1,-1}, cy[4] = {1,-1,1,-1};
  x[id[o]].a[s++] = 1;
  --deg[o];
  FOR(j, 0, 4) {
    int s = o.fi + dx[j], t = o.se + dy[j];
    if (id.find({s,t}) != id.end() && id[o] < n) --deg[{s,t}];
  }
  vis[o] = 1;
  FOR(k, 0, 4) {
    pii p = {o.fi + cx[k], o.se + cy[k]};
    while (id.find(p) != id.end()) {
      x[id[p]].a[s++] = 1;
      vis[p] = 1;
      bool nok = id[p] >= n;
      --deg[p];
      FOR(j, 0, 4) {
        int s = p.fi + dx[j], t = p.se + dy[j];
        if (id.find({s,t}) != id.end() && !nok) --deg[{s,t}];
      }
      p = {p.fi + cx[k], p.se + cy[k]};
    }
  }
}

inline void build(pii o) {
  cross(o);
  FOR(k, 0, 4) {
    if (id.find({o.fi+dx[k], o.se+dy[k]}) != id.end()) {
      o.fi += dx[k];
      o.se += dy[k];
      cross(o);
      break;
    }
  }
  hd = 1;
  for (auto u : deg) {
    if (u.se == 1) {
      qu[++tl] = u.fi;
    } else if (u.se == 0) {
      equ f = x[id[u.fi]] + (p - w[u.fi]) % p;
      FOR(k, 0, 4) {
        pii v = {u.fi.fi+dx[k], u.fi.se+dy[k]};
        if (id.find(v) == id.end() || (id[v] >= n)) continue;
        f = f + (p-i4) * x[id[v]];
      }
      f.append();
    }
  }
  while (hd <= tl) {
    pii u = qu[hd++];
    pii to = u;
    equ f = x[id[u]] + (p - w[u]) % p;
    bool nok = id[u] >= n;
    FOR(k, 0, 4) {
      pii v = {u.fi+dx[k], u.se+dy[k]};
      if (id.find(v) == id.end() || (id[v] >= n)) continue;
      f = f + (p-i4) * x[id[v]];
      if (!vis[v]) to = v;
    }
    if (deg[u] == 0) {
      f.append();
      continue;
    } else if (to == u) {
      x[id[u]] = (p-1) * f;
    } else {
      x[id[to]] = 4 * f;
    }
    vis[to] = 1;
    --deg[to];
    if (deg[to] == 1) qu[++tl] = to;
    nok = id[to] >= n;
    FOR(k, 0, 4) {
      pii v = {to.fi+dx[k], to.se+dy[k]};
      if (id.find(v) != id.end() && !(nok)) {
        --deg[v];
        if (deg[v] == 1) qu[++tl] = v;
      }
    }
  }
}

inline void solve() {
  rd(n);
  m = n;
  set<int> xx, yy, xxx, yyy;
  int lx = 1e9, hx = -1e9, ly = 1e9, hy = -1e9;
  FOR(i, 0, n) {
    int x, y, c;
    rd(x, y, c);
    chkmin(lx, x);
    chkmax(hx, x);
    chkmax(hy, y);
    chkmin(ly, y);
    id[{x,y}] = i;
    w[{x,y}] = c;
    FOR(k, 0, 4) {
      int s = x + dx[k], t = y + dy[k];
      if (id.find({s,t}) == id.end()) {
        id[{s,t}] = m++;
      }
    }
  }
  for (auto u : id) {
    if (u.se > n) continue;
    if (u.fi.fi == lx) xx.insert(u.fi.se);
    if (u.fi.se == ly) yy.insert(u.fi.fi);
  }
  for (auto u : id) {
    if (u.se > n) continue;
    if (u.fi.fi == hx) xxx.insert(u.fi.se);
    if (u.fi.se == hy) yyy.insert(u.fi.fi);
  }
  int S, T;
  for (auto u : xxx) {
    if (xx.find(u) != xx.end()) {
      S = u;
      break;
    }
  }
  for (auto u : yyy) {
    if (yy.find(u) != yy.end()) {
      T = u;
      break;
    }
  }
  for (auto u : id) {
    pii x = u.fi;
    deg[x] = 1;
    FOR(k, 0, 4) {
      int s = x.fi + dx[k], t = x.se + dy[k];
      if (id.find({s,t}) == id.end() || (id[{s,t}] >= n)) continue;
      ++deg[x];
    }
  }
  build({T,S});
  println(s);
  int ans = 0;
  gauss();
  FOR(i, n, m) {
    ans ^= x[i].eval();
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
