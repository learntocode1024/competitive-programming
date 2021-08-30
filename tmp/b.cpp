#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

#define MULTI

char s[100];
bool ok[128], ban[128];

void solve() {
  int k = rd();
  rdstr(s);
  FOR(i, 0, k) {
    if (ok[s[i]]) {
      puts("1");
      cout << s[i] << '\n';
      return;
    }
  }
  FOR(i, 0, k) FOR(j, i + 1, k) {
    if (!ban[(s[i] - '0') * 10 + (s[j] - '0')]) {
      puts("2");
      cout << s[i] << s[j] << '\n';
      return;
    }
  }
}

int main() {
  IO::init_in();
  ok['1'] = 1;
  ok['4'] = 1;
  ok['6'] = 1;
  ok['8'] = 1;
  ok['9'] = 1;
  ban[23] = 1;
  ban[37] = 1;
  ban[53] = 1;
  ban[73] = 1;
  ban[57] = 1;
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}

