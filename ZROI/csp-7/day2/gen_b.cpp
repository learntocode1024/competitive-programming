#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"

const int N = 10000;
char str[N + 5];

void solve() {
  srand(time(0));
  FOR(i, 0, N) {
    str[i] = "AP"[rand()&1];
  }
  auto data = fopen("b.in", "w");
  fprintf(stdout, "%s\n", str);
  fclose(data);
}

int main() {
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

