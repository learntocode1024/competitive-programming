#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  *s = '\0';
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
#define MULTI

const int N = 10005;

char s[N];
int ord[N][N];
int n;

struct sam {
  int len[N << 1] = {}, nxt[26][N << 1] = {}, f[N << 1] = {}, a[N << 1] = {}, c[N << 1] = {};
  i64 sz[N << 1] = {}, low[27][N << 1] = {};
  int lst = 0, tot = 0;
  void extend(char ch) {
    int cur = ++tot;
    len[cur] = len[lst] + 1;
    sz[cur] = 1;
    int p = lst;
    for (; p != -1 && !nxt[ch][p]; p = f[p]) {
      nxt[ch][p] = cur;
    }
    if (p == -1) {
      f[cur] = 0;
    } else {
      int q = nxt[ch][p];
      if (len[q] == len[p] + 1) {
        f[cur] = q;
      } else {
        int mir = ++tot;
        for (int i = 0; i < 26; ++i) nxt[i][mir] = nxt[i][q];
        len[mir] = len[p] + 1;
        f[mir] = f[q];
        f[q] = f[cur] = mir;
        for (; p != -1 && nxt[ch][p] == q; p = f[p]) {
          nxt[ch][p] = mir;
        }
      }
    }
    lst = cur;
  }
  inline void clear() {
    FOR(i, 0, tot + 1) f[i] = a[i] = c[i] = 0;
    FOR(i, 0, 26) FOR(j, 0, tot + 1) nxt[i][j] = 0;
    lst = tot = 0;
  }
  void init(char* s) {
    clear();
    f[0] = -1;
    while (*s) extend(*s++ - 'a');
    FOR(i, 0, tot + 1) ++c[len[i]];
    FOR(i, 1, tot + 1) c[i] += c[i - 1];
    FOR(i, 0, tot + 1) a[--c[len[i]]] = i;
    FOR(i, 0, tot + 1) sz[i] = 1;
    ROF(i, 0, tot + 1) {
      int u = a[i];
      low[0][u] = 1;
      for (int j = 0; j < 26; ++j) {
        if (nxt[j][u]) sz[u] += sz[nxt[j][u]];
        if (j < 25) low[j + 1][u] = sz[u];
      }
    }
    FOR(i, 0, n) work(i);
  }
  void work(int x) {
    int *o = ord[x];
    int p = 0;
    int ans = 0;
    for (int cur = x; cur < n; ++cur) {
      ans += low[s[cur]-'a'][p];
      o[cur] = ans;
      p = nxt[s[cur]-'a'][p];
    }
  }
} S;

double clc;

void solve() {
  n = rd();
  IO::rdstr(s);
  S.init(s);
  cerr << (clock() - clc) / CLOCKS_PER_SEC << '\n';
  set<int> st;
  set<int>::iterator it;
  st.clear();
  FOR(i, 0, n) FOR(j, i, n) {
    it = st.lower_bound(ord[i][j]);
    if (it != st.end()) st.erase(it);
    st.insert(ord[i][j]);
  cerr << (clock() - clc) / CLOCKS_PER_SEC << '\n';
  }
  cout << st.size() << endl;
}

int main() {
  freopen("1.in", "r", stdin);
  clc = clock();
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
