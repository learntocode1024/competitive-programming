#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

const int N = 2005;

int a[N], l[N], r[N], pool[N];

int main() {
  srand(time(0));
  int n = rand() % N + 1;
  int cnt = rand() % n + 1;
  cnt >>= 1;
  FOR(i, 0, cnt) {
    pool[i] = rand();
  }
  FOR(i, 0, n) {
    a[i] = rand() % cnt;
  }
  int m = N - 5;
  FOR(i, 0, m) {
    l[i] = rand() % n + 1;
    r[i] = rand() % n + 1;
    if (l[i] > r[i]) swap(l[i], r[i]);
  }
  cout << n << '\n';
  FOR(i, 0, n) {
    cout << pool[a[i]] << ' ';
  }
  cout << '\n' << m << '\n';
  FOR(i, 0, m) {
    cout << l[i] << ' ' << r[i] << '\n';
  }
  return 0;
}

