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
char s1[N], s2[N];
int n, k;

namespace sub1 {
vector<string> F[6];

string get(string s, int& i) {
  int t = 0;
  string ret;
  for (;;++i) {
    if (s[i] == '(') ++t;
    else --t;
    if (t == -1) return ret;
    ret.pb(s[i]);
  }
}

string op1(string s, int i) {
  string ret, p, a, b, c;
  int n = s.size();
  FOR(j, 0, i) ret.pb(s[j]);
  if (s[i]=='('&&s[i+1]=='('&&s[i+2]=='(') {
    i += 3;
    a = get(s, i);
    ++i;
    b = get(s, i);
    ++i;
    c = get(s, i);
    ret = ret + "(("+a+")"+b+")"+"("+c+")";
    for (++i;i<n;++i) ret.pb(s[i]);
    return ret;
  }
  return "";
}
string op2(string s, int i) {
  string ret, p, a, b, c;
  int n = s.size();
  FOR(j, 0, i) ret.pb(s[j]);
  if (s[i]=='('&&s[i+1]=='(') {
    i += 2;
    a = get(s, i);
    ++i;
    if (s[i] != '(') return "";
    ++i;
    b = get(s, i);
    ++i;
    c = get(s, i);
    ret = ret + "(("+a+")"+b+")"+"("+c+")";
    for (++i;i<n;++i) ret.pb(s[i]);
    return ret;
  }
  return "";
}
string op3(string s, int i) {
  string ret, p, a, b, c;
  int n = s.size();
  FOR(j, 0, i) ret.pb(s[j]);
  if (s[i]=='(') {
    ++i;
    a = get(s, i);
    ++i;
    if (s[i]!='('||s[i+1]!='(') return "";
    i += 2;
    b = get(s, i);
    ++i;
    c = get(s, i);
    ret = ret + "(("+a+")"+b+")"+"("+c+")";
    for (++i;i<n;++i) ret.pb(s[i]);
    return ret;
  }
  return "";
}
string op4(string s, int i) {
  string ret, p, a, b, c;
  int n = s.size();
  FOR(j, 0, i) ret.pb(s[j]);
  if (s[i]=='(') {
    ++i;
    a = get(s, i);
    ++i;
    if (s[i] != '(') return "";
    ++i;
    b = get(s, i);
    ++i;
    if (s[i] != '(') return "";
    ++i;
    c = get(s, i);
    ret = ret + "(("+a+")"+b+")"+"("+c+")";
    for (++i;i<n;++i) ret.pb(s[i]);
    return ret;
  }
  return "";
}

string op5(string s, int i) {
  string ret;
  if (s[i] != '('||s[i+1] != ')') return "";
  FOR(j, 0, i) ret.pb(s[j]);
  FOR(j, i+2, s.size()) ret.pb(s[j]);
  return ret;
}


struct myOp {
  int op, x;
};

int operator+(int a, myOp b) {
  if (b.op<5) return a;
  return a + 1;
}

map<string, int> S;
string rS[300];
vector<pair<int, myOp> > g[300];
pair<int, myOp> f[300];
int d[300];
  int tot = 0;

inline void init() {
  F[0].pb("");
  FOR(i, 1, 6) {
    FOR(j, 0, i) {
      for (auto a : F[j]) {
        for (auto b : F[i-j-1]) {
          F[i].pb("("+a+")"+b);
        }
      }
    }
  }
  FOR(i, 1, 6) for (auto a : F[i]) S.insert({a,++tot}), rS[tot] = a;
  FOR(i, 1, tot + 1) {
    int l = rS[i].size();
    FOR(j, 0, l-5) {
      string to;
      to = op1(rS[i], j);
      if (to.size()>1) {
        g[i].eb(S[to], myOp{1, j});
      }
      to = op2(rS[i], j);
      if (to.size()>1) {
        g[i].eb(S[to], myOp{2, j});
      }
      to = op3(rS[i], j);
      if (to.size()>1) {
        g[i].eb(S[to], myOp{3, j});
      }
      to = op4(rS[i], j);
      if (to.size()>1) {
        g[i].eb(S[to], myOp{4, j});
      }
    }
    FOR(j, 0, l-1) {
      string to = op5(rS[i], j);
      if (to.size()>1) {
        g[i].eb(S[to], myOp{6,j});
        g[S[to]].eb(i, myOp{5,j});
      }
    }
  }
}
deque<int> Q;
myOp out[10000];
int tt;
void work() {
  int nn, kk;
  cin >> nn >> kk;
  string s1, s2;
  cin >> s1 >> s2;
  int s = S[s1], t = S[s2];
  FOR(i, 1, tot + 1) d[i] = 1e6, f[i] = {};
  d[s] = 0;
  Q.push_front(s);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop_front();
    for (auto to : g[u]) {
      if (d[to.fi] != 1e6) continue;
      d[to.fi] = d[u] + to.se;
      f[to.fi] = {u, to.se};
      if (d[to.fi] > d[u]) Q.push_back(to.fi);
      else Q.push_front(to.fi);
    }
  }
  if (d[t] <= 4) {
    tt = 0;
    while (t) {
      out[++tt] = f[t].se;
      t = f[t].fi;
    }
    --tt;
    println(tt);
    while (tt) {
      println(out[tt].op, out[tt].x);
      --tt;
    }
  } else println(-1);
}

}

namespace sub2 {
void work() {
  cin >> n >> k;
  cin >> s1 >> s2;
  n <<= 1;
  cout << n << '\n';
  ROF(i, 0, n) if (s1[i] == '(') cout << "6 " << i << '\n';
  FOR(i, 0, n) if (s2[i] == '(') cout << "5 " << i << '\n';
}
}

int main() {
#ifndef MISAKA
  freopen("oper.in", "r", stdin);
  freopen("oper.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  int id;
  int T;
  cin >> id >> T;
  if (id <= 3) sub1::init();
  if (id <= 3) while(T--) sub1::work();
  else while (T--) sub2::work();
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

