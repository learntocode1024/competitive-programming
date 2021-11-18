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

const int N = 2e5+5;
set<pii> S;
map<int, vector<int> > M;
int a[N], b[N], nxt[N];
bool v[N];
int n, s;
int o[N];
vector<vector<int> > ans;

int f[N];
int g(int c) {
  if (c == f[c]) return c;
  return (f[c] = g(f[c]));
}

inline void solve() {
  rd(n, s);
  FOR(i, 1, n + 1) cin >> a[i];
  copy(a + 1, a + n + 1, b + 1);
  sort(b + 1, b + n + 1);
  FOR(i, 1, n + 1) S.insert({b[i], i});
  int cnt = 0;
  FOR(i, 1, n + 1) {
    auto it = S.find({a[i], i});
    if (it != S.end()) {
      ++cnt;
      S.erase(it);
      v[i] = 1;
    }
  }
  if (cnt + s < n) {
    println(-1);
  } else if (cnt == n) {
    println(0);
  } else {
    iota(f, f + n + 1, 0);
    FOR(i, 1, n + 1) {
      if (v[i]) continue;
      auto it = S.lower_bound({a[i], 0});
      f[g(it->se)] = g(i);
      nxt[i] = it->se;
      S.erase(it);
      M[a[i]].pb(i);
    }
    for (auto &v : M) {
      for (int i = 0; i < v.se.size() - 1; ++i) {
        int f1 = g(v.se[i]), f2 = g(v.se[i + 1]);
        if (f1 != f2) {
          f[f1] = f2;
          swap(nxt[v.se[i]], nxt[v.se[i + 1]]);
        }
      }
    }
    FOR(i, 1, n + 1) {
      if (!v[i]) {
        ans.pb(vector<int>());
        int p = i;
        while (!v[p]) {
          v[p] = 1;
          ans.back().pb(p);
          p = nxt[p];
        }
      }
    }
    int q = ans.size();
    int t = s - n + cnt;
    chkmin(t, q);
    if (t <= 2) {
      println(q);
      for (auto &v : ans) {
        println(v.size());
        for (auto i : v) {
          cout << i << ' ';
        }
        cout << '\n';
      }
    } else {
      println(q - t + 2);
      int sz = 0;
      FOR(i, 0, t) {
        sz += ans[i].size();
      }
      println(sz);
      FOR(i, 0, t) {
        for (auto i : ans[i]) {
          cout << i << ' ';
        }
      }
      cout << '\n';
      println(t);
      ROF(i, 0, t) cout << ans[i][0] << ' ';
      cout << '\n';
      FOR(i, t, ans.size()) {
        println(ans[i].size());
        for (auto i : ans[i]) {
          cout << i << ' ';
        }
        cout << '\n';
      }
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

