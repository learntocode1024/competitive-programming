#include <bits/stdc++.h>
using namespace std;
mt19937 gen(time(0));

const int c = 1000, n = 300;
int a[c + 100], b[c + 100];
uniform_int_distribution<int> rg{1, c};
int w[c], ccccc[c], low[c], pri[c], tot;

void prework() {
  ccccc[1] = 1; w[1] = 1;
  for (int i = 2; i < c + 1; ++i) {
    if (!low[i]) {
      low[i] = i;
      w[i] = i;
      ccccc[i] = 1;
      pri[tot++] = i;
    }
    for (int j = 0; j < tot && i * pri[j] <= c; ++j) {
      if (pri[j] < low[i]) {
        low[i * pri[j]] = pri[j];
        ccccc[i * pri[j]] = ccccc[i];
        w[i * pri[j]] = w[i] * pri[j];
      } else {
        low[i * pri[j]] = pri[j];
        ccccc[i * pri[j]] = 0;
        w[i * pri[j]] = w[i];
        break;
      }
    }
  }
  int cnt = 0;
  static int ask[c*7/10];
  for (int i = 1; i < c + 1; ++i) {
    if (ccccc[i] == 1) {
      ask[cnt++] = i;
    }
  }
  for (int i = 0; i < cnt; ++i) {
    int x = 0;
    for (int j = 0; j < n; ++j) {
      if (__gcd(a[j], ask[i]) == 1) x ^= a[j];
    }
    cout << x << ' ';
  }
  cout << endl;
}


int main() {
  set<int> aa;
  while (aa.size() < n) {
    aa.insert(rg(gen));
  }
  auto it = aa.begin();
  for (int i = 0; i < n; ++i) {
    a[i] = *it;
    ++it;
    cerr << a[i] << ' ';
  }
  cout << c << ' ' << n << '\n';
  prework();
}