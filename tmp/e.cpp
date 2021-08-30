#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

#include "io"
#include "utils"
#define MULTI

const int N = 5005;

char s[N];
int ord[N][N];
int n;

struct sam {
  int len[N << 1], nxt[26][N << 1], f[N << 1], a[N << 1], c[N << 1];
  i64 sz[N << 1], p[N << 1], psum[27][N << 1];
  int lst, tot;
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
  void init(char* s) {
    f[0] = -1;
    while (*s) extend(*s++ - 'a');
    FOR(i, 0, tot + 1)++ c[len[i]];
    FOR(i, 1, tot + 1) c[i] += c[i - 1];
    FOR(i, 0, tot + 1) a[--c[len[i]]] = i;
    FOR(i, 0, tot + 1) sz[i] = 1;
    sz[0] = 0;
    ROF(i, 0, tot + 1) {
      p[a[i]] = sz[a[i]];
      FOR(j, 0, 26) {
        if (nxt[j][a[i]]) p[a[i]] += p[nxt[j][a[i]]];
      }
    }
    ROF(i, 0, tot + 1) {
      // psum[0][i] = 1;
      FOR(j, 0, 26) {
        psum[j + 1][i] = psum[j][i] + (nxt[j][a[i]] > 0) * p[nxt[j][i]];
      }
    }
    FOR(i, 0, n) work(i);
  }
  void work(int i) {
    int tt = 0;
    int cur = 0;
    int* const od = ord[i];
    for (; i < n; ++i) {
      od[i] = tt + psum[s[i] - 'a'][cur] + 1;
      tt = od[i];
      // cerr << od[i] << ' ';
      cur = nxt[s[i] - 'a'][cur];
    }
    cerr << endl;
  }
} S;

void solve() {
  memset(&S, 0, sizeof(S));
  n = rd();
  rdstr(s);
  S.init(s);  // substr[l, r] -> int O(n^2)
  set<int> st;
  set<int>::iterator it;
  st.clear();
  FOR(i, 0, n) FOR(j, i, n) {
    it = st.lower_bound(ord[i][j]);
    if (it != st.end()) st.erase(it);
    st.insert(ord[i][j]);
  }
  cout << st.size() << endl;
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
