#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

const int N = 3e5+5;

char s[N];

struct pam {
  char *s;
  int len[N], f[N], nxt[N][26];
  int last, tot;
  int dp[N];
  void init(char *_s, int n) {
    s = _s;
    len[0] = -1;
    f[0] = 0;
    len[1] = 0;
    f[1] = 0;
    last = 1;
    tot = 1;
    int p;
    for (int i = 0; i < n; ++i) {
      p = last;
      while (s[i] != s[i - len[p] - 1]) p = f[p];
      int &cur = nxt[p][s[i] - '0'];
      if (cur == 0) {
        cur = ++tot;
        len[cur] = len[p] + 2;
        if (p == 0) f[cur] = 1;
        else {
          p = f[p];
          while (s[i] != s[i - len[p] - 1]) p = f[p];
          f[cur] = nxt[p][s[i] - '0'];
        }
      }
      last = cur;
      ++dp[cur];
    }
  }
  i64 work() {
    i64 ret = 0;
    ROF(i, 0, tot + 1) {
      chkmax(ret, 1ll * dp[i] * len[i]);
      dp[f[i]] += dp[i];
    }
    return ret;
  }
} P;

void solve() {
  int n = rdstr(s) - s;
  P.init(s, n);
  cout << P.work() << '\n';
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
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/
